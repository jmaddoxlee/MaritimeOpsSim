#pragma once

#include "ScenarioData.h"

class RaylibRenderer {
    public:
        RaylibRenderer();

        void run(const ScenarioData& scenario) const;
};