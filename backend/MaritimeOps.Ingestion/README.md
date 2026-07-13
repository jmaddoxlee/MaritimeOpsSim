# MaritimeOps.Ingestion

## Purpose

MaritimeOps.Ingestion is the planned C#/.NET telemetry ingestion backend for MaritimeOpsSim.

This service will receive telemetry from the C++ simulation layer, decode telemetry packets, maintain latest vessel state, broadcast live updates to the frontend dashboard, and eventually persist telemetry to TimescaleDB.

---

## Planned Responsibilities

The backend will:

- Listen for UDP telemetry packets
- Decode binary or Protocol Buffers telemetry
- Reject malformed packets safely
- Track received, decoded, dropped, and bad packet counts
- Use `System.Threading.Channels` for packet processing
- Maintain latest vessel state using a thread-safe registry
- Detect stale vessel updates
- Broadcast live state over WebSockets
- Persist telemetry to TimescaleDB
- Expose basic health and metrics information

---

## Planned Main Components

| Component                  | Responsibility                                         |
| -------------------------- | ------------------------------------------------------ |
| `UdpTelemetryReceiver`     | Receives telemetry packets from the C++ simulator      |
| `PacketDecoder`            | Decodes binary or Protobuf telemetry packets           |
| `TelemetryChannelWorker`   | Processes packets through a producer-consumer pipeline |
| `VesselStateRegistry`      | Stores latest state for each vessel                    |
| `TelemetryMetrics`         | Tracks packet and processing metrics                   |
| `WebSocketBroadcaster`     | Sends live telemetry snapshots to dashboard clients    |
| `TimescaleTelemetryWriter` | Writes telemetry history to TimescaleDB                |

---

## Initial Development Goal

The first backend goal is to create a .NET service that can:

1. Start successfully
2. Listen on UDP port `5005`
3. Receive a test packet
4. Decode or log the packet
5. Avoid crashing on malformed packets

---

## Current Implementation

The first backend skeleton has been created as an ASP.NET Core service.

Current implementation includes:

- ASP.NET Core application startup
- `UdpTelemetryReceiver` background service
- UDP bind on port `5005`
- Raw packet receive loop
- Packet length logging
- Sender endpoint logging
- Basic root endpoint
- Basic health endpoint

Current UDP test flow:

```text
C++ FleetTelemetrySimulation
    ↓ UDP 127.0.0.1:5005
C# MaritimeOps.Ingestion
    ↓
UdpTelemetryReceiver
    ↓
Console logs packet length and sender endpoint
```
