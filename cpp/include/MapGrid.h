#pragma once

#include "MapGrid.h"
#include "ScenarioData.h"
#include "Vessel.h"

#include <vector>

class MapGrid {
    public:
        MapGrid(
            double width,
            double height,
            std::vector<ObstacleConfig> obstacles,
            std::vector<RestrictedZoneConfig> restrictedZones
        );

        double getWidth() const;
        double getHeight() const;

        bool isInsideBounds(Position position) const;
        bool isInsideObstacle(Position position) const;
        bool isInsideRestrictedZone(Position position) const;

    private:
        static bool isInsideRectangle(
            Position position,
            double x,
            double y,
            double width,
            double height
        );

        double width_;
        double height_;
        std::vector<ObstacleConfig> obstacles_;
        std::vector<RestrictedZoneConfig> restrictedZones_;
};