#include "FleetGeneration.h"
#include "FleetSimulationEngine.h"
#include "ProtobufTelemetryPacketBuilder.h"
#include "UdpTelemetrySender.h"
#include "VesselState.h"

#include <chrono>
#include <cstddef>
#include <iostream>
#include <limits>
#include <string>
#include <thread>
#include <vector>

namespace {
constexpr std::size_t kDefaultVesselCount = 5;
constexpr int kDefaultDurationSeconds = 60;
constexpr double kDeltaTimeSeconds = 1.0;

struct SimulationOptions {
    std::size_t vesselCount = kDefaultVesselCount;
    int durationSeconds = kDefaultDurationSeconds;
};

std::size_t parseVesselCountOrDefault(
    const std::string& value,
    std::size_t fallback
) {
    try {
        std::size_t processedCharacters = 0;
        const unsigned long long parsedValue =
            std::stoull(value, &processedCharacters);

        if (processedCharacters != value.size()) {
            return fallback;
        }

        if (parsedValue == 0) {
            return fallback;
        }

        if (parsedValue > std::numeric_limits<std::size_t>::max()) {
            return fallback;
        }

        return static_cast<std::size_t>(parsedValue);
    } catch (...) {
        return fallback;
    }
}

SimulationOptions parseCommandLineArguments(int argc, char* argv[]) {
    SimulationOptions options{};

    for (int index = 1; index < argc; ++index) {
        const std::string argument = argv[index];

        if (argument == "--vessels" && index + 1 < argc) {
            options.vesselCount = parseVesselCountOrDefault(
                argv[index + 1],
                kDefaultVesselCount
            );
            ++index;
        }
    }

    return options;
}
}

int main(int argc, char* argv[]) {
    const SimulationOptions options = parseCommandLineArguments(argc, argv);

    std::vector<VesselState> vessels = createSampleFleet(options.vesselCount);

    FleetSimulationEngine engine{vessels};
    UdpTelemetrySender sender{};

    std::cout << "Fleet Protobuf Telemetry Simulation\n";
    std::cout << "endpoint=" << sender.getHost() << ":" << sender.getPort() << '\n';
    std::cout << "vessels=" << options.vesselCount << '\n';
    std::cout << "durationSeconds=" << options.durationSeconds << '\n';
    std::cout << "deltaTimeSeconds=" << kDeltaTimeSeconds << "\n\n";

    bool printedSerializedSize = false;

    std::size_t totalPacketsSent = 0;
    std::size_t totalPacketsFailed = 0;

    for (int tick = 1; tick <= options.durationSeconds; ++tick) {
        engine.update(kDeltaTimeSeconds);

        std::size_t packetsSentThisTick = 0;
        std::size_t packetsFailedThisTick = 0;

        for (const VesselState& vessel : engine.getVessels()) {
            const std::vector<std::uint8_t> packet =
                ProtobufTelemetryPacketBuilder::buildPacketWithGeneratedMetadata(vessel);

            if (!printedSerializedSize) {
                std::cout << "protobufSerializedBytes=" << packet.size() << '\n';
                printedSerializedSize = true;
            }

            if (sender.sendPacket(packet)) {
                ++packetsSentThisTick;
                ++totalPacketsSent;
            } else {
                ++packetsFailedThisTick;
                ++totalPacketsFailed;
            }
        }

        std::cout << "tick=" << tick
                  << " packetsSent=" << packetsSentThisTick
                  << " packetsFailed=" << packetsFailedThisTick
                  << std::endl;

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    std::cout << "\ncomplete=true\n";
    std::cout << "totalPacketsSent=" << totalPacketsSent << '\n';
    std::cout << "totalPacketsFailed=" << totalPacketsFailed << '\n';

    return totalPacketsFailed == 0 ? 0 : 1;
}