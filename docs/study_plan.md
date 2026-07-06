# MaritimeOpsSim Study Plan

## Purpose

This study plan supports MaritimeOpsSim as a portfolio-grade distributed maritime telemetry platform.

The goal is to build technical depth for mission software, ground systems, telemetry systems, software test, IoT backend, and distributed systems roles.

---

## Core Study Pillars

### 1. C++ Simulation Core

Focus areas:

- C++20
- CMake
- GoogleTest
- RAII
- Smart pointers
- Move semantics
- Fixed timestep simulation
- Vessel state modeling
- Fleet simulation
- UDP telemetry sender

Project connection:

- `Vessel`
- `VesselState`
- `SimulationEngine`
- `FleetSimulationEngine`
- `MapGrid`
- `ScenarioLoader`

---

### 2. C#/.NET Ingestion Backend

Focus areas:

- UDP sockets
- Background services
- `System.Threading.Channels`
- `ConcurrentDictionary`
- Cancellation tokens
- Packet decoding
- WebSockets
- Unit testing

Project connection:

- `UdpTelemetryReceiver`
- `PacketDecoder`
- `TelemetryChannelWorker`
- `VesselStateRegistry`
- `WebSocketBroadcaster`

---

### 3. Real-Time Frontend Dashboard

Focus areas:

- React
- TypeScript
- WebSockets
- Canvas or MapLibre
- `useRef`
- `requestAnimationFrame`
- High-frequency rendering
- Alert panels
- Connection health display

Project connection:

- `maritime-dashboard`
- Mission map
- Vessel rendering
- Telemetry panel
- Alert panel

---

### 4. Telemetry, Storage, and System Design

Focus areas:

- UDP telemetry
- Protocol Buffers
- Time-series storage
- TimescaleDB
- Latest-state queries
- Historical telemetry queries
- Docker Compose
- GitHub Actions CI

Project connection:

- `proto/vessel_telemetry.proto`
- `database/migrations`
- `database/queries`
- `docker-compose.yml`

---

### 5. Testing, Fault Injection, and Linux Operations

Focus areas:

- Pytest
- Corrupt packet testing
- Packet flood testing
- Disconnect testing
- Stale vessel detection
- `tcpdump`
- `ss`
- `netstat`
- `top`
- `htop`

Project connection:

- `python/control`
- Backend resilience tests
- Integration tests
- Failure-mode documentation

---

## Current Next Focus

The next implementation focus is:

Phase 1 — C++ Fleet Simulation and UDP Telemetry

Immediate study targets:

- Runtime vessel state modeling
- 100-vessel simulation
- Fixed timestep loop
- Fuel burn model
- UDP packet basics
- Telemetry packet structure
- GoogleTest coverage
