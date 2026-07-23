using System.Threading.Channels;

namespace MaritimeOps.Ingestion.Telemetry;

public sealed class TelemetryDecoderWorker : BackgroundService
{
    private readonly ChannelReader<UdpTelemetryPacket> _packetReader;
    private readonly TelemetryPacketProcessor _packetProcessor;
    private readonly ILogger<TelemetryDecoderWorker> _logger;

    public TelemetryDecoderWorker(
        ChannelReader<UdpTelemetryPacket> packetReader,
        TelemetryPacketProcessor packetProcessor,
        ILogger<TelemetryDecoderWorker> logger
    )
    {
        _packetReader = packetReader;
        _packetProcessor = packetProcessor;
        _logger = logger;
    }

    protected override async Task ExecuteAsync(CancellationToken stoppingToken)
    {
        _logger.LogInformation("Telemetry decoder worker started.");

        try
        {
            await foreach (UdpTelemetryPacket packet in _packetReader.ReadAllAsync(stoppingToken))
            {
                _packetProcessor.Process(packet);
            }
        }
        catch (OperationCanceledException) when (stoppingToken.IsCancellationRequested)
        {
            _logger.LogInformation("Telemetry decoder worker stopping.");
        }
    }
}