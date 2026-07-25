## Fuel Model

The fleet simulation includes a simple deterministic fuel model.

Each active vessel burns fuel during every simulation update based on its current speed and the elapsed simulation time.

Current formula:

```text
fuelBurn = speed * deltaTimeSeconds * fuelBurnRate
```

The current fuel burn rate is:

```text
fuelBurnRate = 0.05
```

This means faster vessels consume more fuel than slower vessels, and longer update intervals consume more fuel than shorter update intervals.

Example:

```text
speed = 10.0
deltaTimeSeconds = 2.0
fuelBurnRate = 0.05

fuelBurn = 10.0 * 2.0 * 0.05
fuelBurn = 1.0
```

If the vessel starts with:

```text
fuel = 100.0
```

then after one update:

```text
fuel = 99.0
```

Fuel is clamped so it never drops below zero.

```text
fuel = max(0.0, fuel - fuelBurn)
```

If a vessel has no fuel remaining, the simulation keeps its fuel at `0.0` and does not continue burning negative fuel.

Inactive vessels do not move and do not burn fuel.

This fuel model is intentionally simple for the current milestone. Its purpose is to create predictable telemetry values that can be tested, displayed, and transmitted through the future UDP telemetry pipeline.

Later versions may replace this with a more realistic model that considers vessel type, acceleration, load, sea conditions, or mission behavior.

# System Design

## Backend Architecture

The backend is designed as an asynchronous telemetry ingestion and broadcast service.

Current backend flow:

```text
C++ Protobuf UDP Sender
    ↓ UDP 127.0.0.1:5005
UdpTelemetryReceiver
    ↓ writes UdpTelemetryPacket
System.Threading.Channels
    ↓ reads packet
TelemetryDecoderWorker
    ↓
TelemetryPacketProcessor
    ↓
ProtobufPacketDecoder
    ↓
VesselTelemetry
    ↓
VesselStateRegistry
    ↓
WebSocketTelemetryBroadcaster
    ↓
Browser / dashboard clients
```

## Frontend Rendering Performance

The React dashboard is designed to handle live vessel telemetry without forcing React to re-render on every incoming message.

Current rendering strategy:

```text
WebSocket message
    ↓
parse telemetry snapshot
    ↓
write vessel data into useRef store
    ↓
Canvas reads latest vessel state during requestAnimationFrame
    ↓
React state updates only at low frequency for UI counters
```
