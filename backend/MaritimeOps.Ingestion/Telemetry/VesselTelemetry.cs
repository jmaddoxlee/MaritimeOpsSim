namespace MaritimeOps.Ingestion.Telemetry;

public sealed record VesselTelemetry(
    ulong SequenceNumber,
    DateTimeOffset TimestampUtc,
    uint VesselId,
    double X,
    double Y,
    double Speed,
    double Heading,
    double Fuel,
    double SignalStrength,
    uint StatusFlags,
    DateTimeOffset ReceivedAtUtc
)
{
    public string VesselDisplayId => $"VESSEL-{VesselId:000}";
}