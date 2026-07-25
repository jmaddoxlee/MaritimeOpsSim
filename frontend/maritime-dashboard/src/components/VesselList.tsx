import type { VesselState } from "../types/telemetry";
import { getVesselStatusLabel } from "../utils/telemetryStatus";

interface VesselListProps {
  vessels: VesselState[];
  selectedVesselId: string | null;
  onSelectVessel: (vesselId: string) => void;
}

export function VesselList({
  vessels,
  selectedVesselId,
  onSelectVessel,
}: VesselListProps) {
  return (
    <div className="panel">
      <div className="panel-header">
        <h2>Raw Vessel List</h2>
        <span>{vessels.length} vessels</span>
      </div>

      <div className="vessel-list">
        {vessels.map((vessel) => {
          const statusLabel = getVesselStatusLabel(vessel);

          return (
            <button
              key={vessel.vesselId}
              className={
                vessel.vesselId === selectedVesselId
                  ? "vessel-row vessel-row--selected"
                  : "vessel-row"
              }
              type="button"
              onClick={() => onSelectVessel(vessel.vesselId)}
            >
              <span className="vessel-id">{vessel.vesselId}</span>
              <span>x {vessel.x.toFixed(1)}</span>
              <span>y {vessel.y.toFixed(1)}</span>
              <span
                className={`vessel-status vessel-status--${statusLabel.replace(" ", "-")}`}
              >
                {statusLabel}
              </span>
            </button>
          );
        })}
      </div>
    </div>
  );
}
