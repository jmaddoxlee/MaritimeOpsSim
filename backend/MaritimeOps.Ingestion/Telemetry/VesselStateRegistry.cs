using System.Collections.Concurrent;

namespace MaritimeOps.Ingestion.Telemetry;

public sealed class VesselStateRegistry
{
    private static readonly TimeSpan DefaultStaleThreshold = TimeSpan.FromSeconds(3);

    private readonly ConcurrentDictionary<string, VesselTelemetry> _latestStates = new();

    private long _stateUpdateCount;

    public int TrackedVesselCount => _latestStates.Count;

    public int ActiveVesselCount => GetActiveVesselCount(DateTimeOffset.UtcNow);

    public long StateUpdateCount => Interlocked.Read(ref _stateUpdateCount);

    public void Upsert(VesselTelemetry telemetry)
    {
        _latestStates.AddOrUpdate(
            telemetry.VesselId,
            telemetry,
            (_, _) => telemetry
        );

        Interlocked.Increment(ref _stateUpdateCount);
    }

    public IReadOnlyCollection<VesselTelemetry> GetSnapshot()
    {
        return _latestStates.Values
            .OrderBy(vessel => vessel.VesselId)
            .ToArray();
    }

    public IReadOnlyCollection<VesselTelemetrySnapshot> GetSnapshotWithStaleStatus(
        DateTimeOffset nowUtc
    )
    {
        return _latestStates.Values
            .OrderBy(vessel => vessel.VesselId)
            .Select(vessel => ToSnapshot(vessel, nowUtc, DefaultStaleThreshold))
            .ToArray();
    }

    public int GetActiveVesselCount(DateTimeOffset nowUtc)
    {
        return GetSnapshotWithStaleStatus(nowUtc)
            .Count(vessel => !vessel.IsStale);
    }

    public int GetStaleVesselCount(DateTimeOffset nowUtc)
    {
        return GetSnapshotWithStaleStatus(nowUtc)
            .Count(vessel => vessel.IsStale);
    }

    private static VesselTelemetrySnapshot ToSnapshot(
        VesselTelemetry telemetry,
        DateTimeOffset nowUtc,
        TimeSpan staleThreshold
    )
    {
        bool isStale = nowUtc - telemetry.ReceivedAtUtc > staleThreshold;

        return new VesselTelemetrySnapshot(
            telemetry.VesselId,
            telemetry.SequenceNumber,
            telemetry.TimestampUtc,
            telemetry.X,
            telemetry.Y,
            telemetry.Speed,
            telemetry.Heading,
            telemetry.Fuel,
            telemetry.SignalStrength,
            telemetry.StatusFlags,
            telemetry.ReceivedAtUtc,
            isStale
        );
    }
}