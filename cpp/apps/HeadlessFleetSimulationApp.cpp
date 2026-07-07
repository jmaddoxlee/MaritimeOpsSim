#include "FleetGeneration.h"
#include "FleetSimulationEngine.h"
#include "VesselState.h"

#include <iomanip>
#include <iostream>
#include <numeric>
#include <vector>

namespace {
    constexpr std::size_t kDefaultVesselCount = 100;
    constexpr int kDefaultDurationSeconds = 60;
    constexpr double kDeltaTimeSeconds = 1.0;

    double calculateAverageFuel(const std::vector<VesselState>& vessels) {
        if (vessels.empty()) {
            return 0.0;
        }

        const double totalFuel = std::accumulate(
            vessels.begin(),
            vessels.end(),
            0.0,
            [](double total, const VesselState& vessel) {
                return total + vessel.fuel;
            }
        );

        return totalFuel / static_cast<double>(vessels.size());
    }

    void printFleetSummary(int tick, const std::vector<VesselState>& vessels) {
        std::cout << std::fixed << std::setprecision(2);

        std::cout << "tick=" << tick << " totalVessels=" << vessels.size();

        if (!vessels.empty()) {
            const VesselState& firstVessel = vessels.front();

            std::cout << " firstVessel=" << firstVessel.id << " Position=(" << firstVessel.position.x << ", " << firstVessel.position.y << ")";
        }

        std::cout << " avgFuel =" << calculateAverageFuel(vessels) << '\n';
    }
}

int main() {
    std::vector<VesselState> vessels = createSampleFleet(kDefaultVesselCount);

    FleetSimulationEngine engine(vessels);

    std::cout << "MaritimeOpsSim Headless Fleet Simulation\n";
    std::cout << "mode=headless\n";
    std::cout << "vessels=" << kDefaultVesselCount << '\n';
    std::cout << "durationSeconds=" << kDefaultDurationSeconds << '\n';
    std::cout << "deltaTimeSeconds=" << kDeltaTimeSeconds << "\n\n";

    printFleetSummary(0, engine.getVessels());

    for (int tick = 1; tick < kDefaultDurationSeconds; ++tick) {
        engine.update(kDeltaTimeSeconds);
        printFleetSummary(tick, engine.getVessels());
    }

    return 0;
}