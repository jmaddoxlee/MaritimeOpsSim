#include "Vessel.h"
#include "Mission.h"

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

    Mission mission("Search Rescue Demo", "search_and_rescue");
    Vessel vessel("USV-01", Position{100.0, 650.0}, 12.0, 0.0);

    std::cout << "Initial mission status:\n";
    mission.printStatus();

    std::cout << "\nStarting mission...\n";
    mission.start();

    mission.update(1.0);
    mission.update(1.0);
    mission.update(1.0);

    std::cout << "\nUpdated mission status:\n";
    mission.printStatus();

    std::cout << "\nInitial vessel telemetry:\n";
    vessel.printTelemetry();

    std::cout << "\nCompleting mission for Week 2 test...\n";
    mission.complete();

    std::cout << "\nFinal mission status:\n";
    mission.printStatus();

    std::cout << "\nMaritimeOpsSim started successfully.\n";

    return 0;
}