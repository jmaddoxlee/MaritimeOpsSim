#include "FleetSimulationEngine.h"
#include "VesselState.h"

#include <gtest/gtest.h>

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