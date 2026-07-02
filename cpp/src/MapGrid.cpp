#include "MapGrid.h"

MapGrid::MapGrid(
    double width,
    double height,
    std::vector<ObstacleConfig> obstacles,
    std::vector<RestrictedZoneConfig> restrictedZones
)
    : width_(width),
      height_(height),
      obstacles_(obstacles),
      restrictedZones_(restrictedZones) {};

double MapGrid::getWidth() const {
    return width_;
}

double MapGrid::getHeight() const {
    return height_;
}

bool MapGrid::isInsideBounds(Position position) const {
    return 
        position.x >= 0 &&
        position.y >= 0 &&
        position.x <= width_ &&
        position.y <= height_;
}

bool MapGrid::isInsideObstacle(Position position) const {
    for (const ObstacleConfig& obstacle : obstacles_) {
        if (isInsideRectangle(
            position,
            obstacle.x,
            obstacle.y,
            obstacle.width,
            obstacle.height
        )) {
            return true;
        }
    }

    return false;
}

bool MapGrid::isInsideRestrictedZone(Position position) const {
    for (const RestrictedZoneConfig& zone : restrictedZones_) {
        if (isInsideRectangle(
            position,
            zone.x,
            zone.y,
            zone.width,
            zone.height
        )) {
            return true;
        }
    }

    return false;
}

bool MapGrid::isInsideRectangle(
    Position position,
    double x,
    double y,
    double width,
    double height
) {
    return
        position.x >= x &&
        position.x <= x + width &&
        position.y >= y &&
        position.y <= y + height;
}