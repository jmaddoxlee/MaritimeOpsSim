using System.Collections.Concurrent;

namespace MaritimeOps.Ingestion.Telemetry;

public sealed class VesselStateRegistry
{
    private readonly ConcurrentDictionary<uint, VesselTelemetry> _latestStates = new();

    private long _stateUpdateCount;

    public int ActiveVesselCount => _latestStates.Count;

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
}