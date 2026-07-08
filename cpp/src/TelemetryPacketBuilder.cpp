#include "TelemetryPacketBuilder.h"

#include <bit>
#include <cctype>
#include <limits>
#include <stdexcept>
#include <string>

namespace {
    constexpr double kLowFuelThreshold = 20.0;
    constexpr double kSignalDegradedThreshold = 0.5;
    
    void appendUint32LittleEndian(
        std::vector<std::uint8_t>& bytes,
        std::uint32_t value
    ) {
        for (int shift = 0; shift <32; shift += 8) {
            bytes.push_back(static_cast<std::uint8_t>((value >> shift) & 0xFF));
        }
    }

    void appendUint64LittleEndian(
        std::vector<std::uint8_t>& bytes,
        std::uint32_t value
    ) {
        for (int shift = 0; shift <64; shift += 8) {
            bytes.push_back(static_cast<std::uint8_t>((value >> shift) & 0xFF));
        }
    }

    void appendDoubleLittleEndian(
        std::vector<std::uint8_t>& bytes,
        double value
    ) {
        const std::uint64_t rawValue = std::bit_cast<std::uint64_t>(value);
        appendUint64LittleEndian(bytes, rawValue);
    }
}

std::vector<std::uint8_t> TelemetryPacketBuilder::buildPacket(
    const VesselState& vessel,
    std::uint64_t sequenceNumber,
    std::uint64_t timestampUnixMs
) {
    std::vector<std::uint8_t> packet;
    packet.reserve(kPacketSizeBytes);

    appendUint64LittleEndian(packet, sequenceNumber);
    appendUint64LittleEndian(packet, timestampUnixMs);
    appendUint32LittleEndian(packet, extractVesselNumericId(vessel.id));
    appendDoubleLittleEndian(packet, vessel.position.x);
    appendDoubleLittleEndian(packet, vessel.position.y);
    appendDoubleLittleEndian(packet, vessel.speed);
    appendDoubleLittleEndian(packet, vessel.heading);
    appendDoubleLittleEndian(packet, vessel.fuel);
    appendDoubleLittleEndian(packet, vessel.signalStrength);
    appendUint32LittleEndian(packet, buildStatusFlags(vessel));

    return packet;
}

std::uint32_t TelemetryPacketBuilder::buildStatusFlags(
    const VesselState& vessel
) {
    std::uint32_t flags = 0;

    if (vessel.active) {
        flags |= TelemetryStatusFlags::Active;
    }

    if (vessel.fuel <= kLowFuelThreshold) {
        flags |= TelemetryStatusFlags::LowFuel;
    }

    if (vessel.signalStrength < kSignalDegradedThreshold) {
        flags |= TelemetryStatusFlags::SignalDegraded;
    }

    // OutOfBounds and RestrictedZoneWarning will be connected later
    // when MapGrid/restricted-zone checks are wired into fleet telemetry.

    return flags;
}

std::uint32_t TelemetryPacketBuilder::extractVesselNumericId(
    const std::string& vesselId
) {
    std::string digits;

    for (unsigned char character : vesselId) {
        if (std::isdigit(character)) {
            digits.push_back(static_cast<char>(character));
        }
    }

    if (digits.empty()) {
        return 0;
    }

    const unsigned long long value = std::stoull(digits);

    if (value > std::numeric_limits<std::uint32_t>::max()) {
        throw std::out_of_range("Vessel numeric ID exceeds uint32 range");
    }

    return static_cast<std::uint32_t>(value);
}