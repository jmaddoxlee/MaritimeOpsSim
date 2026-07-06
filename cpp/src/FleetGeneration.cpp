#include "FleetGeneration.h"

#include <iomanip>
#include <sstream>
#include <string>

namespace {
    constexpr std::size_t kFleetGridColumns = 10;
    constexpr double kStartX = 50.0;
    constexpr double kStartY = 50.0;
    constexpr double kSpacingX = 25.0;
    constexpr double kSpacingY = 25.0;

    std::string buildVesselId(std::size_t index) {
        std::ostringstream stream;
        stream << "VESSEL-" << std::setw(3) << std::setfill('0') << index + 1;
        return stream.str(); 
    }

    Position calculateStartingPosition(std::size_t index) {
        const std::size_t column = index % kFleetGridColumns;
        const std::size_t row = index / kFleetGridColumns;

        return Position{
            kStartX + static_cast<double>(column) * kSpacingX,
            kStartY + static_cast<double>(row) * kSpacingY
        };
    }
}

std::vector<VesselState> createSampleFleet(std::size_t vesselCount) {
    std::vector<VesselState> vessels;
    vessels.reserve(vesselCount);

    for (std::size_t index = 0; index < vesselCount; ++index) {
        VesselState vessel{};
        vessel.id = buildVesselId(index);
        vessel.position = calculateStartingPosition(index);
        vessel.speed = 5.0 + static_cast<double>(index % 5);
        vessel.heading = static_cast<double>((index * 15) % 360);
        vessel.fuel = 100.0;
        vessel.signalStrength = 1.0;
        vessel.active = true;

        vessels.push_back(vessel);
    }

    return vessels;
}