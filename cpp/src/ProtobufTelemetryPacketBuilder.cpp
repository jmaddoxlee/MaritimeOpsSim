#include "ProtobufTelemetryPacketBuilder.h"

#include "TelemetryPacketBuilder.h"
#include "vessel_telemetry.pb.h"

#include <string>

std::vector<std::uint8_t> ProtobufTelemetryPacketBuilder::buildPacket(
    const VesselState& vessel,
    std::uint64_t sequenceNumber,
    std::uint64_t timestampUnixMs
) {
    maritimeops::telemetry::VesselTelemetry message;

    message.set_vessel_id(vessel.id);
    message.set_timestamp_unix_ms(timestampUnixMs);
    message.set_x(vessel.position.x);
    message.set_y(vessel.position.y);
    message.set_speed(vessel.speed);
    message.set_heading(vessel.heading);
    message.set_fuel(vessel.fuel);
    message.set_signal_strength(vessel.signalStrength);
    message.set_status_flags(TelemetryPacketBuilder::buildStatusFlags(vessel));
    message.set_sequence_number(sequenceNumber);

    std::string serializedMessage;
    message.SerializeToString(&serializedMessage);

    return std::vector<std::uint8_t>(
        serializedMessage.begin(),
        serializedMessage.end()
    );
}

std::vector<std::uint8_t> ProtobufTelemetryPacketBuilder::buildPacketWithGeneratedMetadata(
    const VesselState& vessel
) {
    return buildPacket(
        vessel,
        TelemetryPacketBuilder::nextSequenceNumber(),
        TelemetryPacketBuilder::currentTimestampUnixMs()
    );
}