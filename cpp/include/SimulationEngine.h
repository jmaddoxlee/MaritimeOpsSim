#pragma once

#include "Mission.h"
#include "Vessel.h"

class SimulationEngine {
    public:
        SimulationEngine(Mission mission, Vessel vessel, double timeStepSeconds, int maxSteps);

        void run();

    private:
        void update();
        void printStepHeader() const;

        Mission mission_;
        Vessel vessel_;
        double timeStepSeconds_;
        int maxSteps_;
        int currentStep_;
};