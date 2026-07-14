namespace MaritimeOps.Ingestion.Telemetry;

public sealed class TelemetryMetricsReporter : BackgroundService
{
    private readonly TelemetryMetrics _metrics;
    private readonly ILogger<TelemetryMetricsReporter> _logger;

    public TelemetryMetricsReporter(
        TelemetryMetrics metrics,
        ILogger<TelemetryMetricsReporter> logger
    )
    {
        _metrics = metrics;
        _logger = logger;
    }

    protected override async Task ExecuteAsync(CancellationToken stoppingToken)
    {
        long lastReceivedPacket = 0;
        long lastDecodedPacket = 0;

        try
        {
            while (!stoppingToken.IsCancellationRequested)
            {
                await Task.Delay(TimeSpan.FromSeconds(1), stoppingToken);

                long currentReceivedPacket = _metrics.ReceivedPacket;
                long currentDecodedPacket = _metrics.DecodedPackets;

                long receivedPacketsPerSecond = currentReceivedPacket - lastReceivedPacket;

                long decodedPacketsPerSecond = currentDecodedPacket - lastDecodedPacket;

                lastReceivedPacket = currentReceivedPacket;
                lastDecodedPacket = currentDecodedPacket;

                _logger.LogInformation(
                    "Telemetry metrics: receivedPerSecond={ReceivedPerSecond}, decodedPerSecond={DecodedPerSecond}, totalReceived={TotalReceived}, totalDecoded={TotalDecoded}, badPackets={BadPackets}, droppedPackets={DroppedPackets}",
                    receivedPacketsPerSecond,
                    decodedPacketsPerSecond,
                    _metrics.ReceivedPacket,
                    _metrics.DecodedPackets,
                    _metrics.BadPackets,
                    _metrics.DroppedPackets
                );
            }
        } catch (OperationCanceledException) when (stoppingToken.IsCancellationRequested)
        {
            _logger.LogInformation("Telemetry metrics reporter stopping.");
        }
    }
}