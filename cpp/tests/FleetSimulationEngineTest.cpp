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