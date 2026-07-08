#pragma once

#include "VesselState.h"

#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

namespace TelemetryStatusFlags {
    constexpr std::uint32_t Active = 1 << 0;
    constexpr std::uint32_t LowFuel = 1 << 1;
    constexpr std::uint32_t SignalDegraded = 1 << 2;
    constexpr std::uint32_t OutofBounds = 1 << 3;
    constexpr std::uint32_t RestrictedZoneWarning = 1 << 4;
}

class TelemetryPacketBuilder {
    public:
        static constexpr std::size_t kPacketSizeBytes = 72;

        static std::vector<std::uint8_t> buildPacket(
            const VesselState& vessel,
            std::uint64_t sequenceNumber,
            std::uint64_t timestampUnixMs
        );

        static std::uint32_t buildStatusFlags(const VesselState& vessel);

        static std::uint32_t extractVesselNumericId(const std::string& vesselId);
};