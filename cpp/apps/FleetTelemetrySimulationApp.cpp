#include "FleetGeneration.h"
#include "FleetSimulationEngine.h"
#include "TelemetryPacketBuilder.h"
#include "UdpTelemetrySender.h"
#include "VesselState.h"

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

namespace {
    constexpr std::size_t kDefaultVesselCount = 100;
    constexpr int kDefaultDurationSeconds = 60;
    constexpr double kDeltaTimeSeconds = 1.0;

    bool isSilentMode(int argc, char* argv[]) {
        for (int index = 1; index < argc; ++index) {
            const std::string argument = argv[index];

            if (argument == "--silent" || argument == "-s") {
                return true;
            }
        }

        return false;
    }

    struct TickTelemetryResult {
        std::size_t packetsAttempted = 0;
        std::size_t packetsSent = 0;
        std::size_t packetsFailed = 0;
    };

    TickTelemetryResult emitTelemetryForFleet(
        const std::vector<VesselState>& vessels,
        const UdpTelemetrySender& sender
    ) {
        TickTelemetryResult result{};

        for (const VesselState& vessel : vessels) {
            const std::vector<uint8_t> packet = TelemetryPacketBuilder::buildPacketWithGeneratedMetadata(vessel);

            ++result.packetsAttempted;

            if (sender.sendPacket(packet)) {
                ++result.packetsSent;
            } else {
                ++result.packetsFailed;
            }
        }

        return result;
    }

    void logTickSummary(
        int tick,
        const TickTelemetryResult& result
    ) {
        std::cout << "tick=" << tick
              << " packetsAttempted=" << result.packetsAttempted
              << " packetsSent=" << result.packetsSent
              << " packetsFailed=" << result.packetsFailed
              << '\n';
    }
}

int main(int argc, char* argv[]) {
    const bool silent = isSilentMode(argc, argv);

    std::vector<VesselState> vessels = createSampleFleet(kDefaultVesselCount);

    FleetSimulationEngine engine{vessels};
    UdpTelemetrySender sender;

    if (!silent) {
        std::cout << "Fleet Telemetry Simulation\n";
        std::cout << "endpoint=" << sender.getHost() << ":" << sender.getPort() << '\n';
        std::cout << "vessels=" << kDefaultVesselCount << '\n';
        std::cout << "durationSeconds=" << kDefaultDurationSeconds << '\n';
        std::cout << "deltaTimeSeconds=" << kDeltaTimeSeconds << '\n';
        std::cout << "mode=" << (silent ? "silent" : "logging") << "\n\n";
    }
    
    std::size_t totalPacketsSent = 0;
    std::size_t totalPacketsFailed = 0;

    for (int tick = 1; tick <= kDefaultDurationSeconds; ++tick) {
        engine.update(kDeltaTimeSeconds);

        TickTelemetryResult result = emitTelemetryForFleet(
            engine.getVessels(),
            sender
        );

        totalPacketsSent += result.packetsSent;
        totalPacketsFailed += result.packetsFailed;

        if (!silent) {
            logTickSummary(tick, result);
        }

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    if (!silent) {
        std::cout << "\ncomplete=true\n";
        std::cout << "totalPacketsSent=" << totalPacketsSent << '\n';
        std::cout << "totalPacketsFailed=" << totalPacketsFailed << '\n';
    }

    return totalPacketsFailed == 0 ? 0 : 1;
}