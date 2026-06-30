#include "Mission.h"
#include "ScenarioData.h"
#include "ScenarioLoader.h"
#include "SimulationEngine.h"
#include "Vessel.h"

#include <exception>
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

    try {
        ScenarioLoader loader;
        ScenarioData scenario = loader.loadFromFile(scenarioPath);

        std::cout << "Scenario file loaded successfully.\n\n";

        std::cout << "Loaded scenario:\n";
        std::cout << "Mission Name: " << scenario.mission.name << "\n";
        std::cout << "Mission Type: " << scenario.mission.type << "\n";
        std::cout << "Map Width: " << scenario.map.width << " " << scenario.map.unit << "\n";
        std::cout << "Map Height: " << scenario.map.height << " " << scenario.map.unit << "\n";
        std::cout << "Waypoint Count: " << scenario.waypoints.size() << "\n\n";

        if (scenario.vessels.empty()) {
            std:: cerr << "Scenario error: no vessels found.\n";
            return 1;
        }

        const VesselConfig& vesselConfig = scenario.vessels.front();

        Mission mission(scenario.mission.name, scenario.mission.type);

        Vessel vessel(
            vesselConfig.id,
            vesselConfig.startPosition,
            vesselConfig.speed,
            vesselConfig.heading
        );

        std::cout << "Loaded vessel:\n";
        std::cout << "ID: " << vesselConfig.id << "\n";
        std::cout << "Start Position: x="
                  << vesselConfig.startPosition.x
                  << ", y="
                  << vesselConfig.startPosition.y
                  << "\n";
        std::cout << "Speed: " << vesselConfig.speed << "\n";
        std::cout << "Heading: " << vesselConfig.heading << "\n\n";

        std::cout << "Loaded waypoints:\n";
        for (const WaypointConfig& waypoint : scenario.waypoints) {
            std::cout << waypoint.id
                      << " -> x="
                      << waypoint.position.x
                      << ", y="
                      << waypoint.position.y
                      << "\n";
        }

        std::cout << "\n";

        SimulationEngine engine(
            mission,
            vessel,
            1.0,
            10
        );

        engine.run();

        std::cout << "\nMaritimeOpsSim finished successfully.\n";
    } catch (const std::exception& error) {
        std:: cerr << "Failed to load scenario " << error.what() << "\n";
        return 1;
    }

    return 0;
}