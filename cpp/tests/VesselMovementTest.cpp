#include "Vessel.h"

#include <gtest/gtest.h>

TEST(VesselMovementTest, MovesForwardWhenHeadingIsZeroDegrees) {
    Vessel vessel("USV-01", Position{100.0, 650.0}, 12.0, 0.0);

    vessel.update(1.0);

    Position position = vessel.getPosition();

    EXPECT_DOUBLE_EQ(position.x, 112.0);
    EXPECT_DOUBLE_EQ(position.y, 650.0);
}