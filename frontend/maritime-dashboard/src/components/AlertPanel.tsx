import type { VesselState } from "../types/telemetry";
import {
  hasRestrictedZoneWarning,
  isLowFuel,
  isSignalDegraded,
} from "../utils/telemetryStatus";

interface AlertPanelProps {
  vessels: VesselState[];
}

interface AlertItem {
  vesselId: string;
  label: string;
  priority: number;
  kind: "danger" | "warning" | "info";
}

function buildAlerts(vessels: VesselState[]): AlertItem[] {
  const alerts: AlertItem[] = [];

  for (const vessel of vessels) {
    if (hasRestrictedZoneWarning(vessel)) {
      alerts.push({
        vesselId: vessel.vesselId,
        label: `${vessel.vesselId} restricted-zone warning`,
        priority: 1,
        kind: "danger",
      });
    }

    if (vessel.isStale) {
      alerts.push({
        vesselId: vessel.vesselId,
        label: `${vessel.vesselId} stale telemetry`,
        priority: 2,
        kind: "warning",
      });
    }

    if (isLowFuel(vessel)) {
      alerts.push({
        vesselId: vessel.vesselId,
        label: `${vessel.vesselId} low fuel: ${vessel.fuel.toFixed(1)}`,
        priority: 3,
        kind: "warning",
      });
    }

    if (isSignalDegraded(vessel)) {
      alerts.push({
        vesselId: vessel.vesselId,
        label: `${vessel.vesselId} signal degraded: ${vessel.signalStrength.toFixed(2)}`,
        priority: 4,
        kind: "info",
      });
    }
  }

  return alerts.sort((a, b) => {
    if (a.priority !== b.priority) {
      return a.priority - b.priority;
    }

    return a.vesselId.localeCompare(b.vesselId);
  });
}

export function AlertPanel({ vessels }: AlertPanelProps) {
  const alerts = buildAlerts(vessels);

  return (
    <div className="panel">
      <div className="panel-header">
        <h2>Alerts</h2>
        <span>{alerts.length}</span>
      </div>

      <div className="alert-list">
        {alerts.slice(0, 20).map((alert) => (
          <div
            className={`alert alert-${alert.kind}`}
            key={`${alert.vesselId}-${alert.label}`}
          >
            <span className="alert-priority">P{alert.priority}</span>
            {alert.label}
          </div>
        ))}

        {alerts.length > 20 && (
          <p className="muted">Showing top 20 of {alerts.length} alerts.</p>
        )}

        {alerts.length === 0 && <p className="muted">No current alerts.</p>}
      </div>
    </div>
  );
}
