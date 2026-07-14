using System.Net;

namespace MaritimeOps.Ingestion.Telemetry;

public sealed record UdpTelemetryPacket(
    byte[] Payload,
    IPEndPoint SenderEndpoint,
    DateTimeOffset ReceivedAtUtc
);