#pragma once

#include "VesselState.h"

#include <vector>

class FleetSimulationEngine {
    public:
        explicit FleetSimulationEngine(std::vector<VesselState> vessels);

        void update(double deltaTimeSeconds);

        const std::vector<VesselState>& getVessels() const;

    private:
        static void updateVesselPosition(VesselState& vessel, double deltaTimeSeconds);

        std::vector<VesselState> vessels_;
};