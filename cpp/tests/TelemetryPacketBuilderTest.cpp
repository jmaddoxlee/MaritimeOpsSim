#include "TelemetryPacketBuilder.h"
#include "VesselState.h"

#include <gtest/gtest.h>

TEST(TelemetryPacketBuilderTest, BuildsExpectedPacketSize) {
    VesselState vessel{
        "VESSEL-001",
        Position{55.0, 50.0},
        5.0,
        0.0,
        99.75,
        1.0,
        true
    };

    const std::vector<std::uint8_t> packet = 
        TelemetryPacketBuilder::buildPacket(vessel, 42, 1783545600000);

    EXPECT_EQ(packet.size(), TelemetryPacketBuilder::kPacketSizeBytes);
}

TEST(TelemetryPacketBuilderTest, ExtractsVesselNumericId) {
    EXPECT_EQ(TelemetryPacketBuilder::extractVesselNumericId("VESSEL-001"), 1);
    EXPECT_EQ(TelemetryPacketBuilder::extractVesselNumericId("VESSEL-100"), 100);
    EXPECT_EQ(TelemetryPacketBuilder::extractVesselNumericId("NO-ID"), 0);
}

TEST(TelemetryPacketBuilderTest, BuildsActiveStatusFlag) {
    VesselState vessel{};
    vessel.active = true;
    vessel.fuel = 100.0;
    vessel.signalStrength = 1.0;

    const std::uint32_t flags = TelemetryPacketBuilder::buildStatusFlags(vessel);

    EXPECT_EQ(flags, TelemetryStatusFlags::Active);
}

TEST(TelemetryPacketBuilderTest, BuildsLowFuelStatusFlag) {
    VesselState vessel{};
    vessel.active = true;
    vessel.fuel = 20.0;
    vessel.signalStrength = 1.0;

    const std::uint32_t flags = TelemetryPacketBuilder::buildStatusFlags(vessel);

    EXPECT_TRUE((flags & TelemetryStatusFlags::Active) != 0);
    EXPECT_TRUE((flags & TelemetryStatusFlags::LowFuel) != 0);
}

TEST(TelemetryPacketBuilderTest, BuildsSignalDegradedStatusFlag) {
    VesselState vessel{};
    vessel.active = true;
    vessel.fuel = 100.0;
    vessel.signalStrength = 0.25;

    const std::uint32_t flags = TelemetryPacketBuilder::buildStatusFlags(vessel);

    EXPECT_TRUE((flags & TelemetryStatusFlags::Active) != 0);
    EXPECT_TRUE((flags & TelemetryStatusFlags::SignalDegraded) != 0);
}

TEST(TelemetryPacketBuilderTest, InactiveHealthyVesselHasNoFlags) {
    VesselState vessel{};
    vessel.active = false;
    vessel.fuel = 100.0;
    vessel.signalStrength = 1.0;

    const std::uint32_t flags = TelemetryPacketBuilder::buildStatusFlags(vessel);

    EXPECT_EQ(flags, 0);
}