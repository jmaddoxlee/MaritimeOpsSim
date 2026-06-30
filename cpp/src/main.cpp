#include "Vessel.h"

#include <filesystem>
#include <iostream>

int main() {
    std::cout << "========================================\n";
    std::cout << " MaritimeOpsSim\n";
    std::cout << " AI-Assisted USV Mission Simulator\n";
    std::cout << "========================================\n\n";

    std::cout << "Project status: Week 1 setup\n";
    std::cout << "Mission focus: Search-and-rescue and maritime domain awareness\n\n";

    std::filesystem::path scenarioPath = "../scenarios/search_rescue_demo.json";

    std::cout << "Checking scenario file: " << scenarioPath << "\n";

    if (std::filesystem::exists(scenarioPath)) {
        std::cout << "Scenario file found.\n";
    } else {
        std::cout << "Scenario file not found yet.\n";
        std::cout << "Expected location: scenarios/search_rescue_demo.json\n";
    }

    Vessel vessel("USV-01", Position{100.0, 650.0}, 12.0, 0.0);

    std::cout << "Initial vessel telemetry:\n";
    vessel.printTelemetry();

    std::cout << "\nMaritimeOpsSim started successfully.\n";

    return 0;
}