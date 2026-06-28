# MaritimeOpsSim Requirements

## Project Goal

Build an AI-assisted unmanned surface vessel mission simulator for safe search-and-rescue and maritime domain awareness scenarios.

The project should demonstrate practical software engineering skills in C++ systems programming, mission simulation, 2D visualization, path planning, telemetry processing, AI-assisted analysis, testing, CI/CD, documentation, and release packaging.

## Scope

MaritimeOpsSim will simulate unmanned surface vessels operating in a coastal maritime environment. The simulator will support scenario loading, mission logic, route planning, telemetry generation, communication-loss simulation, failure alerts, AI-assisted anomaly detection, mission risk scoring, and post-mission reports.

## Safe-Scope Requirements

The project shall only support safe maritime simulation scenarios.

The project shall focus on:

- Search-and-rescue missions
- Maritime domain awareness
- Coastal patrol simulation
- Distress beacon response
- Telemetry analysis
- Mission risk scoring
- Post-mission reporting
- Software engineering education

The project shall not include:

- Weapon targeting
- Missile guidance
- Strike planning
- Combat engagement
- Fire-control logic
- Attack optimization
- Real-world tactical recommendations

## MVP Requirements

| ID      | Requirement                                                            |
| ------- | ---------------------------------------------------------------------- |
| REQ-001 | The project shall include a C++ simulation engine.                     |
| REQ-002 | The project shall simulate at least one unmanned surface vessel.       |
| REQ-003 | The project shall load at least one mission scenario from JSON.        |
| REQ-004 | The project shall include a 2D map viewer using Raylib.                |
| REQ-005 | The project shall support waypoint-based navigation.                   |
| REQ-006 | The project shall generate telemetry logs.                             |
| REQ-007 | The project shall support a basic search-and-rescue mission objective. |
| REQ-008 | The project shall support basic mission success and failure rules.     |
| REQ-009 | The project shall include a safe-scope disclaimer.                     |
| REQ-010 | The project shall include a professional README.                       |

## Strong Portfolio Requirements

| ID      | Requirement                                                                                |
| ------- | ------------------------------------------------------------------------------------------ |
| REQ-011 | The project shall implement A\* path planning.                                             |
| REQ-012 | The project shall simulate communication delay or communication loss.                      |
| REQ-013 | The project shall generate alerts for low battery, route deviation, or communication loss. |
| REQ-014 | The project shall store mission and telemetry data in SQLite.                              |
| REQ-015 | The project shall include Python tools for mission analysis.                               |
| REQ-016 | The project shall include AI-assisted anomaly detection.                                   |
| REQ-017 | The project shall include mission risk scoring.                                            |
| REQ-018 | The project shall include GoogleTest unit tests for C++ logic.                             |
| REQ-019 | The project shall include Pytest tests for Python tools.                                   |
| REQ-020 | The project shall include GitHub Actions CI.                                               |
| REQ-021 | The project shall include a demo video.                                                    |
| REQ-022 | The project shall include a downloadable GitHub Release.                                   |

## Week 1 Acceptance Criteria

Week 1 is complete when:

- The GitHub repository exists.
- The project folder structure exists.
- `README.md` exists.
- `CMakeLists.txt` exists.
- `cpp/src/main.cpp` exists.
- The project builds with CMake.
- The executable prints a startup message.
- `scenarios/search_rescue_demo.json` exists.
- `docs/requirements.md` exists.
- `docs/architecture.md` exists.

## Final Project Acceptance Criteria

The project is complete when:

- The simulator runs visually with Raylib.
- A mission can be loaded from JSON.
- At least one USV can follow waypoints.
- A\* path planning works around obstacles.
- Search-and-rescue mission logic works.
- Telemetry is saved.
- SQLite stores mission data.
- Communication loss can be simulated.
- Alerts appear in the UI.
- Python can analyze mission logs.
- AI anomaly detection produces useful output.
- Mission risk score is generated.
- GoogleTest tests pass.
- Pytest tests pass.
- GitHub Actions CI passes.
- README explains the project clearly.
- Demo video exists.
- GitHub Release exists.
- Resume bullets are ready.
