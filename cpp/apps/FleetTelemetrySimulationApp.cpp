#include "FleetGeneration.h"
#include "FleetSimulationEngine.h"
#include "TelemetryPacketBuilder.h"
#include "UdpTelemetrySender.h"
#include "VesselState.h"

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <limits>
#include <string>
#include <thread>
#include <vector>

namespace {
    constexpr std::size_t kDefaultVesselCount = 100;
    constexpr int kDefaultDurationSeconds = 60;
    constexpr double kDeltaTimeSeconds = 1.0;

    struct SimulationOptions {
        bool headless = true;
        bool silent = false;
        bool showHelp = false;
        std::size_t vesselCount = kDefaultVesselCount;
        int durationSeconds = kDefaultDurationSeconds;
    };

    struct TickTelemetryResult {
        std::size_t packetsAttempted = 0;
        std::size_t packetsSent = 0;
        std::size_t packetsFailed = 0;
    };

    void printUsage() {
        std::cout << "FleetTelemetrySimulation\n\n";
        std::cout << "Usage:\n";
        std::cout << "  ./FleetTelemetrySimulation [options]\n\n";
        std::cout << "Options:\n";
        std::cout << "  --headless          Run without visual window. This is the default.\n";
        std::cout << "  --vessels <count>   Number of vessels to simulate. Default: 100.\n";
        std::cout << "  --silent, -s        Run without console tick logs.\n";
        std::cout << "  --help, -h          Show this help message.\n";
    }

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

            if (argument == "--headless") {
                options.headless = true;
            } else if (argument == "--silent" || argument == "-s") {
                options.silent = true;
            } else if (argument == "--help" || argument == "-h") {
                options.showHelp = true;
            } else if (argument == "--vessels") {
                if (index + 1 < argc) {
                    options.vesselCount = parseVesselCountOrDefault(
                        argv[index + 1],
                        kDefaultVesselCount
                    );

                    ++index;
                } else {
                    options.vesselCount = kDefaultVesselCount;
                }
            }
        }
        return options;
    }

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
    const SimulationOptions options = parseCommandLineArguments(argc, argv);

    if (options.showHelp) {
        printUsage();
        return 0;
    }

    std::vector<VesselState> vessels = createSampleFleet(options.vesselCount);

    FleetSimulationEngine engine{vessels};
    UdpTelemetrySender sender;

    if (!options.silent) {
        std::cout << "Fleet Telemetry Simulation\n";
        std::cout << "endpoint=" << sender.getHost() << ":" << sender.getPort() << '\n';
        std::cout << "mode=" << (options.headless ? "headless" : "unknown") << '\n';
        std::cout << "vessels=" << options.vesselCount << '\n';
        std::cout << "durationSeconds=" << options.durationSeconds << '\n';
        std::cout << "deltaTimeSeconds=" << kDeltaTimeSeconds << "\n\n";
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

        if (!options.silent) {
            logTickSummary(tick, result);
        }

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    if (!options.silent) {
        std::cout << "\ncomplete=true\n";
        std::cout << "totalPacketsSent=" << totalPacketsSent << '\n';
        std::cout << "totalPacketsFailed=" << totalPacketsFailed << '\n';
    }

    return totalPacketsFailed == 0 ? 0 : 1;
}