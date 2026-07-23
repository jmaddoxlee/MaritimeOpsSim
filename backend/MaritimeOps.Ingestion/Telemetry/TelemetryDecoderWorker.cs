using System.Threading.Channels;

namespace MaritimeOps.Ingestion.Telemetry;

public sealed class TelemetryDecoderWorker : BackgroundService
{
    private readonly ChannelReader<UdpTelemetryPacket> _packetReader;
    private readonly PacketDecoder _packetDecoder;
    private readonly VesselStateRegistry _vesselStateRegistry;
    private readonly TelemetryMetrics _metrics;
    private readonly ILogger<TelemetryDecoderWorker> _logger;

    public TelemetryDecoderWorker(
        ChannelReader<UdpTelemetryPacket> packetReader,
        PacketDecoder packetDecoder,
        VesselStateRegistry vesselStateRegistry,
        TelemetryMetrics metrics,
        ILogger<TelemetryDecoderWorker> logger
    )
    {
        _packetReader = packetReader;
        _packetDecoder = packetDecoder;
        _vesselStateRegistry = vesselStateRegistry;
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
                if (!_packetDecoder.TryDecode(packet, out VesselTelemetry? telemetry, out string? error) ||
                    telemetry is null)
                {
                    _metrics.IncrementBadPacket();

                    _logger.LogWarning(
                        "Rejected malformed telemetry packet. bytes={PacketLength}, sender={SenderEndpoint}, error={Error}",
                        packet.Payload.Length,
                        packet.SenderEndpoint,
                        error
                    );

                    continue;
                }

                _vesselStateRegistry.Upsert(telemetry);
                _metrics.IncrementDecoded();

                _logger.LogInformation(
                    "Decoded vessel telemetry: vesselId={VesselId}, x={X:F2}, y={Y:F2}, speed={Speed:F2}, fuel={Fuel:F2}",
                    telemetry.VesselDisplayId,
                    telemetry.X,
                    telemetry.Y,
                    telemetry.Speed,
                    telemetry.Fuel
                );
            }
        }
        catch (OperationCanceledException) when (stoppingToken.IsCancellationRequested) {
            _logger.LogInformation("Telemetry decoder worker stopping.");
        }
    }
}