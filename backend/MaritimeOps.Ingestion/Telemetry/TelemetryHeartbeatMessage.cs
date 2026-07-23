namespace MaritimeOps.Ingestion.Telemetry;

public sealed record TelemetryHeartbeatMessage(
    string Type,
    DateTimeOffset TimestampUtc,
    int ConnectedClientCount
);