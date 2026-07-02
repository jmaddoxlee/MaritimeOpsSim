#include "ScenarioLoader.h"

#include <fstream>
#include <stdexcept>
#include <string>

#include <nlohmann/json.hpp>

namespace {
    using json = nlohmann::json;

    void requireField(const json& object, const std::string& field, const std::string& context) {
        if (!object.contains(field)) {
            throw std::runtime_error(
                "Invalid scenario: missing required field '" + context + "." + field + "'"
            );
        }
    }

    const json& getObject(const json& object, const std::string& field, const std::string& context) {
        requireField(object, field, context);

        if (!object.at(field).is_object()) {
            throw std::runtime_error(
                "Invalid scenario: field '" + context + "." + field + "' must be an object"
            );
        }
        return object.at(field);
    }

    const json& getArray(const json& object, const std::string& field, const std::string& context) {
        requireField(object, field, context);

        if (!object.at(field).is_array()) {
            throw std::runtime_error(
                "Invalid scenario: field '" + context + "." + field + "' must be an array"
            );
        }
        return object.at(field);
    }

    std::string getString(const json& object, const std::string& field, const std::string& context) {
        requireField(object, field, context);

        if (!object.at(field).is_string()) {
            throw std::runtime_error(
                "Invalid scenario: field '" + context + "." + field + "' must be a string"
            );
        }
        return object.at(field).get<std::string>();
    }

    double getDouble(const json& object, const std::string& field, const std::string& context) {
        requireField(object, field, context);

        if (!object.at(field).is_number()) {
            throw std::runtime_error(
                "Invalid scenario: field '" + context + "." + field + "' must be a number"
            );
        }
        return object.at(field).get<double>();
    }

    Position getPositionFromObject(const json& object, const std::string& context) {
        return Position{
            getDouble(object, "x", context),
            getDouble(object, "y", context)
        };
    }

    ObstacleConfig parseObstacle(const json& obstacleJson, const std::string& context) {
        ObstacleConfig obstacle;

        obstacle.id = getString(obstacleJson, "id", context);
        obstacle.x = getDouble(obstacleJson, "x", context);
        obstacle.y = getDouble(obstacleJson, "y", context);
        obstacle.width = getDouble(obstacleJson, "width", context);
        obstacle.height = getDouble(obstacleJson, "height", context);

        return obstacle;
    }

    RestrictedZoneConfig parseRestrictedZone(const json& zoneJson, const std::string& context) {
        RestrictedZoneConfig zone;

        zone.id = getString(zoneJson, "id", context);
        zone.x = getDouble(zoneJson, "x", context);
        zone.y = getDouble(zoneJson, "y", context);
        zone.width = getDouble(zoneJson, "width", context);
        zone.height = getDouble(zoneJson, "height", context);

        return zone;
    }
}

ScenarioData ScenarioLoader::loadFromFile(const std::filesystem::path& filePath) const {
    std::ifstream file(filePath);

    if (!file.is_open()) {
        throw std::runtime_error("Failed to open scenario file: " + filePath.string());
    }

    nlohmann::json jsonData;

    try {
        file >> jsonData;
    } catch (const json::parse_error&error) {
        throw std::runtime_error(
            std::string("Invalid scenario: failed to parse JSON. ") + error.what()
        );
    }

    if (!jsonData.is_object()) {
        throw std::runtime_error("Invalid scenario: root JSON value must be an object");
    }

    ScenarioData scenario;

    const json& missionJson = getObject(jsonData, "mission", "root");
    scenario.mission.name = getString(missionJson, "name", "mission");
    scenario.mission.type = getString(missionJson, "type", "mission");
    scenario.mission.description = getString(missionJson, "description", "mission");

    const json& mapJson = getObject(jsonData, "map", "root");
    scenario.map.width = getDouble(mapJson, "width", "map");
    scenario.map.height = getDouble(mapJson, "height", "map");
    scenario.map.unit = getString(mapJson, "unit", "map");

    if (scenario.map.width <= 0 || scenario.map.height <= 0) {
        throw std::runtime_error("Invalid scenario: map width and height must be greater than 0");
    }

    const json& vesselsJson = getArray(jsonData, "vessels", "root");

    if (vesselsJson.empty()) {
        throw std::runtime_error("Invalid scenario: vessels array must contain at least one vessel");
    }

    for (std::size_t i = 0; i < vesselsJson.size(); ++i) {
        const json& vesselJson = vesselsJson.at(i);
        const std::string context = "vessels[" + std::to_string(i) + "]";

        if (!vesselJson.is_object()) {
            throw std::runtime_error("Invalid scenario: " + context + " must be an object");
        }

        VesselConfig vessel;

        vessel.id = getString(vesselJson, "id", context);

        const json& startPositionJson = getObject(vesselJson, "startPosition", context);
        vessel.startPosition = getPositionFromObject(startPositionJson, context + ".startPosition");

        vessel.speed = getDouble(vesselJson, "speed", context);
        vessel.heading = getDouble(vesselJson, "heading", context);
        vessel.battery = getDouble(vesselJson, "battery", context);
        vessel.signalStrength = getDouble(vesselJson, "signalStrength", context);

        if (vessel.battery < 0.0) {
            throw std::runtime_error("Invalid scenario: " + context + ".battery cannot be negative");
        }

        scenario.vessels.push_back(vessel);
    }

    const json& waypointsJson = getArray(jsonData, "waypoints", "root");

    for (std::size_t i = 0; i < waypointsJson.size(); ++i) {
        const json& waypointJson = waypointsJson.at(i);
        const std::string context = "waypoints[" + std::to_string(i) + "]";

        if (!waypointJson.is_object()) {
            throw std::runtime_error("Invalid scenario: " + context + " must be an object");
        }

        WaypointConfig waypoint;

        waypoint.id = getString(waypointJson, "id", context);

        const json& waypointPositionJson = getObject(
            waypointJson,
            "position",
            context
        );

        waypoint.position = getPositionFromObject(
            waypointPositionJson,
            context + ".position"
        );

        scenario.waypoints.push_back(waypoint);
    }

    const json& obstaclesJson = getArray(jsonData, "obstacles", "root");

    for (std::size_t i = 0; i < obstaclesJson.size(); ++i) {
        const json& obstacleJson = obstaclesJson.at(i);
        const std::string context = "obstacles[" + std::to_string(i) + "]";

        if (!obstacleJson.is_object()) {
            throw std::runtime_error("Invalid scenario: " + context + " must be an object");
        }

        scenario.obstacles.push_back(parseObstacle(obstacleJson, context));
    }

    const json& restrictedZonesJson = getArray(jsonData, "restrictedZones", "root");

    for (std::size_t i = 0; i < restrictedZonesJson.size(); ++i) {
        const json& zoneJson = restrictedZonesJson.at(i);
        const std::string context = "restrictedZones[" + std::to_string(i) + "]";

        if (!zoneJson.is_object()) {
            throw std::runtime_error("Invalid scenario: " + context + " must be an object");
        }

        scenario.restrictedZones.push_back(parseRestrictedZone(zoneJson, context));
    }

    const json& distressBeaconJson = getObject(jsonData, "distressBeacon", "root");
    scenario.distressBeacon.id = getString(distressBeaconJson, "id", "distressBeacon");

    const json& distressPositionJson = getObject(distressBeaconJson, "position", "distressBeacon");
    scenario.distressBeacon.position =
        getPositionFromObject(distressPositionJson, "distressBeacon.position");

    const json& missionRulesJson = getObject(jsonData, "missionRules", "root");
    scenario.missionRules.successCondition =
        getString(missionRulesJson, "successCondition", "missionRules");

    const json& failureConditionsJson =
        getArray(missionRulesJson, "failureConditions", "missionRules");

    for (const json& conditionJson : failureConditionsJson) {
        if (!conditionJson.is_string()) {
            throw std::runtime_error(
                "Invalid scenario: missionRules.failureConditions must contain strings"
            );
        }

        scenario.missionRules.failureConditions.push_back(conditionJson.get<std::string>());
    }

    return scenario;
}