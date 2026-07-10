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
| Backend state registry | ConcurrentDictionary      | Latest vessel state registry.                       |
| Live Stream            | WebSockets                | Backend to browser real-time updates                |
| Frontend               | React + TypeScript        | Mission-control dashboard                           |
| Map Rendering          | MapLibre GL JS or Canvas  | Live vessel visualization                           |
| Persistence            | TimescaleDB               | Time-series telemetry storage                       |
| Message broker         | Kafka.                    | Optional future event streaming layer               |
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

Telemetry packet layout:

````text
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

---

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
- Simple binary payload first
- Protobuf payload later

### Phase 2 — C#/.NET Ingestion Engine

Goal:

Build the backend service that receives, decodes, and routes C++ telemetry.

Build:

- `UdpTelemetryReceiver`
- `PacketDecoder`
- `VesselStateRegistry`
- `Channel<byte[]>` ingestion pipeline
- Background worker services
- Structured console logs
- Packet counters
- Dropped packet counters
- Bad packet quarantine
- WebSocket broadcaster

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
````

---

## Repository Structure

```text
MaritimeOpsSim/
│
├── cpp/
│   ├── src/
│   ├── include/
│   └── tests/
│
├── proto/
│
├── backend/
│   └── MaritimeOps.Ingestion/
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
│
├── scripts/
│
├── .github/
│   └── workflows/
│
├── docker-compose.yml
├── CMakeLists.txt
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

## How to Run Current Tests

```bash
cd build
ctest --output-on-failure
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

Next milestone:

```text
Phase 1 — C++ Fleet Simulation and UDP Telemetry
```

---

## Resume Direction

### Short Version

Built MaritimeOpsSim, a distributed maritime command-and-telemetry platform that simulates safe search-and-rescue vessel operations, streams live telemetry, visualizes mission state, and validates system resilience through automated testing.

### Strong Version

Developed MaritimeOpsSim, a distributed maritime telemetry platform with a C++20 fleet simulation engine, UDP telemetry streaming, C#/.NET ingestion pipeline, React/TypeScript mission dashboard, TimescaleDB persistence, Python chaos tests, Docker Compose orchestration, and CI automation.

---

## Interview Pitch

I built MaritimeOpsSim, a safe distributed maritime command-and-telemetry platform. It started as a C++20 unmanned surface vessel simulator with Raylib visualization and JSON scenario loading. I expanded it into a distributed telemetry system where the C++ simulation layer produces live vessel state, streams telemetry over UDP, and a C#/.NET backend ingests, decodes, and routes that data through asynchronous producer-consumer pipelines.

The backend maintains latest vessel state, broadcasts updates to a React/TypeScript dashboard over WebSockets, and persists telemetry history into TimescaleDB. I also added Python-based chaos tests that inject corrupted packets, simulate disconnects, and verify that the backend isolates faults instead of crashing.

The project is intentionally safe-scoped around search-and-rescue, maritime domain awareness, telemetry processing, and system reliability. It does not include targeting, fire control, strike planning, or real-world tactical recommendations.
