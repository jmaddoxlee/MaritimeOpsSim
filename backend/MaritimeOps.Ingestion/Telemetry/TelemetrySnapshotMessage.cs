namespace MaritimeOps.Ingestion.Telemetry;

public sealed record TelemetrySnapshotMessage(
    string Type,
    DateTimeOffset TimestampUtc,
    int ActiveVesselCount,
    int StaleVesselCount,
    IReadOnlyCollection<VesselTelemetrySnapshot> Vessels
);