#pragma once

#include "ScenarioData.h"

#include <filesystem>

class ScenarioLoader {
    public:
        ScenarioData loadFromFile(const std::filesystem::path& filePath) const;
};