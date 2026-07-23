import type { VesselState } from "../types/telemetry";

interface SelectedVesselPanelProps {
  vessel: VesselState | null;
}

export function SelectedVesselPanel({ vessel }: SelectedVesselPanelProps) {
  if (!vessel) {
    return (
      <div className="panel">
        <div className="panel-header">
          <h2>Selected Vessel</h2>
        </div>
        <p className="muted">Click a vessel dot or list item to inspect it.</p>
      </div>
    );
  }

  return (
    <div className="panel">
      <div className="panel-header">
        <h2>Selected Vessel</h2>
        <span className={vessel.isStale ? "status-stale" : "status-active"}>
          {vessel.isStale ? "stale" : "active"}
        </span>
      </div>

      <div className="detail-grid">
        <span>ID</span>
        <strong>{vessel.vesselId}</strong>

        <span>X / Y</span>
        <strong>
          {vessel.x.toFixed(2)} / {vessel.y.toFixed(2)}
        </strong>

        <span>Speed</span>
        <strong>{vessel.speed.toFixed(2)}</strong>

        <span>Heading</span>
        <strong>{vessel.heading.toFixed(2)}°</strong>

        <span>Fuel</span>
        <strong>{vessel.fuel.toFixed(2)}</strong>

        <span>Signal</span>
        <strong>{vessel.signalStrength.toFixed(2)}</strong>

        <span>Sequence</span>
        <strong>{vessel.sequenceNumber}</strong>
      </div>
    </div>
  );
}
