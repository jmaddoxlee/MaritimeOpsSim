# Maritime Dashboard

## Purpose

The Maritime Dashboard is the planned React + TypeScript real-time dashboard for MaritimeOpsSim.

This dashboard will connect to the C#/.NET ingestion backend over WebSockets and display live vessel telemetry, mission state, connection health, and alerts.

---

## Planned Responsibilities

The dashboard will:

- Connect to the backend WebSocket stream
- Display connection status
- Render live vessel positions
- Support at least 100 moving vessels
- Show selected vessel telemetry
- Show low-fuel alerts
- Show stale telemetry alerts
- Show restricted-zone alerts
- Show backend packet metrics
- Render efficiently using Canvas or MapLibre
- Avoid unnecessary React re-renders during high-frequency telemetry updates

---

## Planned Main Components

| Component               | Responsibility                                       |
| ----------------------- | ---------------------------------------------------- |
| `WebSocketClient`       | Connects to the backend live telemetry stream        |
| `TelemetryStore`        | Holds latest vessel telemetry state                  |
| `MissionMap`            | Renders the live mission map                         |
| `VesselLayer`           | Draws vessel icons and heading indicators            |
| `TelemetryPanel`        | Displays selected vessel details                     |
| `AlertPanel`            | Displays low-fuel, stale, and restricted-zone alerts |
| `ConnectionHealthPanel` | Displays backend connection and message health       |
| `MissionSummaryPanel`   | Displays fleet-level mission information             |

---

## Initial Development Goal

The first frontend goal is to create a React + TypeScript dashboard that can:

1. Start successfully
2. Connect to a WebSocket endpoint
3. Display connection status
4. Render placeholder vessel data
5. Prepare for live telemetry rendering
