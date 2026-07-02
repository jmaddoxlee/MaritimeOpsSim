#include "RaylibRenderer.h"
#include "ScenarioData.h"
#include "ScenarioLoader.h"

#include <exception>
#include <filesystem>
#include <iostream>
#include <sstream>
#include <vector>

std::filesystem::path resolveScenarioPathForVisualDemo() {
    const std::vector<std::filesystem::path> candidates = {
        "scenarios/search_rescue_demo.json",
        "../scenarios/search_rescue_demo.json"
    };

    for (const std::filesystem::path& candidate : candidates) {
        if (std::filesystem::exists(candidate)) {
            return candidate;
        }
    }

    std::ostringstream message;
    message << "Could not find scenario file. Checked paths:";

    for (const std::filesystem::path& candidate : candidates) {
        message << "\n- " << std::filesystem::absolute(candidate);
    }

    throw std::runtime_error(message.str());
}

int main() {
    try {
        const std::filesystem::path scenarioPath = resolveScenarioPathForVisualDemo();

        std::cout << "Loading visual scenario: " << scenarioPath << "\n";

        ScenarioLoader loader;
        ScenarioData scenario = loader.loadFromFile(scenarioPath);

        RaylibRenderer renderer;
        renderer.run(scenario);

    } catch (const std::exception& error) {
        std::cerr << "Failed to start visual demo: " << error.what() << "\n";
        return 1;
    }
}