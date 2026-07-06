#pragma once

#include "Vessel.h"

#include <string>

struct VesselState {
    std::string id;
    Position position {};
    double speed = 0.0;
    double heading = 0.0;
    double fuel = 100.0;
    double signalStrength = 1.0;
    bool active = true;
};