#include "SimulationEngine.h"

#include <iostream>
#include <utility>

SimulationEngine::SimulationEngine(
    Mission mission,
    Vessel vessel,
    double timeStepSeconds,
    int maxSteps
)
    : mission_(std::move(mission)),
      vessel_(std::move(vessel)),
      timeStepSeconds_(timeStepSeconds),
      maxSteps_(maxSteps),
      currentStep_(0) {}

void SimulationEngine::run() {
    std::cout << "Starting simulation...\n\n";

    mission_.start();

    std::cout << "Initial mission state:\n";
    mission_.printStatus();
    std::cout << "\n";

    std::cout << "Initial vessel state:\n";
    vessel_.printTelemetry();
    std::cout << "\n";

    while (mission_.isRunning() && currentStep_ < maxSteps_) {
        update();
    }

    if (mission_.isRunning()) {
        mission_.complete();
    }

    std::cout << "Simulation complete.\n\n";

    std::cout << "Final mission state:\n";
    mission_.printStatus();
    std::cout << "\n";

    std::cout << "Final vessel state:\n";
    vessel_.printTelemetry();
}

void SimulationEngine::update() {
    ++currentStep_;

    mission_.update(timeStepSeconds_);
    vessel_.update(timeStepSeconds_);

    printStepHeader();

    std::cout << "Mission Time: "
              << mission_.getElapsedTimeSeconds()
              << " seconds\n";

    vessel_.printTelemetry();

    std::cout << "\n";
}

void SimulationEngine::printStepHeader() const {
    std::cout << "----------------------------------------\n";
    std::cout << "Simulation Step: " << currentStep_ << "\n";
}