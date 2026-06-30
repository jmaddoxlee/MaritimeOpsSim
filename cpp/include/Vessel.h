#pragma once

#include <string>

struct Position {
    double x;
    double y;
};

class Vessel {
    public:
        Vessel(std::string id, Position position, double speed, double heading);

        const std::string& getId() const;
        Position getPosition() const;
        double getSpeed() const;
        double getHeading() const;

        void setPosition(Position position);
        void setSpeed(double speed);
        void setHeading(double heading);

        void printTelemetry() const;

    private:
        std::string id_;
        Position position_;
        double speed_;
        double heading_;
};