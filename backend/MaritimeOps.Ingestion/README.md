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

The backend has been upgraded from a basic UDP listener into a structured telemetry ingestion pipeline.

Current implementation includes:

- ASP.NET Core application startup
- `UdpTelemetryReceiver` background service
- UDP bind on port `5005`
- Raw UDP packet receive loop
- `System.Threading.Channels` producer-consumer pipeline
- `PacketDecoder` for temporary 72-byte binary packet decoding
- `VesselTelemetry` structured telemetry model
- `VesselStateRegistry` for latest vessel state storage
- `ConcurrentDictionary` for thread-safe vessel state updates
- `TelemetryMetrics` for packet counters
- `TelemetryMetricsReporter` for packets-per-second logs
- Basic root endpoint
- Basic health endpoint
- Metrics endpoint
- Latest vessel state endpoint

Current UDP telemetry flow:

```text
C++ FleetTelemetrySimulation
    ↓ UDP 127.0.0.1:5005
UdpTelemetryReceiver
    ↓ writes UdpTelemetryPacket into channel
System.Threading.Channels
    ↓ reads packet
TelemetryDecoderWorker
    ↓ decodes binary packet
PacketDecoder
    ↓ creates structured telemetry
VesselTelemetry
    ↓ stores latest vessel state
VesselStateRegistry
```
