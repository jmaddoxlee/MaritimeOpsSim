#include "FleetSimulationEngine.h"

#include <cmath>
#include <utility>

namespace {
    constexpr double kPi = 3.14159265358979323846;

    constexpr double kFuelBurnRatePerSpeedUnitPerSecond = 0.05;
}

FleetSimulationEngine::FleetSimulationEngine(std::vector<VesselState> vessels)
    : vessels_(std::move(vessels)) {
}

void FleetSimulationEngine::update(double deltaTimeSeconds) {
    if (deltaTimeSeconds <= 0.0) {
        return;
    }

    for (VesselState &vessel : vessels_) {
        if (!vessel.active) {
            continue;
        }

        updateVesselPosition(vessel, deltaTimeSeconds);
        updateVesselFuel(vessel, deltaTimeSeconds);
        udpateSignalStrength(vessel, deltaTimeSeconds);
    }
}

const std::vector<VesselState>& FleetSimulationEngine::getVessels() const {
    return vessels_;
}

void FleetSimulationEngine::updateVesselPosition(
    VesselState& vessel,
    double deltaTimeSeconds
) {
    const double headingRadians = vessel.heading * kPi / 180.0;

    vessel.position.x += std::cos(headingRadians) * vessel.speed * deltaTimeSeconds;
    vessel.position.y += std::sin(headingRadians) * vessel.speed * deltaTimeSeconds; 
}

void FleetSimulationEngine::updateVesselFuel(
    VesselState& vessel,
    double deltaTimeSeconds
) {
    const double fuelBurn = 
        vessel.speed * kFuelBurnRatePerSpeedUnitPerSecond * deltaTimeSeconds;

    vessel.fuel = std::max(0.0, vessel.fuel - fuelBurn);
}

void FleetSimulationEngine::udpateSignalStrength(
    VesselState& vessel,
    double deltaTimeSeconds
) {
    (void)vessel;
    (void)deltaTimeSeconds;
}