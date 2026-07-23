# MaritimeOpsSim

## Distributed Maritime Command & Telemetry Platform

MaritimeOpsSim is a safe distributed maritime simulation and telemetry platform focused on search-and-rescue, maritime domain awareness, vessel telemetry, mission coordination, real-time dashboard visualization, time-series persistence, automated fault-injection testing, and resilient distributed systems.

The project started as a C++/Raylib unmanned surface vessel simulator and is now being expanded into a multi-layer distributed telemetry platform.

---

## Safe-Scope Disclaimer

This project is a safe software engineering portfolio project focused on simulated maritime search-and-rescue, maritime domain awareness, telemetry processing, command-dashboard visualization, mission monitoring, fault tolerance, and system reliability.

This project does **not** include weapon targeting, missile guidance, strike planning, combat engagement, fire-control logic, attack optimization, enemy engagement, or real-world tactical recommendations.

The project should be described publicly as a **command-and-telemetry platform**, **mission monitoring platform**, or **distributed maritime telemetry platform**.

---

## Project Goal

The goal of MaritimeOpsSim is to build a portfolio-grade distributed maritime telemetry system that demonstrates skills relevant to:

- Ground Software Engineer
- Ground Systems Software Engineer
- Mission Software Engineer
- C2 Software Engineer
- Tactical Software Engineer
- Software Test Engineer
- Telemetry Software Engineer
- IoT Backend Engineer
- IoT Platform Engineer
- Distributed Systems Engineer
- HIL Test Software Engineer
- Industrial IoT / Smart Grid Software Engineer
- Public Safety Technology Software Engineer
- High-Performance Networking Software Engineer

This project is designed to show more than basic web application development. It demonstrates C++ systems programming, simulation, networking, telemetry ingestion, distributed architecture, frontend performance, time-series persistence, automated testing, Linux operations, CI/CD, and professional software documentation.

---

## Updated High-Level Architecture

```text
Scenario JSON
    ↓
C++ Simulation Layer
    - Fleet simulation
    - Vessel physics loop
    - Position, heading, speed, fuel, signal state
    - UDP telemetry emitter
    ↓
UDP / Protobuf Telemetry
    ↓
C#/.NET Ingestion Layer
    - UDP listener
    - Protocol Buffers decoder
    - System.Threading.Channels pipeline
    - Vessel state registry
    - WebSocket broadcaster
    - TimescaleDB writer
    ↓
WebSocket Stream
    ↓
React + TypeScript Presentation Layer
    - Live mission dashboard
    - Canvas or MapLibre rendering
    - 100 moving vessel icons
    - Telemetry panel
    - Alerts and connection health
    ↓
Python Test & Control Layer
    - Launch automation
    - Corrupt packet injection
    - Socket disconnect tests
    - Performance monitoring
    - Pytest verification
    ↓
Docker / Linux Runtime
    - Multi-container local deployment
    - CI-ready architecture
```

---

## Updated Tech Stack

| Layer                  | Technology                | Purpose                                             |
| ---------------------- | ------------------------- | --------------------------------------------------- |
| Simulation             | C++20                     | High-performance vessel simulation and physics loop |
| Build                  | CMake                     | C++ build system                                    |
| Desktop Visual Demo    | Raylib                    | Local 2D simulation visualization                   |
| Data Contract          | Protocol Buffers          | Binary telemetry schema across C++ and C#           |
| Network Transport      | UDP                       | C++ simulation to backend telemetry stream          |
| Ingestion Backend      | C# / .NET                 | High-performance telemetry receiver and router      |
| Concurrency            | System.Threading.Channels | Producer-consumer ingestion pipeline                |
| Backend State Registry | ConcurrentDictionary      | Latest vessel state registry                        |
| Live Stream            | WebSockets                | Backend to browser real-time updates                |
| Frontend               | React + TypeScript        | Mission-control dashboard                           |
| Map Rendering          | MapLibre GL JS or Canvas  | Live vessel visualization                           |
| Persistence            | TimescaleDB               | Time-series telemetry storage                       |
| Message Broker         | Kafka                     | Optional future event streaming layer               |
| Test Automation        | Python + Pytest           | Chaos, integration, and control tests               |
| Runtime                | Linux + Docker Compose    | Reproducible multi-service environment              |
| CI/CD                  | GitHub Actions            | Build, test, and verification pipeline              |

---

## Why Raylib Is Still Used

Raylib remains part of the project as the **local C++ visual demo and debugging viewer**.

Raylib is used for:

- Local desktop visualization
- Debugging vessel movement
- Showing the scenario map
- Drawing waypoints, obstacles, restricted zones, and distress beacon
- Demonstrating C++ graphics and simulation work

The main distributed dashboard will be built with:

```text
React + TypeScript
```

So the final project uses both:

```text
Raylib = local C++ simulation viewer
React + TypeScript = real-time distributed telemetry dashboard
```

---

## Completed Progress

### Week 1 — Setup, Requirements, and Architecture

Completed:

- Created repository
- Created folder structure
- Created README
- Defined initial project goal
- Added safe-scope disclaimer
- Created initial architecture direction

---

### Week 2 — Core C++ Simulation Engine

Completed:

- Created initial `Vessel` class
- Added vessel ID, position, speed, and heading
- Added vessel movement update logic
- Created initial `Mission` class
- Added mission name, type, status, and elapsed time
- Created initial `SimulationEngine` class
- Connected `SimulationEngine`, `Mission`, and `Vessel`
- Added basic time-stepped simulation loop
- Added console telemetry output
- Added GoogleTest setup
- Wrote first vessel movement test

---

### Week 3 — Scenario Loader and Map System

Completed:

- Created `search_rescue_demo.json`
- Added structured scenario data models
- Loaded mission data from JSON
- Loaded map data from JSON
- Loaded vessel data from JSON
- Loaded waypoint data from JSON
- Loaded obstacle data from JSON
- Loaded restricted zone data from JSON
- Loaded distress beacon data from JSON
- Loaded mission rule descriptions from JSON
- Added `ScenarioLoader`
- Added scenario validation and useful error messages
- Added invalid scenario fixture
- Added ScenarioLoader tests
- Added basic `MapGrid` model
- Added bounds, obstacle, and restricted-zone checks

---

### Week 4 — Basic Raylib Visual Demo

Completed:

- Added `MaritimeOpsSimVisual` executable
- Added Raylib rendering window
- Drew mission map
- Drew vessel position
- Drew waypoints
- Drew obstacles
- Drew restricted zones
- Drew distress beacon
- Added telemetry panel
- Added mission timer
- Added basic status text
- Added screenshot capture
- Recorded first visual demo clip

---

### Week 5 — Fleet Simulation and UDP Telemetry

Completed:

- Added `VesselState` runtime model for live fleet state
- Added `FleetSimulationEngine` to update multiple vessels per tick
- Added deterministic position and fuel updates
- Added sample fleet generation for 100 vessels
- Added headless fleet simulation mode
- Added `TelemetryPacketBuilder` for fixed-size binary telemetry packets
- Added packet sequence number generation
- Added timestamp generation using `std::chrono`
- Added status flags for active, low fuel, and degraded signal states
- Added `UdpTelemetrySender` for UDP packet transmission
- Added UDP smoke test app that sends one packet to localhost
- Added fleet telemetry simulation app that sends one packet per vessel per tick
- Added silent simulation mode using `--silent` or `-s`
- Added packet builder tests for packet size, vessel ID, status flags, sequence number, and timestamp
- Added fleet tests for generated fleet size and unique vessel IDs
- Added fuel model explanation to system design documentation

Temporary binary telemetry packet layout:

```text
sequence number       8 bytes
timestamp             8 bytes
vessel numeric ID     4 bytes
x                     8 bytes
y                     8 bytes
speed                 8 bytes
heading               8 bytes
fuel                  8 bytes
signal strength       8 bytes
status flags          4 bytes
```

Current Week 5 telemetry flow:

```text
FleetSimulationEngine
    ↓
VesselState
    ↓
TelemetryPacketBuilder
    ↓
UdpTelemetrySender
    ↓
127.0.0.1:5005
```

---

### Week 6 — CLI Validation and UDP Simulation Run

Completed:

- Added basic command-line option planning for the fleet telemetry simulation
- Added `--headless` option for explicit terminal-only simulation mode
- Added `--vessels <count>` option to configure fleet size from the command line
- Added fallback defaults for invalid or missing CLI values
- Verified C++ build with CMake
- Ran full GoogleTest test suite
- Ran UDP fleet telemetry simulation for 60 seconds
- Captured test output and UDP simulation output under `docs/logs/`

Validation commands:

```bash
ctest --output-on-failure
./FleetTelemetrySimulation --headless --vessels 100
```

Expected simulation scale:

```text
100 vessels
1 packet per vessel per second
60 seconds
6,000 UDP packets total
432,000 raw telemetry payload bytes
```

Terminal log artifacts:

```text
docs/logs/week6_test_output.log
docs/logs/week6_udp_simulation_output.log
```

Current Week 6 flow:

```text
Command-line options
    ↓
FleetSimulationEngine
    ↓
TelemetryPacketBuilder
    ↓
UdpTelemetrySender
    ↓
127.0.0.1:5005
```

---

### Week 7 — C# UDP Ingestion Pipeline

Completed:

- Created `MaritimeOps.Ingestion` C#/.NET backend service
- Added ASP.NET Core application startup
- Added `UdpTelemetryReceiver` background service
- Bound backend UDP receiver to port `5005`
- Added `UdpTelemetryPacket` model for raw UDP payloads
- Added `System.Threading.Channels` producer-consumer pipeline
- Added `TelemetryDecoderWorker` background worker
- Added `TelemetryMetrics` packet counters
- Added `TelemetryMetricsReporter` packets-per-second logs
- Added clean shutdown using `CancellationToken`
- Added basic `/health` endpoint
- Added `/metrics` endpoint
- Confirmed C++ UDP simulation can send packets to the C# backend
- Confirmed backend receives UDP packets from the C++ sender
- Confirmed received packet size is 72 bytes for the temporary binary format

Current Week 7 flow:

```text
C++ FleetTelemetrySimulation
    ↓ UDP 127.0.0.1:5005
C# UdpTelemetryReceiver
    ↓
System.Threading.Channels
    ↓
TelemetryDecoderWorker
    ↓
TelemetryMetricsReporter
```

Expected backend metric log:

```text
Telemetry metrics: receivedPerSecond=100, decodedPerSecond=100, totalReceived=100, totalDecoded=100, badPackets=0, droppedPackets=0
```

---

### Week 8 — Protobuf Telemetry Contract and Cross-Language Decoding

Completed:

- Finalized `proto/vessel_telemetry.proto`
- Added Protobuf telemetry contract with:
  - `vessel_id`
  - `timestamp_unix_ms`
  - `x`
  - `y`
  - `speed`
  - `heading`
  - `fuel`
  - `signal_strength`
  - `status_flags`
  - `sequence_number`

- Added C# Protobuf code generation through `Google.Protobuf` and `Grpc.Tools`
- Added C++ Protobuf code generation through CMake and `protobuf_generate_cpp`
- Added generated C++ Protobuf source to `MaritimeOpsSimCore`
- Linked C++ project against `protobuf::libprotobuf`
- Added `ProtobufTelemetryPacketBuilder` in C++
- Added `FleetProtobufTelemetrySimulation` executable
- Serialized one `VesselTelemetry` Protobuf packet in C++
- Printed serialized Protobuf payload size
- Sent Protobuf UDP payloads from C++ to C#
- Added `ProtobufPacketDecoder` in C#
- Added structured C# `VesselTelemetry` model
- Added `VesselStateRegistry`
- Used `ConcurrentDictionary` to store latest state per vessel
- Added `TelemetryPacketProcessor`
- Added structured Protobuf logs:
  - vessel ID
  - sequence number
  - x
  - y
  - speed
  - fuel

- Added bad packet handling
- Added `badPacketCount`
- Added try/catch around decoder path
- Confirmed invalid bytes do not crash the backend
- Added C# tests for:
  - valid Protobuf packet decode
  - invalid packet increments bad count
  - registry updates on valid packet

- Updated `docs/telemetry_contract.md`
- Ran end-to-end C++ Protobuf UDP sender to C# receiver demo

Current Week 8 flow:

```text
FleetSimulationEngine
    ↓
VesselState
    ↓
ProtobufTelemetryPacketBuilder
    ↓
serialized Protobuf VesselTelemetry bytes
    ↓ UDP 127.0.0.1:5005
UdpTelemetryReceiver
    ↓
System.Threading.Channels
    ↓
TelemetryDecoderWorker
    ↓
TelemetryPacketProcessor
    ↓
ProtobufPacketDecoder
    ↓
VesselTelemetry model
    ↓
VesselStateRegistry
```

Expected structured backend log:

```text
Decoded Protobuf vessel telemetry: vesselId=VESSEL-001, sequenceNumber=1, x=55.00, y=50.00, speed=5.00, fuel=99.75
```

Expected metric log:

```text
Telemetry metrics: packetsPerSecond=100, decodedPerSecond=100, packetCount=6000, decodedPacketCount=6000, badPacketCount=0, droppedPacketCount=0, activeVesselCount=100
```

---

## Week 9 — WebSocket Broadcast Layer

Week 9 adds the first live backend-to-client streaming layer.

Current backend architecture:

````text
UDP receiver
    ↓
Channel
    ↓
Decoder
    ↓
Registry
    ↓
WebSocket broadcaster

## New Distributed Platform Roadmap

### Phase 0 — Rebrand and Architecture Reset

Goal:

Update README, documentation, folders, architecture, and project scope before distributed systems coding.

Deliverables:

- `docs/architecture.md`
- `docs/safe_scope.md`
- `docs/telemetry_contract.md`
- `docs/study_plan.md`
- `proto/vessel_telemetry.proto`
- `backend/MaritimeOps.Ingestion/`
- `frontend/maritime-dashboard/`
- `database/migrations/`
- `database/queries/`
- `python/control/`
- `docker-compose.yml`

Status:

```text
Mostly complete
````

---

### Phase 1 — C++ Fleet Simulation and UDP Telemetry

Goal:

Upgrade from one visual vessel to a headless fleet simulation that can produce telemetry for 100 vessels.

Build:

- `VesselState` runtime model
- `FleetSimulationEngine`
- 100 simulated vessels
- Fixed timestep loop
- Fuel burn model
- Heading and velocity updates
- Signal strength state
- Headless simulation mode
- UDP telemetry sender
- Temporary binary payload
- Protobuf payload

Status:

```text
Complete
```

---

### Phase 2 — C#/.NET Ingestion Engine

Goal:

Build the backend service that receives, decodes, and routes C++ telemetry.

Build:

- `UdpTelemetryReceiver`
- `PacketDecoder`
- `ProtobufPacketDecoder`
- `VesselStateRegistry`
- `Channel<UdpTelemetryPacket>` ingestion pipeline
- Background worker services
- Structured console logs
- Packet counters
- Dropped packet counters
- Bad packet handling
- WebSocket broadcaster

Status:

```text
In progress
```

Completed so far:

- UDP receiver
- Channel pipeline
- Decoder worker
- Metrics reporter
- Protobuf decoder
- Vessel state registry
- Bad packet handling
- HTTP health and metrics endpoints

Remaining:

- WebSocket broadcaster
- Dashboard-facing DTOs
- Stale vessel detection
- Integration test automation

---

### Phase 3 — Protobuf Telemetry Contract

Goal:

Create a stable binary telemetry contract between C++ and C#.

Build:

- `proto/vessel_telemetry.proto`
- C++ generated telemetry types
- C# generated telemetry types
- C++ serializer
- C# decoder
- Valid packet tests
- Invalid packet tests

Status:

```text
Complete
```

---

### Phase 4 — React Mission Dashboard

Goal:

Display 100 moving vessels smoothly in a browser dashboard.

Build:

- React + TypeScript dashboard
- WebSocket client
- Canvas or MapLibre map
- Vessel icon rendering
- Telemetry side panel
- Connection status
- Alert list
- `useRef`-based fast telemetry store
- `requestAnimationFrame` render loop

Status:

```text
Not started
```

---

### Phase 5 — TimescaleDB Telemetry Persistence

Goal:

Save telemetry history and query it efficiently.

Build:

- TimescaleDB container
- `vessel_telemetry` table
- Hypertable
- Backend database writer
- Latest vessel query
- Average speed query
- Fuel trend query
- Database integration tests

Status:

```text
Not started
```

---

### Phase 6 — Python Test and Control Layer

Goal:

Prove system resilience through fault injection and integration testing.

Build:

- `launch_cpp_sim.py`
- `launch_backend.py`
- `packet_fuzzer.py`
- `corrupt_packet_sender.py`
- `disconnect_test.py`
- `performance_monitor.py`
- `socket_flood_test.py`
- `stale_vessel_test.py`

Status:

```text
Not started
```

---

### Phase 7 — Docker, Linux, CI, and Portfolio Polish

Goal:

Turn the project into a portfolio-grade distributed system.

Build:

- `docker-compose.yml`
- C++ simulation container
- C# backend container
- React frontend container
- TimescaleDB container
- Python test-runner container
- GitHub Actions CI
- Architecture diagram
- Performance report
- Failure-mode document
- Demo video
- Resume bullets
- Interview script

Status:

```text
Not started
```

---

## Target End-to-End Demo

The final distributed demo should prove this flow:

```text
C++ fleet simulation
    ↓ UDP / Protobuf
C#/.NET ingestion backend
    ↓ WebSocket
React + TypeScript dashboard
    ↓
TimescaleDB telemetry history
    ↓
Python chaos and integration tests
```

---

## Repository Structure

```text
MaritimeOpsSim/
│
├── cpp/
│   ├── src/
│   ├── include/
│   ├── apps/
│   └── tests/
│
├── proto/
│   └── vessel_telemetry.proto
│
├── backend/
│   ├── MaritimeOps.Ingestion/
│   └── MaritimeOps.Ingestion.Tests/
│
├── frontend/
│   └── maritime-dashboard/
│
├── database/
│   ├── migrations/
│   └── queries/
│
├── python/
│   ├── control/
│   └── tests/
│
├── scenarios/
│
├── assets/
│   ├── screenshots/
│   └── demo/
│
├── docs/
│   ├── telemetry_contract.md
│   └── logs/
│
├── scripts/
│
├── .github/
│   └── workflows/
│
├── CMakeLists.txt
├── MaritimeOps.slnx
├── README.md
└── LICENSE
```

---

## How to Build Current C++ Project

```bash
mkdir -p build
cd build
cmake ..
cmake --build .
```

---

## How to Build Current C# Backend

From the repository root:

```bash
dotnet build MaritimeOps.slnx
```

---

## How to Run Current Console Demo

```bash
cd build
./MaritimeOpsSim
```

---

## How to Run Current Raylib Visual Demo

```bash
cd build
./MaritimeOpsSimVisual
```

---

## How to Run Temporary Binary UDP Simulation

This runs the older temporary binary packet sender.

```bash
cd build
./FleetTelemetrySimulation --headless --vessels 100
```

---

## How to Run Protobuf UDP Simulation

This runs the current Protobuf packet sender.

```bash
cd build
./FleetProtobufTelemetrySimulation --vessels 5
```

For a full 100-vessel run:

```bash
cd build
./FleetProtobufTelemetrySimulation --vessels 100
```

Expected C++ output:

```text
Fleet Protobuf Telemetry Simulation
endpoint=127.0.0.1:5005
vessels=5
durationSeconds=60
deltaTimeSeconds=1

protobufSerializedBytes=...
tick=1 packetsSent=5 packetsFailed=0
```

---

## How to Run C# Backend

From the repository root:

```bash
dotnet run --project backend/MaritimeOps.Ingestion
```

Expected backend startup:

```text
UDP telemetry receiver listening on port 5005
Telemetry decoder worker started.
Application started. Press Ctrl+C to shut down.
```

Use the ASP.NET Core port printed in the backend terminal.

Example:

```text
Now listening on: http://localhost:5048
```

---

## How to Run Current End-to-End Protobuf Demo

Terminal 1 — start the C# backend:

```bash
cd /Users/jasonlee/MaritimeOpsSim
dotnet run --project backend/MaritimeOps.Ingestion
```

Terminal 2 — start the C++ Protobuf sender:

```bash
cd /Users/jasonlee/MaritimeOpsSim/build
./FleetProtobufTelemetrySimulation --vessels 5
```

Expected backend structured log:

```text
Decoded Protobuf vessel telemetry: vesselId=VESSEL-001, sequenceNumber=1, x=55.00, y=50.00, speed=5.00, fuel=99.75
```

Expected backend metrics log:

```text
Telemetry metrics: packetsPerSecond=5, decodedPerSecond=5, packetCount=5, decodedPacketCount=5, badPacketCount=0, droppedPacketCount=0, activeVesselCount=5
```

For a full run:

```bash
cd /Users/jasonlee/MaritimeOpsSim/build
./FleetProtobufTelemetrySimulation --vessels 100
```

Expected full-run totals after 60 seconds:

```text
packetCount ≈ 6000
decodedPacketCount ≈ 6000
badPacketCount = 0
activeVesselCount = 100
```

---

## Backend HTTP Endpoints

Use the actual ASP.NET Core port printed in the backend terminal.

Health check:

```bash
curl http://localhost:5048/health
```

Metrics:

```bash
curl http://localhost:5048/metrics
```

Latest vessel states:

```bash
curl http://localhost:5048/vessels
```

Expected metrics response example:

```json
{
  "receivedPackets": 6000,
  "receivedBytes": 432000,
  "queuedPackets": 6000,
  "decodedPackets": 6000,
  "badPackets": 0,
  "droppedPackets": 0,
  "activeVesselCount": 100,
  "stateUpdateCount": 6000
}
```

---

## How to Run C++ Tests

```bash
cd build
ctest --output-on-failure
```

---

## How to Run C# Tests

From the repository root:

```bash
dotnet test MaritimeOps.slnx
```

Current backend tests cover:

- Valid Protobuf packet decodes
- Invalid Protobuf packet increments bad packet count
- Registry updates on valid packet

---

## Telemetry Contract

The current cross-language telemetry contract is defined in:

```text
proto/vessel_telemetry.proto
```

Current Protobuf schema:

```proto
syntax = "proto3";

package maritimeops.telemetry;

option csharp_namespace = "MaritimeOps.Contracts.Telemetry";

message VesselTelemetry {
  string vessel_id = 1;
  uint64 timestamp_unix_ms = 2;
  double x = 3;
  double y = 4;
  double speed = 5;
  double heading = 6;
  double fuel = 7;
  double signal_strength = 8;
  uint32 status_flags = 9;
  uint64 sequence_number = 10;
}
```

Detailed telemetry contract documentation is available in:

```text
docs/telemetry_contract.md
```

---

## Current Status

MaritimeOpsSim currently has:

- C++ simulation foundation
- Scenario loading from JSON
- Map, obstacle, restricted-zone, and distress-beacon loading
- GoogleTest coverage
- Raylib visual demo
- Basic telemetry panel
- Mission timer
- Status text
- Fleet simulation with multiple vessels
- Headless fleet simulation mode
- UDP telemetry sender
- Temporary binary packet builder
- Temporary binary packet tests
- C#/.NET ingestion backend
- UDP receiver on port `5005`
- `System.Threading.Channels` ingestion pipeline
- Packet metrics and packets-per-second logs
- Protobuf telemetry contract
- C++ Protobuf serialization
- C# Protobuf decoding
- Thread-safe latest vessel state registry
- Bad packet handling
- Backend HTTP health, metrics, and vessel-state endpoints
- C# xUnit tests for the Protobuf ingestion pipeline

Next milestone:

```text
Phase 4 — React Mission Dashboard
```

Recommended next backend/frontend step:

```text
Add WebSocket broadcaster from C# backend to React dashboard
```

---

---

## How to Run React Dashboard

From the repository root:

```bash
cd frontend/maritime-dashboard
npm install
npm run dev
```
