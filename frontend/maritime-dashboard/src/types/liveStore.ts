import type { VesselState } from "./telemetry";

export interface LiveVesselStore {
  vesselsById: Map<string, VesselState>;
  lastSnapshotTimeUtc: string | null;
  activeVesselCount: number;
  staleVesselCount: number;
  connectedClientCount: number;

  totalMessagesReceived: number;
  messagesPerSecond: number;
}
