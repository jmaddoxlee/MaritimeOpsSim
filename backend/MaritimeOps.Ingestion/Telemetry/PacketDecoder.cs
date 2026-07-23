using System.Buffers.Binary;

namespace MaritimeOps.Ingestion.Telemetry;

public sealed class PacketDecoder
{
    public const int ExpectedPacketSizeBytes = 72;

    public bool TryDecode(
        UdpTelemetryPacket packet,
        out VesselTelemetry? telemetry,
        out string? error
    )
    {
        telemetry = null;
        error = null;

        ReadOnlySpan<byte> payload = packet.Payload;

        if (payload.Length != ExpectedPacketSizeBytes)
        {
            error = $"Expected {ExpectedPacketSizeBytes} bytes but received {payload.Length} bytes.";
            return false;
        } 

        try
        {
            ulong sequenceNumber = BinaryPrimitives.ReadUInt64LittleEndian(
                payload.Slice(0, 8)
            );

            ulong timestampUnixMs = BinaryPrimitives.ReadUInt64LittleEndian(
                payload.Slice(8, 8)
            );

            uint vesselId = BinaryPrimitives.ReadUInt32LittleEndian(
                payload.Slice(16, 4)
            );

            double x = ReadDoubleLittleEndian(payload, 20);
            double y = ReadDoubleLittleEndian(payload, 28);
            double speed = ReadDoubleLittleEndian(payload, 36);
            double heading = ReadDoubleLittleEndian(payload, 44);
            double fuel = ReadDoubleLittleEndian(payload, 52);
            double signalStrength = ReadDoubleLittleEndian(payload, 60);

            uint statusFlags = BinaryPrimitives.ReadUInt32LittleEndian(
                payload.Slice(68, 4)
            );

            DateTimeOffset timestampUtc = ConvertUnixMilliseconds(timestampUnixMs);

            telemetry = new VesselTelemetry(
                sequenceNumber,
                timestampUtc,
                $"VESSEL-{vesselId:000}",
                x,
                y,
                speed,
                heading,
                fuel,
                signalStrength,
                statusFlags,
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

    private static double ReadDoubleLittleEndian(
        ReadOnlySpan<byte> payload,
        int offset
    )
    {
        long rawValue = BinaryPrimitives.ReadInt64LittleEndian(
            payload.Slice(offset, 8)
        );

        return BitConverter.Int64BitsToDouble(rawValue);
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