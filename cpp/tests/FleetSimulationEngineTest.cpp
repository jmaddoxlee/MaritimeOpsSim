#include "FleetGeneration.h"
#include "FleetSimulationEngine.h"
#include "VesselState.h"

#include <gtest/gtest.h>
#include <set>
#include <vector>

TEST(FleetSimulationEngineTest, VesselStateCanBeAggregateInitialized) {
    VesselState vessel{
        "usv-001",
        Position{10.0, 20.0},
        5.0,
        90.0,
        100.0,
        1.0,
        true
    };

    EXPECT_EQ(vessel.id, "usv-001");
    EXPECT_DOUBLE_EQ(vessel.position.x, 10.0);
    EXPECT_DOUBLE_EQ(vessel.position.y, 20.0);
    EXPECT_DOUBLE_EQ(vessel.speed, 5.0);
    EXPECT_DOUBLE_EQ(vessel.heading, 90.0);
    EXPECT_DOUBLE_EQ(vessel.fuel, 100.0);
    EXPECT_DOUBLE_EQ(vessel.signalStrength, 1.0);
    EXPECT_TRUE(vessel.active);
}

TEST(FleetSimulationEngineTest, VesselStateHasSafeDefaults) {
    VesselState vessel{};

    EXPECT_TRUE(vessel.id.empty());
    EXPECT_DOUBLE_EQ(vessel.position.x, 0.0);
    EXPECT_DOUBLE_EQ(vessel.position.y, 0.0);
    EXPECT_DOUBLE_EQ(vessel.speed, 0.0);
    EXPECT_DOUBLE_EQ(vessel.heading, 0.0);
    EXPECT_DOUBLE_EQ(vessel.fuel, 100.0);
    EXPECT_DOUBLE_EQ(vessel.signalStrength, 1.0);
    EXPECT_TRUE(vessel.active);
}

TEST(FleetSimulationEngineTest, ConstructorStoresVessels) {
    std::vector<VesselState> vessels{
        VesselState {
            "usv-001",
            Position{0.0, 0.0},
            10.0,
            0.0,
            100.0,
            1.0,
            true
        },
        VesselState {
            "usv-002",
            Position{5.0, 5.0},
            3.0,
            90.0,
            100.0,
            1.0,
            true
        }
    };

    FleetSimulationEngine engine{vessels};

    EXPECT_EQ(engine.getVessels().size(), 2);
    EXPECT_EQ(engine.getVessels().at(0).id, "usv-001");
    EXPECT_EQ(engine.getVessels().at(1).id ,"usv-002");
}

TEST(FleetSimulationEngineTest, UpdateMovesActiveVessels) {
    std::vector<VesselState> vessels{
        VesselState {
            "usv-001",
            Position{0.0, 0.0},
            10.0,
            0.0,
            100.0,
            1.0,
            true
        }
    };

    FleetSimulationEngine engine{vessels};

    engine.update(1.0);

    const VesselState& vessel = engine.getVessels().at(0);

    EXPECT_DOUBLE_EQ(vessel.position.x, 10.0);
    EXPECT_NEAR(vessel.position.y, 0.0, 0.000001);
}

TEST(FleetSimulationEngineTest, UpdateSkipsInactiveVessels) {
    std::vector<VesselState> vessels{
        VesselState{
            "usv-001",
            Position{0.0, 0.0},
            10.0,
            0.0,
            100.0,
            1.0,
            false
        }
    };

    FleetSimulationEngine engine{vessels};

    engine.update(1.0);

    const VesselState& vessel = engine.getVessels().at(0);

    EXPECT_DOUBLE_EQ(vessel.position.x, 0.0);
    EXPECT_DOUBLE_EQ(vessel.position.y, 0.0);
}

TEST(FleetSimulationEngineTest, UpdateIgnoresNonPositiveDeltaTime) {
    std::vector<VesselState> vessels{
        VesselState{
            "usv-001",
            Position{0.0, 0.0},
            10.0,
            0.0,
            100.0,
            1.0,
            true
        }
    };

    FleetSimulationEngine engine{vessels};

    engine.update(0.0);
    engine.update(-1.0);

    const VesselState& vessel = engine.getVessels().at(0);

    EXPECT_DOUBLE_EQ(vessel.position.x, 0.0);
    EXPECT_DOUBLE_EQ(vessel.position.y, 0.0);
}

TEST(FleetSimulationEngineTest, CreateSampleFleetCreatesRequestedCount) {
    std::vector<VesselState> vessels = createSampleFleet(100);

    EXPECT_EQ(vessels.size(), 100);
}

TEST(FleetSimulationEngineTest, CreateSampleFleetGenerateUniqueIds) {
    std::vector<VesselState> vessels = createSampleFleet(100);

    std::set<std::string> ids;

    for (const VesselState& vessel : vessels) {
        ids.insert(vessel.id);
    }

    EXPECT_EQ(ids.size(), 100);
    EXPECT_EQ(vessels.at(0).id, "VESSEL-001");
    EXPECT_EQ(vessels.at(99).id, "VESSEL-100");
}

TEST(FleetSimulationEngineTest, CreateSampleFleetGenerateSpreadOutPositions) {
    const std::vector<VesselState> vessels = createSampleFleet(100);

    EXPECT_DOUBLE_EQ(vessels.at(0).position.x, 50.0);
    EXPECT_DOUBLE_EQ(vessels.at(0).position.y, 50.0);

    EXPECT_DOUBLE_EQ(vessels.at(1).position.x, 75.0);
    EXPECT_DOUBLE_EQ(vessels.at(1).position.y, 50.0);

    EXPECT_DOUBLE_EQ(vessels.at(10).position.x, 50.0);
    EXPECT_DOUBLE_EQ(vessels.at(10).position.y, 75.0);
}

TEST(FleetSimulationEngineTest, FleetSimulationEngineAcceptsGeneratedFleet) {
    const std::vector<VesselState> vessels = createSampleFleet(100);

    FleetSimulationEngine engine{vessels};

    EXPECT_EQ(engine.getVessels().size(), 100);
    EXPECT_EQ(engine.getVessels().at(0).id, "VESSEL-001");
    EXPECT_EQ(engine.getVessels().at(99).id, "VESSEL-100");
}