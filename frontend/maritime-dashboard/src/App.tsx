import { useMemo, useState } from "react";
import "./App.css";
import { AlertPanel } from "./components/AlertPanel";
import { CanvasMap } from "./components/CanvasMap";
import { ConnectionStatusBadge } from "./components/ConnectionStatusBadge";
import { SelectedVesselPanel } from "./components/SelectedVesselPanel";
import { VesselList } from "./components/VesselList";
import { useTelemetrySocket } from "./hooks/useTelemetrySocket";
import type { VesselState } from "./types/telemetry";

function App() {
  const { liveStoreRef, connectionStatus, renderCount } = useTelemetrySocket();

  const [selectedVesselId, setSelectedVesselId] = useState<string | null>(null);

  const vessels = useMemo(() => {
    return Array.from(liveStoreRef.current.vesselsById.values()).sort((a, b) =>
      a.vesselId.localeCompare(b.vesselId),
    );
  }, [liveStoreRef, renderCount]);

  const selectedVessel: VesselState | null =
    selectedVesselId === null
      ? null
      : (liveStoreRef.current.vesselsById.get(selectedVesselId) ?? null);

  return (
    <main className="dashboard">
      <header className="dashboard-header">
        <div>
          <h1>MaritimeOps Dashboard</h1>
          <p>Live C++ → UDP → C# → WebSocket vessel telemetry dashboard.</p>
        </div>

        <ConnectionStatusBadge
          status={connectionStatus}
          connectedClientCount={liveStoreRef.current.connectedClientCount}
        />
      </header>

      <section className="metrics-grid">
        <div className="metric-card">
          <span>Active</span>
          <strong>{liveStoreRef.current.activeVesselCount}</strong>
        </div>

        <div className="metric-card">
          <span>Stale</span>
          <strong>{liveStoreRef.current.staleVesselCount}</strong>
        </div>

        <div className="metric-card">
          <span>Total Seen</span>
          <strong>{vessels.length}</strong>
        </div>

        <div className="metric-card">
          <span>WS Msg/Sec</span>
          <strong>{liveStoreRef.current.messagesPerSecond}</strong>
        </div>

        <div className="metric-card">
          <span>Total WS Msg</span>
          <strong>{liveStoreRef.current.totalMessagesReceived}</strong>
        </div>

        <div className="metric-card">
          <span>Render Count</span>
          <strong>{renderCount}</strong>
        </div>
      </section>

      <section className="dashboard-grid">
        <div className="map-area">
          <CanvasMap
            liveStoreRef={liveStoreRef}
            selectedVesselId={selectedVesselId}
            onSelectVessel={setSelectedVesselId}
          />
        </div>

        <aside className="side-panel">
          <SelectedVesselPanel vessel={selectedVessel} />
          <AlertPanel vessels={vessels} />
        </aside>
      </section>

      <section className="bottom-grid">
        <VesselList
          vessels={vessels}
          selectedVesselId={selectedVesselId}
          onSelectVessel={setSelectedVesselId}
        />
      </section>
    </main>
  );
}

export default App;
