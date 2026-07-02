#include "MapGrid.h"
#include "Mission.h"
#include "ScenarioData.h"
#include "ScenarioLoader.h"
#include "SimulationEngine.h"
#include "Vessel.h"

#include <exception>
#include <filesystem>
#include <iostream>
#include <sstream>
#include <vector>

std::filesystem::path resolveScenarioPath() {
    const std::vector<std::filesystem::path> candidates = {
        "scenarios/search_rescue_demo.json",
        "../scenarios/search_rescue_demo.json"
    };

    for (const std::filesystem::path& candidate : candidates) {
        if (std::filesystem::exists(candidate)) {
            return candidate;
        }
    }

    std::ostringstream message;
    message << "Could not find scenario file. Checked paths:";

    for (const std::filesystem::path& candidate : candidates) {
        message << "\n- " << std::filesystem::absolute(candidate);
    }

    throw std::runtime_error(message.str());
}

int main() {
    std::cout << "========================================\n";
    std::cout << " MaritimeOpsSim\n";
    std::cout << " AI-Assisted USV Mission Simulator\n";
    std::cout << "========================================\n\n";

    std::cout << "Project status: Week 3 scenario loader setup\n";
    std::cout << "Mission focus: Search-and-rescue and maritime domain awareness\n\n";

    try {
        const std::filesystem::path scenarioPath = resolveScenarioPath();

        std::cout << "Loading scenario file: " << scenarioPath << "\n";
        std::cout << "Current working directory: "
                  << std::filesystem::current_path()
                  << "\n\n";

        ScenarioLoader loader;
        ScenarioData scenario = loader.loadFromFile(scenarioPath);

        std::cout << "Scenario file loaded successfully.\n\n";

        std::cout << "Loaded scenario:\n";
        std::cout << "Mission Name: " << scenario.mission.name << "\n";
        std::cout << "Mission Type: " << scenario.mission.type << "\n";
        std::cout << "Map Width: " << scenario.map.width << " " << scenario.map.unit << "\n";
        std::cout << "Map Height: " << scenario.map.height << " " << scenario.map.unit << "\n";
        std::cout << "Vessel Count: " << scenario.vessels.size() << "\n";
        std::cout << "Waypoint Count: " << scenario.waypoints.size() << "\n";
        std::cout << "Obstacle Count: " << scenario.obstacles.size() << "\n";
        std::cout << "Restricted Zone Count: " << scenario.restrictedZones.size() << "\n\n";

        if (scenario.vessels.empty()) {
            std:: cerr << "Scenario error: no vessels found.\n";
            return 1;
        }

        // const VesselConfig& vesselConfig = scenario.vessels.front();

        // Mission mission(scenario.mission.name, scenario.mission.type);

        // Vessel vessel(
        //     vesselConfig.id,
        //     vesselConfig.startPosition,
        //     vesselConfig.speed,
        //     vesselConfig.heading
        // );

        MapGrid mapGrid(
            scenario.map.width,
            scenario.map.height,
            scenario.obstacles,
            scenario.restrictedZones
        );

        std::cout << "Loaded vessel:\n";

        for (const VesselConfig& loadedVessel : scenario.vessels) {
            std::cout << "ID: " << loadedVessel.id << "\n";
            std::cout << "Start Position: x="
                      << loadedVessel.startPosition.x
                      << ", y="
                      << loadedVessel.startPosition.y
                      << "\n";
            std::cout << "Speed: " << loadedVessel.speed << "\n";
            std::cout << "Heading: " << loadedVessel.heading << "\n\n";
        }

        std::cout << "Loaded waypoints:\n";

        for (const WaypointConfig& waypoint : scenario.waypoints) {
            std::cout << waypoint.id
                      << " -> x="
                      << waypoint.position.x
                      << ", y="
                      << waypoint.position.y
                      << "\n";
        }

        std::cout << "\nLoaded obstacles:\n";

        for (const ObstacleConfig& obstacle : scenario.obstacles) {
            std::cout << obstacle.id
                      << " -> x="
                      << obstacle.x
                      << ", y="
                      << obstacle.y
                      << ", width="
                      << obstacle.width
                      << ", height="
                      << obstacle.height
                      << "\n";
        }

        std::cout << "\nLoaded restricted zones:\n";

        for (const RestrictedZoneConfig& zone : scenario.restrictedZones) {
            std::cout << zone.id
                      << " -> x="
                      << zone.x
                      << ", y="
                      << zone.y
                      << ", width="
                      << zone.width
                      << ", height="
                      << zone.height
                      << "\n";
        }

        std::cout << "\n";

        const VesselConfig& vesselConfig = scenario.vessels.front();

        if (!mapGrid.isInsideBounds(vesselConfig.startPosition)) {
            std::cerr << "Scenario error: vessel start position is outside map bounds.\n";
            return 1;
        }

        if (mapGrid.isInsideObstacle(vesselConfig.startPosition)) {
            std::cerr << "Scenario error: vessel starts inside an obstacle.\n";
            return 1;
        }

        if (mapGrid.isInsideRestrictedZone(vesselConfig.startPosition)) {
            std::cerr << "Scenario error: vessel starts inside a restricted zone.\n";
            return 1;
        }

        Mission mission(scenario.mission.name, scenario.mission.type);

        Vessel vessel(
            vesselConfig.id,
            vesselConfig.startPosition,
            vesselConfig.speed,
            vesselConfig.heading
        );

        SimulationEngine engine(
            mission,
            vessel,
            1.0,
            10
        );

        engine.run();

        std::cout << "\nMaritimeOpsSim finished successfully.\n";
    } catch (const std::exception& error) {
        std::cerr << "Failed to load scenario: " << error.what() << "\n";
        return 1;
    }

    return 0;
}