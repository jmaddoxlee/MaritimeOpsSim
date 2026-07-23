import type { VesselState } from "../types/telemetry";

interface AlertPanelProps {
  vessels: VesselState[];
}

export function AlertPanel({ vessels }: AlertPanelProps) {
  const staleVessels = vessels.filter((vessel) => vessel.isStale);
  const lowFuelVessels = vessels.filter((vessel) => vessel.fuel <= 20);

  return (
    <div className="panel">
      <div className="panel-header">
        <h2>Alerts</h2>
        <span>{staleVessels.length + lowFuelVessels.length}</span>
      </div>

      <div className="alert-list">
        {staleVessels.map((vessel) => (
          <div className="alert alert-warning" key={`stale-${vessel.vesselId}`}>
            {vessel.vesselId} stale
          </div>
        ))}

        {lowFuelVessels.map((vessel) => (
          <div className="alert alert-danger" key={`fuel-${vessel.vesselId}`}>
            {vessel.vesselId} low fuel: {vessel.fuel.toFixed(1)}
          </div>
        ))}

        {staleVessels.length === 0 && lowFuelVessels.length === 0 && (
          <p className="muted">No current alerts.</p>
        )}
      </div>
    </div>
  );
}
