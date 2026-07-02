#include "ScenarioLoader.h"

#include <filesystem>
#include <fstream>
#include <stdexcept>
#include <string>

#include <gtest/gtest.h>

namespace {
    std::filesystem::path findFile(
        const std::filesystem::path& fromProjectRoot,
        const std::filesystem::path& fromBuildFolder
    ) {
        if (std::filesystem::exists(fromProjectRoot)) {
            return fromProjectRoot;
        }

        if (std::filesystem::exists(fromBuildFolder)) {
            return fromBuildFolder;
        }

        throw std::runtime_error(
            "Could not find test file. Checked: " +
            fromProjectRoot.string() +
            " and " +
            fromBuildFolder.string()
        );
    }

    std::filesystem::path findValidScenarioPath() {
        return findFile(
            "scenarios/search_rescue_demo.json",
            "../scenarios/search_rescue_demo.json"
        );
    }

    std::filesystem::path findInvalidMissingMissionPath() {
        return findFile(
            "cpp/tests/fixtures/invalid_missing_mission.json",
            "../cpp/tests/fixtures/invalid_missing_mission.json"
        );
    }
}

TEST(ScenarioLoaderTest, LoadsScenarioDataFromJson) {
    ScenarioLoader loader;

    ScenarioData scenario = loader.loadFromFile(findValidScenarioPath());

    EXPECT_EQ(scenario.mission.name, "Search Rescue Demo");
    EXPECT_EQ(scenario.mission.type, "search_and_rescue");

    EXPECT_DOUBLE_EQ(scenario.map.width, 1200.0);
    EXPECT_DOUBLE_EQ(scenario.map.height, 800.0);
    EXPECT_EQ(scenario.map.unit, "meters");

    ASSERT_EQ(scenario.vessels.size(), 1U);

    const VesselConfig& vessel = scenario.vessels.front();

    EXPECT_EQ(vessel.id, "USV-01");
    EXPECT_DOUBLE_EQ(vessel.startPosition.x, 100.0);
    EXPECT_DOUBLE_EQ(vessel.startPosition.y, 650.0);
    EXPECT_DOUBLE_EQ(vessel.speed, 12.0);
    EXPECT_DOUBLE_EQ(vessel.heading, 0.0);
    EXPECT_DOUBLE_EQ(vessel.battery, 100.0);
    EXPECT_DOUBLE_EQ(vessel.signalStrength, 100.0);

    ASSERT_EQ(scenario.waypoints.size(), 4U);

    EXPECT_EQ(scenario.waypoints.front().id, "WP-01");
    EXPECT_DOUBLE_EQ(scenario.waypoints.front().position.x, 250.0);
    EXPECT_DOUBLE_EQ(scenario.waypoints.front().position.y, 600.0);

    ASSERT_EQ(scenario.obstacles.size(), 1U);

    EXPECT_EQ(scenario.obstacles.front().id, "OBS-01");
    EXPECT_DOUBLE_EQ(scenario.obstacles.front().x, 700.0);
    EXPECT_DOUBLE_EQ(scenario.obstacles.front().y, 520.0);
    EXPECT_DOUBLE_EQ(scenario.obstacles.front().width, 120.0);
    EXPECT_DOUBLE_EQ(scenario.obstacles.front().height, 80.0);

    ASSERT_EQ(scenario.restrictedZones.size(), 1U);

    EXPECT_EQ(scenario.restrictedZones.front().id, "RZ-01");
    EXPECT_DOUBLE_EQ(scenario.restrictedZones.front().x, 500.0);
    EXPECT_DOUBLE_EQ(scenario.restrictedZones.front().y, 300.0);
    EXPECT_DOUBLE_EQ(scenario.restrictedZones.front().width, 150.0);
    EXPECT_DOUBLE_EQ(scenario.restrictedZones.front().height, 120.0);

    EXPECT_EQ(scenario.distressBeacon.id, "BEACON-01");
    EXPECT_DOUBLE_EQ(scenario.distressBeacon.position.x, 900.0);
    EXPECT_DOUBLE_EQ(scenario.distressBeacon.position.y, 250.0);

    EXPECT_EQ(scenario.missionRules.successCondition, "USV reaches distress beacon");
    ASSERT_EQ(scenario.missionRules.failureConditions.size(), 3U);
}

TEST(ScenarioLoaderTest, ThrowsForMissingScenarioFile) {
    ScenarioLoader loader;

    EXPECT_THROW(
        loader.loadFromFile("missing_file_does_not_exist.json"),
        std::runtime_error
    );
}

TEST(ScenarioLoaderTest, ThrowsForInvalidScenarioMissingMission) {
    ScenarioLoader loader;

    EXPECT_THROW(
        loader.loadFromFile(findInvalidMissingMissionPath()),
        std::runtime_error
    );
}
