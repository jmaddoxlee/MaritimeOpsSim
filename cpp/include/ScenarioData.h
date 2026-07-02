#pragma once

#include "Vessel.h"

#include <string>
#include <vector>

struct MissionConfig {
    std::string name;
    std::string type;
    std::string description;
};

struct MissionMap {
    double width;
    double height;
    std::string unit;
};

struct VesselConfig {
    std::string id;
    Position startPosition;
    double speed;
    double heading;
    double battery;
    double signalStrength;
};

struct WaypointConfig {
    std::string id;
    Position position;
};

struct ObstacleConfig {
    std::string id;
    double x;
    double y;
    double height;
    double width;
};

struct RestrictedZoneConfig {
    std::string id;
    double x;
    double y;
    double width;
    double height;
};

struct DistressBeaconConfig {
    std::string id;
    Position position;
};

struct MissionRuleConfig {
    std::string successCondition;
    std::vector<std::string> failureConditions;
};

struct ScenarioData {
    MissionConfig mission;
    MissionMap map;
    std::vector<VesselConfig> vessels;
    std::vector<WaypointConfig> waypoints;
    std::vector<ObstacleConfig> obstacles;
    std::vector<RestrictedZoneConfig> restrictedZones;
    DistressBeaconConfig distressBeacon;
    MissionRuleConfig missionRules;
};