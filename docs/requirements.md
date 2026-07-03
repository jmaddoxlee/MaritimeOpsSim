# MaritimeOpsSim Requirements

## Project Identity

**MaritimeOpsSim — Distributed Maritime Command & Telemetry Platform**

MaritimeOpsSim is a safe distributed maritime simulation and telemetry platform focused on search-and-rescue, maritime domain awareness, vessel telemetry, mission monitoring, real-time dashboard visualization, time-series persistence, automated fault-injection testing, and resilient distributed systems.

The project started as a C++/Raylib unmanned surface vessel simulator and is now being expanded into a distributed telemetry platform with a C++ simulation layer, C#/.NET ingestion backend, React/TypeScript dashboard, TimescaleDB persistence, Python test/control layer, Docker runtime, and CI/CD.

---

## Project Goal

The goal of MaritimeOpsSim is to build a portfolio-grade software engineering project that demonstrates practical skills for aerospace, defense, mission software, ground systems, telemetry systems, industrial IoT, public safety technology, and high-performance distributed systems roles.

The project shall demonstrate skills in:

- C++ systems programming
- Deterministic simulation loops
- Maritime mission simulation
- Scenario loading
- 2D local visualization
- Real-time telemetry generation
- UDP networking
- Protocol Buffers telemetry contracts
- C#/.NET ingestion pipelines
- Producer-consumer concurrency
- WebSocket live streaming
- React/TypeScript real-time dashboard rendering
- Time-series database persistence
- Python automation and chaos testing
- Linux debugging
- Docker Compose orchestration
- GitHub Actions CI
- Testing and verification
- Professional documentation
- Portfolio-ready demo delivery

---

## Scope

MaritimeOpsSim shall simulate safe maritime mission scenarios in software.

The system shall include:

- A C++ simulation layer
- A local Raylib visual demo
- A fleet simulation model
- A telemetry packet format
- UDP telemetry streaming
- A C#/.NET ingestion backend
- A live WebSocket stream
- A React/TypeScript mission dashboard
- TimescaleDB telemetry persistence
- Python test and control tools
- Docker Compose runtime support
- Automated tests and CI
- Architecture and requirements documentation

The first goal is to make the original simulator work.

The second goal is to make it visual.

The third goal is to make it produce live telemetry.

The fourth goal is to make that telemetry stream into a backend.

The fifth goal is to display it in a real-time browser dashboard.

The sixth goal is to persist and test it.

The final goal is to make the project professional with Docker, CI, documentation, demo assets, and interview-ready explanations.

---

## Safe-Scope Requirements

The project shall only support safe maritime simulation and telemetry scenarios.

The project shall focus on:

- Search-and-rescue simulation
- Maritime domain awareness
- Coastal monitoring simulation
- Distress beacon response
- Vessel telemetry
- Mission monitoring
- Command-dashboard visualization
- Communication loss simulation
- Failure detection
- Fault tolerance
- System reliability
- Automated testing
- Software engineering education

The project shall not include:

- Weapon targeting
- Missile guidance
- Strike planning
- Combat engagement
- Fire-control logic
- Attack optimization
- Enemy engagement
- Lethality modeling
- Real-world tactical recommendations

---

# 1. Already Completed Requirements

These requirements have already been completed in the current version.

| ID           | Requirement                                                      | Status   |
| ------------ | ---------------------------------------------------------------- | -------- |
| REQ-DONE-001 | The project shall include a GitHub repository.                   | Complete |
| REQ-DONE-002 | The project shall include a basic folder structure.              | Complete |
| REQ-DONE-003 | The project shall include a README file.                         | Complete |
| REQ-DONE-004 | The project shall include a CMake-based C++ build.               | Complete |
| REQ-DONE-005 | The project shall include a basic C++ executable.                | Complete |
| REQ-DONE-006 | The project shall include a `Vessel` class.                      | Complete |
| REQ-DONE-007 | The project shall model vessel position, speed, and heading.     | Complete |
| REQ-DONE-008 | The project shall include vessel movement update logic.          | Complete |
| REQ-DONE-009 | The project shall include a `Mission` class.                     | Complete |
| REQ-DONE-010 | The project shall include a `SimulationEngine` class.            | Complete |
| REQ-DONE-011 | The project shall include a time-stepped simulation loop.        | Complete |
| REQ-DONE-012 | The project shall include console telemetry output.              | Complete |
| REQ-DONE-013 | The project shall include GoogleTest setup.                      | Complete |
| REQ-DONE-014 | The project shall include a vessel movement test.                | Complete |
| REQ-DONE-015 | The project shall include a JSON scenario file.                  | Complete |
| REQ-DONE-016 | The project shall include a scenario loader.                     | Complete |
| REQ-DONE-017 | The project shall load mission data from JSON.                   | Complete |
| REQ-DONE-018 | The project shall load map data from JSON.                       | Complete |
| REQ-DONE-019 | The project shall load vessel data from JSON.                    | Complete |
| REQ-DONE-020 | The project shall load waypoints from JSON.                      | Complete |
| REQ-DONE-021 | The project shall load obstacles from JSON.                      | Complete |
| REQ-DONE-022 | The project shall load restricted zones from JSON.               | Complete |
| REQ-DONE-023 | The project shall load distress beacon data from JSON.           | Complete |
| REQ-DONE-024 | The project shall include scenario validation.                   | Complete |
| REQ-DONE-025 | The project shall include ScenarioLoader tests.                  | Complete |
| REQ-DONE-026 | The project shall include a `MapGrid` model.                     | Complete |
| REQ-DONE-027 | The project shall include map boundary checks.                   | Complete |
| REQ-DONE-028 | The project shall include obstacle checks.                       | Complete |
| REQ-DONE-029 | The project shall include restricted-zone checks.                | Complete |
| REQ-DONE-030 | The project shall include a Raylib visual executable.            | Complete |
| REQ-DONE-031 | The project shall draw the mission map in Raylib.                | Complete |
| REQ-DONE-032 | The project shall draw the vessel position in Raylib.            | Complete |
| REQ-DONE-033 | The project shall draw waypoints in Raylib.                      | Complete |
| REQ-DONE-034 | The project shall draw obstacles and restricted zones in Raylib. | Complete |
| REQ-DONE-035 | The project shall draw the distress beacon in Raylib.            | Complete |
| REQ-DONE-036 | The project shall include a basic telemetry panel.               | Complete |
| REQ-DONE-037 | The project shall include a mission timer.                       | Complete |
| REQ-DONE-038 | The project shall support screenshot capture.                    | Complete |

---

# 2. Core C++ Simulation Requirements

| ID          | Requirement                                                                                                                                   |
| ----------- | --------------------------------------------------------------------------------------------------------------------------------------------- |
| REQ-CPP-001 | The project shall include a C++20 simulation layer.                                                                                           |
| REQ-CPP-002 | The C++ simulation layer shall remain the source of truth for simulated vessel state.                                                         |
| REQ-CPP-003 | The project shall include a `VesselState` runtime model.                                                                                      |
| REQ-CPP-004 | `VesselState` shall include vessel ID, position, speed, heading, fuel, signal strength, elapsed time, and operational status.                 |
| REQ-CPP-005 | The project shall include a `FleetSimulationEngine`.                                                                                          |
| REQ-CPP-006 | `FleetSimulationEngine` shall update multiple vessel states in a deterministic fixed timestep loop.                                           |
| REQ-CPP-007 | The simulator shall support at least 100 simulated vessels.                                                                                   |
| REQ-CPP-008 | The simulator shall generate unique vessel IDs for all simulated vessels.                                                                     |
| REQ-CPP-009 | The simulator shall update vessel position based on speed, heading, and elapsed time.                                                         |
| REQ-CPP-010 | The simulator shall include a fuel or battery burn model.                                                                                     |
| REQ-CPP-011 | The simulator shall prevent fuel from dropping below zero.                                                                                    |
| REQ-CPP-012 | The simulator shall stop or flag a vessel when fuel reaches zero.                                                                             |
| REQ-CPP-013 | The simulator shall track vessel signal strength.                                                                                             |
| REQ-CPP-014 | The simulator shall support future status flags such as active, low fuel, signal degraded, stale, out of bounds, and restricted-zone warning. |
| REQ-CPP-015 | The simulator shall support a headless simulation mode.                                                                                       |
| REQ-CPP-016 | The simulator shall support local Raylib visualization separately from headless telemetry mode.                                               |
| REQ-CPP-017 | The C++ simulation logic shall be testable without requiring Raylib.                                                                          |
| REQ-CPP-018 | The C++ simulation logic shall be separated from network transport logic.                                                                     |
| REQ-CPP-019 | The project shall include GoogleTest coverage for fleet simulation behavior.                                                                  |
| REQ-CPP-020 | The project shall include tests for vessel count, unique IDs, position updates, fuel burn, and inactive vessel behavior.                      |

---

# 3. Local Raylib Visual Demo Requirements

Raylib remains part of the project, but its role is the local C++ visual demo and debugging viewer.

| ID          | Requirement                                                                           |
| ----------- | ------------------------------------------------------------------------------------- |
| REQ-VIS-001 | The project shall include a Raylib-based local visual simulator.                      |
| REQ-VIS-002 | The Raylib viewer shall display the scenario map.                                     |
| REQ-VIS-003 | The Raylib viewer shall display vessel position.                                      |
| REQ-VIS-004 | The Raylib viewer shall display waypoints.                                            |
| REQ-VIS-005 | The Raylib viewer shall display obstacles.                                            |
| REQ-VIS-006 | The Raylib viewer shall display restricted zones.                                     |
| REQ-VIS-007 | The Raylib viewer shall display a distress beacon.                                    |
| REQ-VIS-008 | The Raylib viewer shall include a basic telemetry panel.                              |
| REQ-VIS-009 | The Raylib viewer shall include a mission timer.                                      |
| REQ-VIS-010 | The Raylib viewer shall support screenshot capture.                                   |
| REQ-VIS-011 | The Raylib viewer shall be used for local debugging and demo purposes.                |
| REQ-VIS-012 | The final distributed dashboard shall be implemented in React/TypeScript, not Raylib. |

---

# 4. Telemetry Contract Requirements

| ID          | Requirement                                                                                            |
| ----------- | ------------------------------------------------------------------------------------------------------ |
| REQ-TEL-001 | The project shall define a telemetry contract between the C++ simulation layer and C# ingestion layer. |
| REQ-TEL-002 | The telemetry contract shall include `vessel_id`.                                                      |
| REQ-TEL-003 | The telemetry contract shall include `timestamp_unix_ms`.                                              |
| REQ-TEL-004 | The telemetry contract shall include `sequence_number`.                                                |
| REQ-TEL-005 | The telemetry contract shall include vessel position fields `x` and `y`.                               |
| REQ-TEL-006 | The telemetry contract shall include `speed`.                                                          |
| REQ-TEL-007 | The telemetry contract shall include `heading`.                                                        |
| REQ-TEL-008 | The telemetry contract shall include `fuel`.                                                           |
| REQ-TEL-009 | The telemetry contract shall include `signal_strength`.                                                |
| REQ-TEL-010 | The telemetry contract shall include `status_flags`.                                                   |
| REQ-TEL-011 | The first telemetry implementation may use a simple binary packet.                                     |
| REQ-TEL-012 | The stronger telemetry implementation shall use Protocol Buffers.                                      |
| REQ-TEL-013 | The project shall include `proto/vessel_telemetry.proto`.                                              |
| REQ-TEL-014 | The C++ layer shall serialize telemetry packets.                                                       |
| REQ-TEL-015 | The C# layer shall deserialize telemetry packets.                                                      |
| REQ-TEL-016 | The telemetry contract shall support packet ordering through sequence numbers.                         |
| REQ-TEL-017 | The telemetry contract shall support dropped-packet detection.                                         |
| REQ-TEL-018 | Invalid telemetry packets shall not crash the backend.                                                 |

---

# 5. UDP Network Transport Requirements

| ID          | Requirement                                                                                                     |
| ----------- | --------------------------------------------------------------------------------------------------------------- |
| REQ-NET-001 | The C++ simulation layer shall emit telemetry over UDP.                                                         |
| REQ-NET-002 | The UDP sender shall support localhost during development.                                                      |
| REQ-NET-003 | The UDP sender shall support a configurable host and port later.                                                |
| REQ-NET-004 | The default development UDP target shall be `127.0.0.1:5005`.                                                   |
| REQ-NET-005 | The simulator shall log the number of telemetry packets emitted.                                                |
| REQ-NET-006 | The simulator shall support sending telemetry for multiple vessels.                                             |
| REQ-NET-007 | The simulator shall support a future command-line mode such as `--headless --vessels 100 --udp 127.0.0.1:5005`. |
| REQ-NET-008 | The project shall include tests for telemetry packet creation.                                                  |
| REQ-NET-009 | The project shall include documentation for inspecting UDP packets during development.                          |

---

# 6. C#/.NET Ingestion Backend Requirements

| ID         | Requirement                                                                                             |
| ---------- | ------------------------------------------------------------------------------------------------------- |
| REQ-BE-001 | The project shall include a C#/.NET backend under `backend/MaritimeOps.Ingestion`.                      |
| REQ-BE-002 | The backend shall include a UDP telemetry receiver.                                                     |
| REQ-BE-003 | The backend shall listen on UDP port `5005` during local development.                                   |
| REQ-BE-004 | The backend shall decode incoming telemetry packets.                                                    |
| REQ-BE-005 | The backend shall reject malformed packets safely.                                                      |
| REQ-BE-006 | The backend shall track received packet count.                                                          |
| REQ-BE-007 | The backend shall track decoded packet count.                                                           |
| REQ-BE-008 | The backend shall track bad packet count.                                                               |
| REQ-BE-009 | The backend shall track dropped packet count.                                                           |
| REQ-BE-010 | The backend shall use `System.Threading.Channels` for producer-consumer packet processing.              |
| REQ-BE-011 | The backend shall support cancellation and clean shutdown.                                              |
| REQ-BE-012 | The backend shall include a `PacketDecoder`.                                                            |
| REQ-BE-013 | The backend shall include a `VesselStateRegistry`.                                                      |
| REQ-BE-014 | The `VesselStateRegistry` shall maintain the latest known state for each vessel.                        |
| REQ-BE-015 | The backend shall use `ConcurrentDictionary` or equivalent thread-safe storage for latest vessel state. |
| REQ-BE-016 | The backend shall detect stale vessel updates.                                                          |
| REQ-BE-017 | The backend shall expose or log basic health information.                                               |
| REQ-BE-018 | The backend shall keep core telemetry models separate from UDP, WebSocket, and database adapters.       |
| REQ-BE-019 | The backend shall include unit tests for packet decoding.                                               |
| REQ-BE-020 | The backend shall include unit tests for state registry behavior.                                       |
| REQ-BE-021 | The backend shall include tests for invalid packet handling.                                            |

---

# 7. WebSocket Streaming Requirements

| ID         | Requirement                                                                |
| ---------- | -------------------------------------------------------------------------- |
| REQ-WS-001 | The C# backend shall broadcast live vessel state over WebSockets.          |
| REQ-WS-002 | The backend shall support at least one connected dashboard client.         |
| REQ-WS-003 | The backend shall broadcast latest vessel state snapshots.                 |
| REQ-WS-004 | The snapshot shall include active vessel count.                            |
| REQ-WS-005 | The snapshot shall include vessel telemetry fields needed by the frontend. |
| REQ-WS-006 | The backend shall track connected client count.                            |
| REQ-WS-007 | The backend shall support a heartbeat or connection-health message.        |
| REQ-WS-008 | The backend shall avoid crashing when a WebSocket client disconnects.      |

---

# 8. React / TypeScript Dashboard Requirements

| ID         | Requirement                                                                                                  |
| ---------- | ------------------------------------------------------------------------------------------------------------ |
| REQ-FE-001 | The project shall include a React + TypeScript dashboard under `frontend/maritime-dashboard`.                |
| REQ-FE-002 | The dashboard shall connect to the backend WebSocket stream.                                                 |
| REQ-FE-003 | The dashboard shall display connection status.                                                               |
| REQ-FE-004 | The dashboard shall receive live vessel snapshots.                                                           |
| REQ-FE-005 | The dashboard shall render live vessel positions.                                                            |
| REQ-FE-006 | The dashboard shall support at least 100 moving vessels.                                                     |
| REQ-FE-007 | The dashboard shall include a selected vessel panel.                                                         |
| REQ-FE-008 | The selected vessel panel shall show vessel ID, position, speed, heading, fuel, signal strength, and status. |
| REQ-FE-009 | The dashboard shall include an alert panel.                                                                  |
| REQ-FE-010 | The dashboard shall show low-fuel alerts.                                                                    |
| REQ-FE-011 | The dashboard shall show stale telemetry alerts.                                                             |
| REQ-FE-012 | The dashboard shall show restricted-zone alerts when available.                                              |
| REQ-FE-013 | The dashboard shall include a connection health panel.                                                       |
| REQ-FE-014 | The dashboard shall show message rate or last-message time.                                                  |
| REQ-FE-015 | The dashboard shall use `useRef` or an equivalent approach for high-frequency telemetry state.               |
| REQ-FE-016 | The dashboard shall avoid React state updates for every telemetry frame.                                     |
| REQ-FE-017 | The dashboard shall use `requestAnimationFrame` or equivalent timing for rendering.                          |
| REQ-FE-018 | The dashboard shall render using Canvas or MapLibre.                                                         |
| REQ-FE-019 | The dashboard shall include basic frontend tests or type checks.                                             |
| REQ-FE-020 | The dashboard shall include at least one screenshot or demo clip for the README.                             |

---

# 9. TimescaleDB Persistence Requirements

| ID         | Requirement                                                                                                                            |
| ---------- | -------------------------------------------------------------------------------------------------------------------------------------- |
| REQ-DB-001 | The project shall use TimescaleDB as the primary distributed telemetry persistence target.                                             |
| REQ-DB-002 | The project shall include database migrations under `database/migrations`.                                                             |
| REQ-DB-003 | The project shall include sample queries under `database/queries`.                                                                     |
| REQ-DB-004 | The database shall include a `vessel_telemetry` table.                                                                                 |
| REQ-DB-005 | The telemetry table shall include time, vessel ID, position, speed, heading, fuel, signal strength, status flags, and sequence number. |
| REQ-DB-006 | The telemetry table shall be designed as a time-series table.                                                                          |
| REQ-DB-007 | The backend shall write telemetry records to TimescaleDB.                                                                              |
| REQ-DB-008 | The backend shall support latest position queries.                                                                                     |
| REQ-DB-009 | The backend or SQL scripts shall support average speed queries.                                                                        |
| REQ-DB-010 | The backend or SQL scripts shall support fuel trend queries.                                                                           |
| REQ-DB-011 | The backend shall keep database writing separate from packet receiving and decoding.                                                   |
| REQ-DB-012 | SQLite may remain as an older/local analysis option, but TimescaleDB is the primary revised persistence target.                        |

---

# 10. Python Test and Control Requirements

| ID         | Requirement                                                                                                  |
| ---------- | ------------------------------------------------------------------------------------------------------------ |
| REQ-PY-001 | The project shall include Python control tools under `python/control`.                                       |
| REQ-PY-002 | Python tools shall support launching the C++ simulator.                                                      |
| REQ-PY-003 | Python tools shall support launching the C# backend.                                                         |
| REQ-PY-004 | Python tools shall include a corrupt packet sender.                                                          |
| REQ-PY-005 | Python tools shall include a packet fuzzer.                                                                  |
| REQ-PY-006 | Python tools shall include a simulator disconnect test.                                                      |
| REQ-PY-007 | Python tools shall include a packet flood test.                                                              |
| REQ-PY-008 | Python tools shall include a stale vessel test.                                                              |
| REQ-PY-009 | Python tools shall include basic performance monitoring.                                                     |
| REQ-PY-010 | The project shall include Pytest coverage for Python control tools.                                          |
| REQ-PY-011 | Python tests shall verify that corrupt packets do not crash the backend.                                     |
| REQ-PY-012 | Python tests shall verify that simulator shutdown causes stale vessel detection rather than backend failure. |
| REQ-PY-013 | Python tests shall verify that packet flood behavior is counted and handled safely.                          |
| REQ-PY-014 | Python AI anomaly detection is optional after telemetry, persistence, and chaos testing are complete.        |

---

# 11. Docker / Linux Runtime Requirements

| ID          | Requirement                                                                                                          |
| ----------- | -------------------------------------------------------------------------------------------------------------------- |
| REQ-RUN-001 | The project shall include a `docker-compose.yml` file.                                                               |
| REQ-RUN-002 | Docker Compose shall eventually define a `cpp-sim` service.                                                          |
| REQ-RUN-003 | Docker Compose shall eventually define an `ingestion-api` service.                                                   |
| REQ-RUN-004 | Docker Compose shall eventually define a `maritime-dashboard` service.                                               |
| REQ-RUN-005 | Docker Compose shall eventually define a `timescaledb` service.                                                      |
| REQ-RUN-006 | Docker Compose shall eventually define a `python-test-runner` service.                                               |
| REQ-RUN-007 | The project shall document how to inspect UDP sockets.                                                               |
| REQ-RUN-008 | The project shall document use of basic Linux debugging tools such as `ss`, `netstat`, `tcpdump`, `top`, and `htop`. |
| REQ-RUN-009 | The project shall eventually run the core stack with `docker compose up --build`.                                    |

---

# 12. CI/CD and Testing Requirements

| ID         | Requirement                                                      |
| ---------- | ---------------------------------------------------------------- |
| REQ-CI-001 | The project shall include GitHub Actions CI.                     |
| REQ-CI-002 | CI shall build the C++ project.                                  |
| REQ-CI-003 | CI shall run GoogleTest tests.                                   |
| REQ-CI-004 | CI shall build the C# backend.                                   |
| REQ-CI-005 | CI shall run C# backend tests.                                   |
| REQ-CI-006 | CI shall build the React frontend.                               |
| REQ-CI-007 | CI shall run frontend type checks or tests.                      |
| REQ-CI-008 | CI shall run safe Pytest tests.                                  |
| REQ-CI-009 | CI shall validate sample scenario files.                         |
| REQ-CI-010 | CI shall eventually run a Docker Compose smoke test.             |
| REQ-CI-011 | The README shall include CI status badges when CI is configured. |

---

# 13. Documentation Requirements

| ID          | Requirement                                                                                  |
| ----------- | -------------------------------------------------------------------------------------------- |
| REQ-DOC-001 | The project shall include a professional README.                                             |
| REQ-DOC-002 | The project shall include `docs/architecture.md`.                                            |
| REQ-DOC-003 | The project shall include `docs/requirements.md`.                                            |
| REQ-DOC-004 | The project shall include `docs/safe_scope.md`.                                              |
| REQ-DOC-005 | The project shall include `docs/telemetry_contract.md`.                                      |
| REQ-DOC-006 | The project shall include `docs/study_plan.md`.                                              |
| REQ-DOC-007 | The project shall include `docs/system_design.md`.                                           |
| REQ-DOC-008 | The project shall include `docs/testing_strategy.md`.                                        |
| REQ-DOC-009 | The project shall include `docs/failure_modes.md`.                                           |
| REQ-DOC-010 | The project shall include `docs/performance_report.md`.                                      |
| REQ-DOC-011 | The project shall include `docs/project_case_study.md`.                                      |
| REQ-DOC-012 | The project shall include `docs/interview_script.md`.                                        |
| REQ-DOC-013 | Documentation shall explain why Raylib is used only as a local visual demo.                  |
| REQ-DOC-014 | Documentation shall explain why React/TypeScript is used for the main distributed dashboard. |
| REQ-DOC-015 | Documentation shall explain the safe-scope boundary.                                         |
| REQ-DOC-016 | Documentation shall include resume bullets and interview explanation material.               |

---

# 14. Portfolio and Demo Requirements

| ID           | Requirement                                                                                 |
| ------------ | ------------------------------------------------------------------------------------------- |
| REQ-PORT-001 | The project shall include at least one screenshot of the Raylib visual demo.                |
| REQ-PORT-002 | The project shall include at least one screenshot of the React dashboard after it is built. |
| REQ-PORT-003 | The project shall include a demo video.                                                     |
| REQ-PORT-004 | The project shall include a 2-minute project explanation script.                            |
| REQ-PORT-005 | The project shall include a 5-minute technical deep-dive script.                            |
| REQ-PORT-006 | The project shall include resume bullets.                                                   |
| REQ-PORT-007 | The project shall include a project case study.                                             |
| REQ-PORT-008 | The project shall include a final architecture diagram.                                     |
| REQ-PORT-009 | The project shall include a performance report.                                             |
| REQ-PORT-010 | The project shall be understandable to a hiring manager from the README and demo video.     |

---

# 15. Phase Acceptance Criteria

## Phase 0 — Rebrand and Architecture Reset

Phase 0 is complete when:

- README title is updated to `MaritimeOpsSim — Distributed Maritime Command & Telemetry Platform`.
- README includes the safe-scope disclaimer.
- README includes the updated high-level architecture.
- README includes the updated tech stack.
- README includes completed Weeks 1–4 progress.
- `docs/architecture.md` is updated for the distributed architecture.
- `docs/requirements.md` is updated for the distributed architecture.
- `proto/` folder exists.
- `backend/MaritimeOps.Ingestion/` folder exists.
- `frontend/maritime-dashboard/` folder exists.
- `database/migrations/` folder exists.
- `database/queries/` folder exists.
- `python/control/` folder exists.
- `docker-compose.yml` placeholder exists.
- The current C++ project still builds.
- Current GoogleTest tests still pass.

## Phase 1 — C++ Fleet Simulation and UDP Telemetry

Phase 1 is complete when:

- `VesselState` exists.
- `FleetSimulationEngine` exists.
- The simulator can create or load 100 vessel states.
- The fleet simulation updates all vessels in a fixed timestep loop.
- Fuel decreases over time.
- Fleet simulation tests pass.
- `TelemetryPacketBuilder` exists.
- `UdpTelemetrySender` exists.
- C++ can emit telemetry packets over UDP.
- Packet builder tests pass.

## Phase 2 — C#/.NET Ingestion Engine

Phase 2 is complete when:

- C# backend project exists.
- Backend starts successfully.
- Backend receives UDP packets from C++.
- Backend decodes valid telemetry.
- Backend safely rejects invalid telemetry.
- Backend uses `System.Threading.Channels`.
- Backend maintains latest vessel state.
- Backend tracks packet metrics.
- Backend tests pass.

## Phase 3 — WebSocket and React Dashboard

Phase 3 is complete when:

- Backend broadcasts vessel state over WebSockets.
- React dashboard connects to backend.
- Dashboard displays connection status.
- Dashboard renders vessel positions.
- Dashboard shows selected vessel telemetry.
- Dashboard shows alerts.
- Dashboard can display 100 vessels smoothly.
- Frontend type checks or tests pass.

## Phase 4 — TimescaleDB Persistence

Phase 4 is complete when:

- TimescaleDB container exists.
- Telemetry table migration exists.
- Backend writes telemetry to TimescaleDB.
- Latest vessel query works.
- Historical query works.
- Sample SQL queries exist.
- Database documentation exists.

## Phase 5 — Python Chaos and Integration Tests

Phase 5 is complete when:

- Python control scripts exist.
- Corrupt packet test exists.
- Packet flood test exists.
- Disconnect test exists.
- Stale vessel test exists.
- Backend survives malformed packets.
- Backend handles simulator shutdown safely.
- Pytest suite runs successfully.

## Phase 6 — Docker, CI, and Portfolio Polish

Phase 6 is complete when:

- Docker Compose can run the core stack.
- GitHub Actions builds C++.
- GitHub Actions builds C#.
- GitHub Actions builds frontend.
- GitHub Actions runs Pytest.
- Performance report exists.
- Failure-mode document exists.
- Demo video exists.
- Resume bullets exist.
- Interview script exists.
- README is clear and professional.

---

# 16. Final Project Acceptance Criteria

The final revised project is complete when:

- The C++ simulation layer can simulate 100 vessels.
- The C++ simulation layer can run in headless mode.
- The Raylib visual demo still works.
- The simulator can load mission scenarios from JSON.
- The simulator can generate live telemetry.
- Telemetry includes vessel ID, timestamp, sequence number, position, speed, heading, fuel, signal strength, and status flags.
- Telemetry can be sent over UDP.
- Telemetry can be serialized and decoded with Protocol Buffers.
- The C# backend can receive UDP telemetry.
- The C# backend can decode valid telemetry.
- The C# backend can reject malformed telemetry safely.
- The C# backend can maintain latest vessel state.
- The C# backend can detect stale vessel updates.
- The C# backend can broadcast live state over WebSockets.
- The React dashboard can display live vessel movement.
- The React dashboard can display at least 100 vessels.
- The React dashboard can show selected vessel telemetry.
- The React dashboard can show connection health and alerts.
- TimescaleDB stores telemetry history.
- Sample latest-state and historical queries work.
- Python chaos tests can inject corrupt packets.
- Python tests can simulate disconnects and packet floods.
- The backend survives fault-injection tests.
- GoogleTest tests pass.
- C# backend tests pass.
- Frontend type checks or tests pass.
- Pytest tests pass.
- GitHub Actions CI passes.
- Docker Compose can run the core stack.
- README explains the project clearly.
- Architecture documentation exists.
- Requirements documentation exists.
- Testing strategy documentation exists.
- Failure-mode documentation exists.
- Performance report exists.
- Demo video exists.
- Resume bullets are ready.
- Interview explanation script is ready.

---

# 17. Non-Goals

The project shall not attempt to become:

- A real vessel control system
- A real autonomous navigation system
- A real military command system
- A weapon system
- A missile system
- A targeting system
- A combat engagement simulator
- A fire-control system
- A real-world tactical recommendation engine

The project is a safe software engineering simulation, telemetry, testing, and distributed systems portfolio project.
