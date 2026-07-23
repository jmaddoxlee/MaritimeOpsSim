using MaritimeOps.Ingestion.Telemetry;

namespace MaritimeOps.Ingestion.WebSockets;

public sealed class WebSocketTelemetryBroadcaster : BackgroundService
{
    private static readonly TimeSpan SnapshotInterval = TimeSpan.FromMilliseconds(100);
    private static readonly TimeSpan HeartbeatInterval = TimeSpan.FromSeconds(1);

    private readonly VesselStateRegistry _vesselStateRegistry;
    private readonly WebSocketClientManager _clientManager;
    private readonly ILogger<WebSocketTelemetryBroadcaster> _logger;

    public WebSocketTelemetryBroadcaster(
        VesselStateRegistry vesselStateRegistry,
        WebSocketClientManager clientManager,
        ILogger<WebSocketTelemetryBroadcaster> logger
    )
    {
        _vesselStateRegistry = vesselStateRegistry;
        _clientManager = clientManager;
        _logger = logger;
    }

    protected override async Task ExecuteAsync(CancellationToken stoppingToken)
    {
        _logger.LogInformation("WebSocket telemetry broadcaster started.");

        DateTimeOffset lastHeartbeatUtc = DateTimeOffset.MinValue;

        try
        {
            while (!stoppingToken.IsCancellationRequested)
            {
                DateTimeOffset nowUtc = DateTimeOffset.UtcNow;

                await BroadcastSnapshotAsync(nowUtc, stoppingToken);

                if (nowUtc - lastHeartbeatUtc >= HeartbeatInterval)
                {
                    await BroadcastHeartbeatAsync(nowUtc, stoppingToken);
                    lastHeartbeatUtc = nowUtc;
                }

                await Task.Delay(SnapshotInterval, stoppingToken);
            }
        }
        catch (OperationCanceledException) when (stoppingToken.IsCancellationRequested)
        {
            _logger.LogInformation("WebSocket telemetry broadcaster stopping.");
        }
    }

    private async Task BroadcastSnapshotAsync(
        DateTimeOffset nowUtc,
        CancellationToken cancellationToken
    )
    {
        IReadOnlyCollection<VesselTelemetrySnapshot> vessels =
            _vesselStateRegistry.GetSnapshotWithStaleStatus(nowUtc);

        TelemetrySnapshotMessage message = new(
            Type: "snapshot",
            TimestampUtc: nowUtc,
            ActiveVesselCount: vessels.Count(vessel => !vessel.IsStale),
            StaleVesselCount: vessels.Count(vessel => vessel.IsStale),
            Vessels: vessels
        );

        await _clientManager.BroadcastAsync(message, cancellationToken);
    }

    private async Task BroadcastHeartbeatAsync(
        DateTimeOffset nowUtc,
        CancellationToken cancellationToken
    )
    {
        TelemetryHeartbeatMessage message = new(
            Type: "heartbeat",
            TimestampUtc: nowUtc,
            ConnectedClientCount: _clientManager.ConnectedClientCount
        );

        await _clientManager.BroadcastAsync(message, cancellationToken);
    }
}