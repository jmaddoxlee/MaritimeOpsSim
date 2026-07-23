using MaritimeOps.Ingestion.Telemetry;

namespace MaritimeOps.Ingestion.Tests;

public sealed class VesselStateRegistryTests
{
    [Fact]
    public void RegistryUpdateStoresLatestVesselState()
    {
        VesselStateRegistry registry = new();

        VesselTelemetry first = CreateTelemetry(
            vesselId: "VESSEL-001",
            sequenceNumber: 1,
            x: 10.0,
            receivedAtUtc: DateTimeOffset.UtcNow
        );

        VesselTelemetry second = CreateTelemetry(
            vesselId: "VESSEL-001",
            sequenceNumber: 2,
            x: 20.0,
            receivedAtUtc: DateTimeOffset.UtcNow
        );

        registry.Upsert(first);
        registry.Upsert(second);

        VesselTelemetry latest = registry.GetSnapshot().Single();

        Assert.Equal("VESSEL-001", latest.VesselId);
        Assert.Equal(2UL, latest.SequenceNumber);
        Assert.Equal(20.0, latest.X);
        Assert.Equal(1, registry.TrackedVesselCount);
        Assert.Equal(2, registry.StateUpdateCount);
    }

    [Fact]
    public void StaleStateIsMarkedAfterThreeSeconds()
    {
        VesselStateRegistry registry = new();

        DateTimeOffset nowUtc = DateTimeOffset.UtcNow;

        VesselTelemetry staleTelemetry = CreateTelemetry(
            vesselId: "VESSEL-001",
            sequenceNumber: 1,
            x: 10.0,
            receivedAtUtc: nowUtc.AddSeconds(-4)
        );

        registry.Upsert(staleTelemetry);

        VesselTelemetrySnapshot snapshot =
            registry.GetSnapshotWithStaleStatus(nowUtc).Single();

        Assert.True(snapshot.IsStale);
        Assert.Equal(0, registry.GetActiveVesselCount(nowUtc));
        Assert.Equal(1, registry.GetStaleVesselCount(nowUtc));
    }

    [Fact]
    public void FreshStateIsNotMarkedStale()
    {
        VesselStateRegistry registry = new();

        DateTimeOffset nowUtc = DateTimeOffset.UtcNow;

        VesselTelemetry freshTelemetry = CreateTelemetry(
            vesselId: "VESSEL-001",
            sequenceNumber: 1,
            x: 10.0,
            receivedAtUtc: nowUtc
        );

        registry.Upsert(freshTelemetry);

        VesselTelemetrySnapshot snapshot =
            registry.GetSnapshotWithStaleStatus(nowUtc).Single();

        Assert.False(snapshot.IsStale);
        Assert.Equal(1, registry.GetActiveVesselCount(nowUtc));
        Assert.Equal(0, registry.GetStaleVesselCount(nowUtc));
    }

    private static VesselTelemetry CreateTelemetry(
        string vesselId,
        ulong sequenceNumber,
        double x,
        DateTimeOffset receivedAtUtc
    )
    {
        return new VesselTelemetry(
            SequenceNumber: sequenceNumber,
            TimestampUtc: receivedAtUtc,
            VesselId: vesselId,
            X: x,
            Y: 50.0,
            Speed: 5.0,
            Heading: 0.0,
            Fuel: 99.75,
            SignalStrength: 1.0,
            StatusFlags: 1,
            ReceivedAtUtc: receivedAtUtc
        );
    }
}