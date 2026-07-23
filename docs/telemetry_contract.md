# Telemetry Contract

## Purpose

The telemetry contract defines the wire format used between the C++ simulation layer and the C# ingestion backend.

Week 8 moves the project from a temporary fixed-size binary packet to a Protocol Buffers message.

---

## Current Wire Format

The current UDP payload is a serialized Protobuf message:

````proto
syntax = "proto3";

package maritimeops.telemetry;

option csharp_namespace = "MaritimeOps.Contracts.Telemetry";

message VesselTelemetry {
  string vessel_id = 1;
  uint64 timestamp_unix_ms = 2;
  double x = 3;
  double y = 4;
  double speed = 5;
  double heading = 6;
  double fuel = 7;
  double signal_strength = 8;
  uint32 status_flags = 9;
  uint64 sequence_number = 10;
}

## Telemetry Scope

Each telemetry packet represents one vessel snapshot at one point in simulated time.

A packet answers:

```text
What is the current state of this vessel right now?
````

The telemetry contract is focused on safe simulation state only:

- Vessel identity
- Timestamp
- Sequence number
- Position
- Speed
- Heading
- Fuel
- Signal strength
- Status flags

It does not include weapon targeting, fire-control logic, strike planning, or real-world tactical recommendations.

---

## Planned Telemetry Fields

| Field               | Type   | Purpose                                                           |
| ------------------- | ------ | ----------------------------------------------------------------- |
| `vessel_id`         | string | Unique vessel identifier such as `VESSEL-001`                     |
| `timestamp_unix_ms` | uint64 | Timestamp in Unix milliseconds                                    |
| `sequence_number`   | uint64 | Monotonic packet number for ordering and dropped-packet detection |
| `x`                 | double | Vessel x-position in the simulation map                           |
| `y`                 | double | Vessel y-position in the simulation map                           |
| `speed`             | double | Current vessel speed                                              |
| `heading`           | double | Current heading in degrees                                        |
| `fuel`              | double | Current fuel or energy level                                      |
| `signal_strength`   | double | Simulated communication signal quality                            |
| `status_flags`      | uint32 | Compact bitmask describing vessel state                           |

---

## Temporary Packet Format Before Protobuf

Before Protocol Buffers are added, the simulator will use a simple UTF-8 text packet format.

Temporary format:

```text
MOPS1|sequence_number|timestamp_unix_ms|vessel_id|x|y|speed|heading|fuel|signal_strength|status_flags
```

Example packet:

```text
MOPS1|42|1783545600000|VESSEL-001|55.00|50.00|5.00|0.00|99.75|1.00|1
```

Field meaning:

| Position | Field                       | Example         |
| -------- | --------------------------- | --------------- |
| 1        | Protocol/version marker     | `MOPS1`         |
| 2        | Sequence number             | `42`            |
| 3        | Timestamp Unix milliseconds | `1783545600000` |
| 4        | Vessel ID                   | `VESSEL-001`    |
| 5        | X-position                  | `55.00`         |
| 6        | Y-position                  | `50.00`         |
| 7        | Speed                       | `5.00`          |
| 8        | Heading                     | `0.00`          |
| 9        | Fuel                        | `99.75`         |
| 10       | Signal strength             | `1.00`          |
| 11       | Status flags                | `1`             |

This format is temporary and intentionally simple. It is useful because it can be inspected in logs, printed to the console, copied into tests, and parsed without adding a serialization dependency yet.

The C++ simulator should generate one packet per vessel snapshot.

---

## Status Flags

`status_flags` is a compact integer bitmask.

Each bit represents one vessel state.

| Flag                      | Bit | Value | Meaning                                    |
| ------------------------- | --: | ----: | ------------------------------------------ |
| `active`                  |   0 |   `1` | Vessel is active                           |
| `low_fuel`                |   1 |   `2` | Fuel is below threshold                    |
| `signal_degraded`         |   2 |   `4` | Signal strength is below threshold         |
| `out_of_bounds`           |   3 |   `8` | Vessel is outside the simulation map       |
| `restricted_zone_warning` |   4 |  `16` | Vessel is near or inside a restricted zone |

### Flag Examples

Active vessel only:

```text
status_flags = 1
```

Active vessel with low fuel:

```text
active + low_fuel = 1 + 2 = 3
status_flags = 3
```

Active vessel with degraded signal:

```text
active + signal_degraded = 1 + 4 = 5
status_flags = 5
```

Active vessel that is out of bounds and near a restricted zone:

```text
active + out_of_bounds + restricted_zone_warning = 1 + 8 + 16 = 25
status_flags = 25
```

Inactive vessel with no warnings:

```text
status_flags = 0
```

---

## Initial Flag Rules

The first implementation should use simple rules.

| Flag                      | Initial Rule                                        |
| ------------------------- | --------------------------------------------------- |
| `active`                  | Set when `vessel.active == true`                    |
| `low_fuel`                | Set when `fuel <= 20.0`                             |
| `signal_degraded`         | Set when `signalStrength < 0.5`                     |
| `out_of_bounds`           | Set when vessel position is outside map bounds      |
| `restricted_zone_warning` | Set when vessel is near or inside a restricted zone |

The first packet builder may only implement `active`, `low_fuel`, and `signal_degraded`.

`out_of_bounds` and `restricted_zone_warning` can be added when `MapGrid` and restricted-zone checks are connected to fleet telemetry.

---

## Temporary C++ Representation

The first C++ packet builder can use a lightweight struct before Protobuf is introduced.

```cpp
struct TelemetryPacket {
    std::uint64_t sequenceNumber;
    std::uint64_t timestampUnixMs;
    std::string vesselId;
    double x;
    double y;
    double speed;
    double heading;
    double fuel;
    double signalStrength;
    std::uint32_t statusFlags;
};
```

The packet builder should convert `VesselState` into this telemetry packet structure.

Conceptual flow:

```text
VesselState
    ↓
TelemetryPacket
    ↓
temporary text format
    ↓
UDP sender later
```

UDP transport is not part of this step. This step only defines the packet fields and temporary format.

---

## Future Protobuf Direction

After the temporary text format works, the same fields should move into a `.proto` schema.

Future Protobuf message shape:

```proto
syntax = "proto3";

message VesselTelemetry {
  string vessel_id = 1;
  uint64 timestamp_unix_ms = 2;
  uint64 sequence_number = 3;
  double x = 4;
  double y = 5;
  double speed = 6;
  double heading = 7;
  double fuel = 8;
  double signal_strength = 9;
  uint32 status_flags = 10;
}
```

The temporary text packet and Protobuf message should represent the same logical data.

---

## Design Notes

The telemetry packet format should stay small, predictable, and easy to validate.

Important design rules:

```text
one packet = one vessel snapshot
sequence numbers should increase predictably
timestamps should be explicit
status flags should be compact
packet builder should stay separate from UDP sending
simulation should not depend directly on the C# backend
```

This separation keeps the C++ simulation testable before networking is added.
