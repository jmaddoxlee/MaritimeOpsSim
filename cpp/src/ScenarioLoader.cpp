#include "ScenarioLoader.h"

#include <fstream>
#include <stdexcept>

#include <nlohmann/json.hpp>

ScenarioData ScenarioLoader::loadFromFile(const std::filesystem::path& filePath) const {
    std::ifstream file(filePath);

    if (!file.is_open()) {
        throw std::runtime_error("Failed to open scenario file: " + filePath.string());
    }

    nlohmann::json jsonData;
    file >> jsonData;

    ScenarioData scenario;

    scenario.mission.name = jsonData.at("mission").at("name").get<std::string>();
    scenario.mission.type = jsonData.at("mission").at("type").get<std::string>();
    scenario.mission.description = jsonData.at("mission").at("description").get<std::string>();

    scenario.map.width = jsonData.at("map").at("width").get<double>();
    scenario.map.height = jsonData.at("map").at("height").get<double>();
    scenario.map.unit = jsonData.at("map").at("unit").get<std::string>();

    for (const auto& vesselJson : jsonData.at("vessels")) {
        VesselConfig vessel;

        vessel.id = vesselJson.at("id").get<std::string>();
        vessel.startPosition = Position{
            vesselJson.at("startPosition").at("x").get<double>(),
            vesselJson.at("startPosition").at("y").get<double>()
        };
        vessel.speed = vesselJson.at("speed").get<double>();
        vessel.heading = vesselJson.at("heading").get<double>();
        vessel.battery = vesselJson.at("battery").get<double>();
        vessel.signalStrength = vesselJson.at("signalStrength").get<double>();

        scenario.vessels.push_back(vessel);
    }

    for (const auto& waypointJson : jsonData.at("waypoints")) {
        WaypointConfig waypoint;

        waypoint.id = waypointJson.at("id").get<std::string>();
        waypoint.position = Position{
            waypointJson.at("position").at("x").get<double>(),
            waypointJson.at("position").at("y").get<double>()
        };

        scenario.waypoints.push_back(waypoint);
    }

    return scenario;
}