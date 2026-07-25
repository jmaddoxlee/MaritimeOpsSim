import type { VesselState } from "../types/telemetry";

export const TelemetryStatusFlags = {
  active: 1 << 0,
  lowFuel: 1 << 1,
  signalDegraded: 1 << 2,
  outOfBounds: 1 << 3,
  restrictedZoneWarning: 1 << 4,
} as const;

export function hasStatusFlag(vessel: VesselState, flag: number): boolean {
  return (vessel.statusFlags & flag) !== 0;
}

export function isLowFuel(vessel: VesselState): boolean {
  return (
    vessel.fuel <= 20 || hasStatusFlag(vessel, TelemetryStatusFlags.lowFuel)
  );
}

export function isSignalDegraded(vessel: VesselState): boolean {
  return (
    vessel.signalStrength < 0.5 ||
    hasStatusFlag(vessel, TelemetryStatusFlags.signalDegraded)
  );
}

export function hasRestrictedZoneWarning(vessel: VesselState): boolean {
  return hasStatusFlag(vessel, TelemetryStatusFlags.restrictedZoneWarning);
}

export function getVesselStatusLabel(vessel: VesselState): string {
  if (vessel.isStale) {
    return "stale";
  }

  if (hasRestrictedZoneWarning(vessel)) {
    return "restricted";
  }

  if (isLowFuel(vessel)) {
    return "low fuel";
  }

  if (isSignalDegraded(vessel)) {
    return "signal";
  }

  return "active";
}
