namespace MaritimeOps.Ingestion.Telemetry;

public sealed class TelemetryMetricsReporter : BackgroundService
{
    private readonly TelemetryMetrics _metrics;
    private readonly VesselStateRegistry _vesselStateRegistry;
    private readonly ILogger<TelemetryMetricsReporter> _logger;

    public TelemetryMetricsReporter(
        TelemetryMetrics metrics,
        VesselStateRegistry vesselStateRegistry,
        ILogger<TelemetryMetricsReporter> logger
    )
    {
        _metrics = metrics;
        _vesselStateRegistry = vesselStateRegistry;
        _logger = logger;
    }

    protected override async Task ExecuteAsync(CancellationToken stoppingToken)
    {
        long lastReceivedPackets = 0;
        long lastDecodedPackets = 0;

        try
        {
            while (!stoppingToken.IsCancellationRequested)
            {
                await Task.Delay(TimeSpan.FromSeconds(1), stoppingToken);

                long currentReceivedPackets = _metrics.ReceivedPackets;
                long currentDecodedPackets = _metrics.DecodedPackets;

                long receivedPacketsPerSecond =
                    currentReceivedPackets - lastReceivedPackets;

                long decodedPacketsPerSecond =
                    currentDecodedPackets - lastDecodedPackets;

                lastReceivedPackets = currentReceivedPackets;
                lastDecodedPackets = currentDecodedPackets;

                _logger.LogInformation(
                    "Telemetry metrics: packetsPerSecond={PacketsPerSecond}, decodedPerSecond={DecodedPerSecond}, packetCount={PacketCount}, decodedPacketCount={DecodedPacketCount}, badPacketCount={BadPacketCount}, droppedPacketCount={DroppedPacketCount}, activeVesselCount={ActiveVesselCount}",
                    receivedPacketsPerSecond,
                    decodedPacketsPerSecond,
                    _metrics.ReceivedPackets,
                    _metrics.DecodedPackets,
                    _metrics.BadPackets,
                    _metrics.DroppedPackets,
                    _vesselStateRegistry.ActiveVesselCount
                );
            }
        } catch (OperationCanceledException) when (stoppingToken.IsCancellationRequested)
        {
            _logger.LogInformation("Telemetry metrics reporter stopping.");
        }
    }
}