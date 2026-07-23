using Google.Protobuf;
using MaritimeOps.Ingestion.Telemetry;
using Microsoft.Extensions.Logging.Abstractions;
using System.Net;
using ProtoVesselTelemetry = MaritimeOps.Contracts.Telemetry.VesselTelemetry;

namespace MaritimeOps.Ingestion.Tests;

public sealed class ProtobufTelemetryPipelineTests
{
    [Fact]
    public void ValidProtobufPacketDecodes()
    {
        ProtoVesselTelemetry protoTelemetry = CreateProtoTelemetry();

        UdpTelemetryPacket packet = CreatePacket(protoTelemetry.ToByteArray());

        ProtobufPacketDecoder decoder = new();

        bool decoded = decoder.TryDecode(
            packet,
            out VesselTelemetry? telemetry,
            out string? error
        );

        Assert.True(decoded);
        Assert.Null(error);
        Assert.NotNull(telemetry);
        Assert.Equal("VESSEL-001", telemetry!.VesselId);
        Assert.Equal(55.0, telemetry.X);
        Assert.Equal(50.0, telemetry.Y);
        Assert.Equal(5.0, telemetry.Speed);
        Assert.Equal(99.75, telemetry.Fuel);
    }

    [Fact]
    public void InvalidPacketIncrementsBadCount()
    {
        TelemetryMetrics metrics = new();
        VesselStateRegistry registry = new();
        ProtobufPacketDecoder decoder = new();

        TelemetryPacketProcessor processor = new(
            decoder,
            registry,
            metrics,
            NullLogger<TelemetryPacketProcessor>.Instance
        );

        UdpTelemetryPacket badPacket = CreatePacket(new byte[] { 0xFF });

        bool processed = processor.Process(badPacket);

        Assert.False(processed);
        Assert.Equal(1, metrics.BadPackets);
        Assert.Equal(0, metrics.DecodedPackets);
        Assert.Equal(0, registry.ActiveVesselCount);
    }

    [Fact]
    public void RegistryUpdatesOnValidPacket()
    {
        TelemetryMetrics metrics = new();
        VesselStateRegistry registry = new();
        ProtobufPacketDecoder decoder = new();

        TelemetryPacketProcessor processor = new(
            decoder,
            registry,
            metrics,
            NullLogger<TelemetryPacketProcessor>.Instance
        );

        ProtoVesselTelemetry protoTelemetry = CreateProtoTelemetry();

        UdpTelemetryPacket packet = CreatePacket(protoTelemetry.ToByteArray());

        bool processed = processor.Process(packet);

        Assert.True(processed);
        Assert.Equal(1, metrics.DecodedPackets);
        Assert.Equal(0, metrics.BadPackets);
        Assert.Equal(1, registry.ActiveVesselCount);
        Assert.Equal(1, registry.StateUpdateCount);

        VesselTelemetry latestState = registry.GetSnapshot().Single();

        Assert.Equal("VESSEL-001", latestState.VesselId);
        Assert.Equal(55.0, latestState.X);
        Assert.Equal(99.75, latestState.Fuel);
    }

    private static ProtoVesselTelemetry CreateProtoTelemetry()
    {
        return new ProtoVesselTelemetry
        {
            VesselId = "VESSEL-001",
            TimestampUnixMs = 1783545600000,
            X = 55.0,
            Y = 50.0,
            Speed = 5.0,
            Heading = 0.0,
            Fuel = 99.75,
            SignalStrength = 1.0,
            StatusFlags = 1,
            SequenceNumber = 1
        };
    }

    private static UdpTelemetryPacket CreatePacket(byte[] payload)
    {
        return new UdpTelemetryPacket(
            payload,
            new IPEndPoint(IPAddress.Loopback, 5005),
            DateTimeOffset.UtcNow
        );
    }
}