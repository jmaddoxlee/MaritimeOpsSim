import type { ConnectionStatus } from "../types/telemetry";

interface ConnectionStatusBadgeProps {
  status: ConnectionStatus;
  connectedClientCount: number;
}

export function ConnectionStatusBadge({
  status,
  connectedClientCount,
}: ConnectionStatusBadgeProps) {
  return (
    <div className={`connection-badge connection-badge--${status}`}>
      <span className="connection-dot" />
      <span>{status}</span>
      <span className="connection-clients">
        clients: {connectedClientCount}
      </span>
    </div>
  );
}
