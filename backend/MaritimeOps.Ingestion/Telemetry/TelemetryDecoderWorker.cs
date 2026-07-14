using System.Threading.Channels;

namespace MaritimeOps.Ingestion.Telemetry;

public sealed class TelemetryDecoderWorker : BackgroundService
{
    private const int ExpectedPacketSizeBytes = 72;

    private readonly ChannelReader<UdpTelemetryPacket> _packetReader;
    private readonly TelemetryMetrics _metrics;
    private readonly ILogger<TelemetryDecoderWorker> _logger;

    public TelemetryDecoderWorker(
        ChannelReader<UdpTelemetryPacket> packetReader,
        TelemetryMetrics metrics,
        ILogger<TelemetryDecoderWorker> logger
    )
    {
        _packetReader = packetReader;
        _metrics = metrics;
        _logger = logger;
    }

    protected override async Task ExecuteAsync(CancellationToken stoppingToken)
    {
        _logger.LogInformation("Telemetry decoder worker started.");

        try
        {
            await foreach (UdpTelemetryPacket packet in _packetReader.ReadAllAsync(stoppingToken))
            {
                if (packet.Payload.Length != ExpectedPacketSizeBytes)
                {
                    _metrics.IncrementBadPacket();

                    _logger.LogWarning(
                        "Rejected malformed telemetry packet. bytes={PacketLength}, sender={SenderEndpoint}",
                        packet.Payload.Length,
                        packet.SenderEndpoint
                    );

                    continue;
                }

                _metrics.IncrementDecoded();
            }
        }
        catch (OperationCanceledException) when (stoppingToken.IsCancellationRequested) {
            _logger.LogInformation("Telemetry decoder worker stopping.");
        }
    }
}