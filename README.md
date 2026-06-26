# MaritimeOpsSim

## AI-Assisted Unmanned Surface Vessel Mission Simulator

MaritimeOpsSim is a C++/Python 2D mission simulation platform that models unmanned surface vessels performing safe search-and-rescue and maritime domain awareness missions with route planning, telemetry generation, communication-loss simulation, anomaly detection, mission risk scoring, replay, and post-mission analysis.

## Project Goal

The goal of this project is to build a safe, advanced, aerospace/defense-relevant software engineering portfolio project that demonstrates skills in C++ systems programming, mission simulation, 2D tactical visualization, algorithms, telemetry processing, AI-assisted analysis, testing, CI/CD, and professional software delivery.

## Project Scope

MaritimeOpsSim will simulate unmanned surface vessels operating in a coastal maritime environment. The simulator will include mission objectives, route planning, telemetry, communication delays, failure simulation, alerts, AI-assisted anomaly detection, mission risk scoring, and post-mission reports.

## Safe-Scope Disclaimer

This project is a safe maritime mission simulation platform focused on search-and-rescue, maritime domain awareness, telemetry analysis, and software engineering education.

This project does not include weapon targeting, missile guidance, strike planning, combat engagement, fire-control logic, attack optimization, or real-world tactical recommendations.

## Planned Features

- C++20 simulation engine
- Raylib 2D tactical maritime viewer
- JSON scenario loader
- A\* path planning
- Search-and-rescue mission logic
- Maritime domain awareness scenarios
- Telemetry logging
- SQLite mission database
- Communication loss and failure simulation
- Python analysis tools
- AI anomaly detection
- Mission risk scoring
- GoogleTest unit tests
- Pytest tests
- GitHub Actions CI pipeline
- Downloadable desktop release

## Tech Stack

| Tool / Language     | Purpose                                     |
| ------------------- | ------------------------------------------- |
| C++20               | Core simulation engine                      |
| CMake               | C++ build system                            |
| Raylib              | 2D graphical simulation viewer              |
| GoogleTest          | C++ unit testing                            |
| Python              | Analysis tools, AI tools, report generation |
| Pytest              | Python testing                              |
| SQLite              | Mission and telemetry storage               |
| scikit-learn        | AI anomaly detection and risk scoring       |
| pandas / NumPy      | Telemetry data processing                   |
| matplotlib / Plotly | Charts and reports                          |
| GitHub Actions      | CI pipeline                                 |
| Linux / Bash        | Scripts and development workflow            |
| Docker              | Optional reproducible environment           |

## Initial Architecture

```text
Scenario JSON
    ↓
C++ Simulation Engine
    ↓
Raylib 2D Viewer
    ↓
Telemetry Logs
    ↓
SQLite Mission Database
    ↓
Python AI / Analysis Tools
    ↓
Mission Reports / Charts
    ↓
GitHub Actions CI
    ↓
GitHub Release / Downloadable Build
```

## Current Status

Project setup in progress.

## Roadmap

### Week 1 — Setup, Requirements, Architecture

- Create repository
- Create folder structure
- Create README
- Define project goal
- Write safe-scope disclaimer
- Create initial requirements and architecture drafts

### Week 2 — Core C++ Simulation Engine

- Create `SimulationEngine`
- Create `Mission`
- Create `Vessel`
- Add basic simulation loop
- Print console telemetry

### Week 3 — Scenario Loader and Map System

- Load mission scenarios from JSON
- Add map size, waypoints, obstacles, and validation

### Week 4 — Raylib 2D Visualization

- Add 2D window
- Draw ocean map, USV, route lines, waypoints, and telemetry panel

### Week 5 — Path Planning

- Implement BFS and A\* pathfinding

### Week 6 — Mission Logic

- Add search-and-rescue objective, distress beacon, mission scoring, and success/failure logic

### Week 7 — Telemetry Logging and SQLite

- Persist mission and telemetry data

### Week 8 — Communication Loss and Failure Simulation

- Add heartbeat, signal loss, communication delay, low battery, and alerts

### Week 9 — Python Analysis Tools

- Parse logs, generate mission reports, and create charts

### Week 10 — AI Anomaly Detection and Mission Risk Scoring

- Detect abnormal telemetry patterns and generate risk score

### Week 11 — Testing, CI, and Reliability

- Add GoogleTest, Pytest, and GitHub Actions

### Week 12 — Demo, Documentation, and Release

- Add demo video, screenshots, release package, and resume bullets

## License

License to be added later.
