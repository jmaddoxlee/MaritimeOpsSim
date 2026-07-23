namespace MaritimeOps.Ingestion.Telemetry;

public sealed record VesselTelemetrySnapshot(
    string VesselId,
    ulong SequenceNumber,
    DateTimeOffset TimestampUtc,
    double X,
    double Y,
    double Speed,
    double Heading,
    double Fuel,
    double SignalStrength,
    uint StatusFlags,
    DateTimeOffset ReceivedAtUtc,
    bool IsStale
);