#include "TelemetryPacketBuilder.h"
#include "UdpTelemetrySender.h"
#include "VesselState.h"

#include <iostream>
#include <vector>

int main() {
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

    UdpTelemetrySender sender;

    const bool sent = sender.sendPacket(packet);

    std::cout << "UdpTelemetrySmokeTest\n";
    std::cout << "endpoint=" << sender.getHost() << ":" << sender.getPort() << '\n';
    std::cout << "packetBytes=" << packet.size() << '\n';
    std::cout << "sent=" << (sent ? "true" : "false") << '\n';

    return sent ? 0 : 1;
}