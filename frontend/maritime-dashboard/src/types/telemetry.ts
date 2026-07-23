export type ConnectionStatus =
  | "connecting"
  | "connected"
  | "disconnected"
  | "reconnecting";

export interface VesselState {
  vesselId: string;
  sequenceNumber: number;
  timestampUtc: string;
  x: number;
  y: number;
  speed: number;
  heading: number;
  fuel: number;
  signalStrength: number;
  statusFlags: number;
  receivedAtUtc: string;
  isStale: boolean;
}

export interface TelemetrySnapshot {
  type: "snapshot";
  timestampUtc: string;
  activeVesselCount: number;
  staleVesselCount: number;
  vessels: VesselState[];
}

export interface TelemetryHeartbeat {
  type: "heartbeat";
  timestampUtc: string;
  connectedClientCount: number;
}

export type TelemetryMessage = TelemetrySnapshot | TelemetryHeartbeat;
