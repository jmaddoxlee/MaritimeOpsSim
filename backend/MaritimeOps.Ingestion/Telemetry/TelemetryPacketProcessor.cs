namespace MaritimeOps.Ingestion.Telemetry;

public sealed class TelemetryPacketProcessor
{
    private readonly ProtobufPacketDecoder _packetDecoder;
    private readonly VesselStateRegistry _vesselStateRegistry;
    private readonly TelemetryMetrics _metrics;
    private readonly ILogger<TelemetryPacketProcessor> _logger;

    public TelemetryPacketProcessor(
        ProtobufPacketDecoder packetDecoder,
        VesselStateRegistry vesselStateRegistry,
        TelemetryMetrics metrics,
        ILogger<TelemetryPacketProcessor> logger
    )
    {
        _packetDecoder = packetDecoder;
        _vesselStateRegistry = vesselStateRegistry;
        _metrics = metrics;
        _logger = logger;
    }

    public bool Process(UdpTelemetryPacket packet)
    {
        try
        {
            if (!_packetDecoder.TryDecode(packet, out VesselTelemetry? telemetry, out string? error) ||
                telemetry is null)
            {
                _metrics.IncrementBadPacket();

                _logger.LogWarning(
                    "Rejected malformed Protobuf telemetry packet. bytes={PacketLength}, sender={SenderEndpoint}, error={Error}",
                    packet.Payload.Length,
                    packet.SenderEndpoint,
                    error
                );

                return false;
            }

            _vesselStateRegistry.Upsert(telemetry);
            _metrics.IncrementDecoded();

            _logger.LogInformation(
                "Decoded Protobuf vessel telemetry: vesselId={VesselId}, sequenceNumber={SequenceNumber}, x={X:F2}, y={Y:F2}, speed={Speed:F2}, fuel={Fuel:F2}",
                telemetry.VesselDisplayId,
                telemetry.SequenceNumber,
                telemetry.X,
                telemetry.Y,
                telemetry.Speed,
                telemetry.Fuel
            );

            return true;
        }
        catch (Exception exception)
        {
            _metrics.IncrementBadPacket();

            _logger.LogError(
                exception,
                "Unexpected decoder error. Packet was rejected without crashing the service."
            );

            return false;
        }
    }
}