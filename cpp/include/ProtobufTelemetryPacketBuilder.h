#pragma once

#include "VesselState.h"

#include <cstdint>
#include <vector>

class ProtobufTelemetryPacketBuilder {
public:
    static std::vector<std::uint8_t> buildPacket(
        const VesselState& vessel,
        std::uint64_t sequenceNumber,
        std::uint64_t timestampUnixMs
    );

    static std::vector<std::uint8_t> buildPacketWithGeneratedMetadata(
        const VesselState& vessel
    );
};