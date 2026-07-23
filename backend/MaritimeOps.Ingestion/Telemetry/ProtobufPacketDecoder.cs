using Google.Protobuf;
using ProtoVesselTelemetry = MaritimeOps.Contracts.Telemetry.VesselTelemetry;

namespace MaritimeOps.Ingestion.Telemetry;

public sealed class ProtobufPacketDecoder
{
    public bool TryDecode(
        UdpTelemetryPacket packet,
        out VesselTelemetry? telemetry,
        out string? error
    )
    {
        telemetry = null;
        error = null;

        try
        {
            ProtoVesselTelemetry protoTelemetry =
                ProtoVesselTelemetry.Parser.ParseFrom(packet.Payload);

            if (string.IsNullOrWhiteSpace(protoTelemetry.VesselId))
            {
                error = "Missing vessel_id.";
                return false;
            }

            DateTimeOffset timestampUtc =
                ConvertUnixMilliseconds(protoTelemetry.TimestampUnixMs);

            telemetry = new VesselTelemetry(
                protoTelemetry.SequenceNumber,
                timestampUtc,
                protoTelemetry.VesselId,
                protoTelemetry.X,
                protoTelemetry.Y,
                protoTelemetry.Speed,
                protoTelemetry.Heading,
                protoTelemetry.Fuel,
                protoTelemetry.SignalStrength,
                protoTelemetry.StatusFlags,
                packet.ReceivedAtUtc
            );

            return true;
        }
        catch (Exception exception)
        {
            error = exception.Message;
            return false;
        }
    }

    private static DateTimeOffset ConvertUnixMilliseconds(ulong timestampUnixMs)
    {
        if (timestampUnixMs > long.MaxValue)
        {
            return DateTimeOffset.UnixEpoch;
        }

        return DateTimeOffset.FromUnixTimeMilliseconds((long)timestampUnixMs);
    }
}