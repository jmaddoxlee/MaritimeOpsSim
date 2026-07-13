#include "TelemetryPacketBuilder.h"
#include "VesselState.h"

#include <gtest/gtest.h>

#include <cstddef>
#include <cstdint>
#include <vector>

namespace {
    std::uint32_t readUint32LittleEndian(
        const std::vector<uint8_t>& bytes,
        std::size_t offset
    ) {
        return static_cast<std::uint32_t>(bytes.at(offset)) |
            (static_cast<std::uint32_t>(bytes.at(offset + 1)) << 8) |
            (static_cast<std::uint32_t>(bytes.at(offset + 2)) << 16) |
            (static_cast<std::uint32_t>(bytes.at(offset + 3)) << 24);
    }
}

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

TEST(TelemetryPacketBuilderTest, PacketIsNotEmpty) {
    VesselState vessel{
        "VESSEL-001",
        Position{55.0, 50.0},
        5.0,
        0.0,
        99.75,
        1.0,
        true
    };

    const std::vector<std::uint8_t> packet = TelemetryPacketBuilder::buildPacket(vessel, 1, 1000);

    EXPECT_FALSE(packet.empty());
    EXPECT_EQ(packet.size(), TelemetryPacketBuilder::kPacketSizeBytes);
}

TEST(TelemetryPacketBuilderTest, PacketContainsExpectedVesselId) {
    VesselState vessel{
        "VESSEL-042",
        Position{55.0, 50.0},
        5.0,
        0.0,
        99.75,
        1.0,
        true
    };

    const std::vector<std::uint8_t> packet = TelemetryPacketBuilder::buildPacket(vessel, 1, 1000);

    // Packet layout:
    // sequence number  = bytes 0-7
    // timestamp        = bytes 8-15
    // vessel numeric ID = bytes 16-19
    const std::uint32_t vesselNumericId = readUint32LittleEndian(packet, 16);
    EXPECT_EQ(vesselNumericId, 42);
}

TEST(TelemetryPacketBuilderTest, StatusFlagCanBeSet) {
    VesselState vessel{};
    vessel.active = true;
    vessel.fuel = 10.0;
    vessel.signalStrength = 0.25;

    const std::uint32_t flags = TelemetryPacketBuilder::buildStatusFlags(vessel);

    EXPECT_TRUE((flags & TelemetryStatusFlags::Active) != 0);
    EXPECT_TRUE((flags & TelemetryStatusFlags::LowFuel) != 0);
    EXPECT_TRUE((flags & TelemetryStatusFlags::SignalDegraded) != 0);
}

TEST(TelemetryPacketBuilderTest, SequenceNumberIncreases) {
    const std::uint64_t first = TelemetryPacketBuilder::nextSequenceNumber();
    const std::uint64_t second = TelemetryPacketBuilder::nextSequenceNumber();

    EXPECT_GT(second, first);
}

TEST(TelemetryPacketBuilderTest, TimestampUsesUnixMilliseconds) {
    const std::uint64_t timestamp = TelemetryPacketBuilder::currentTimestampUnixMs();

    EXPECT_GT(timestamp, 0);
}

TEST(TelemetryPacketBuilderTest, BuildsPacketWithGeneratedMetadata) {
    VesselState vessel{
        "VESSEL-001",
        Position{55.0, 50.0},
        5.0,
        0.0,
        99.75,
        1.0,
        true
    };

    const std::vector<std::uint8_t> packet = TelemetryPacketBuilder::buildPacketWithGeneratedMetadata(vessel);

    EXPECT_FALSE(packet.empty());
    EXPECT_EQ(packet.size(), TelemetryPacketBuilder::kPacketSizeBytes);
}