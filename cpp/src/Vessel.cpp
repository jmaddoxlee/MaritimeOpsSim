#include "Vessel.h"

#include <iostream>
#include <utility>

Vessel::Vessel(std::string id, Position position, double speed, double heading)
    : id_(std::move(id)),
      position_(position),
      speed_(speed),
      heading_(heading) {}

const std::string& Vessel::getId() const {
    return id_;
}

Position Vessel::getPosition() const {
    return position_;
}

double Vessel::getSpeed() const {
    return speed_;
}

double Vessel::getHeading() const {
    return heading_;
}

void Vessel::setPosition(Position position) {
    position_ = position;
}

void Vessel::setSpeed(double speed) {
    speed_ = speed;
}

void Vessel::setHeading(double heading) {
    heading_ = heading;
}

void Vessel::update(double deltaTimeSeconds) {
    constexpr double pi = 3.14159265358979323846;
    const double headingRadians = heading_ * pi / 180.0;

    position_.x += std::cos(headingRadians) * speed_ * deltaTimeSeconds;
    position_.y += std::sin(headingRadians) * speed_ * deltaTimeSeconds;
}

void Vessel::printTelemetry() const {
    std::cout << "Vessel: " << id_ << "\n";
    std::cout << "Position: x=" << position_.x << ", y=" << position_.y << "\n";
    std::cout << "Speed: " << speed_ << "\n";
    std::cout << "Heading: " << heading_ << "\n";
}