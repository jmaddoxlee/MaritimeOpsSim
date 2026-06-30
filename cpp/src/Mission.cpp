#include "Mission.h"

#include <iostream>
#include <utility>

Mission::Mission(std::string name, std::string type)
    : name_(std::move(name)),
      type_(std::move(type)),
      status_(MissionStatus::NotStarted),
      elapsedTimeSeconds_(0.0) {}

const std::string& Mission::getName() const {
    return name_;
}

const std::string& Mission::getType() const {
    return type_;
}

MissionStatus Mission::getStatus() const {
    return status_;
}

double Mission::getElapsedTimeSeconds() const {
    return elapsedTimeSeconds_;
}

void Mission::start() {
    status_ = MissionStatus::Running;
    elapsedTimeSeconds_ = 0.0;
}

void Mission::update(double deltaTimeSeconds) {
    if (status_ == MissionStatus::Running) {
        elapsedTimeSeconds_ += deltaTimeSeconds;
    }
}

void Mission::complete() {
    status_ = MissionStatus::Completed;
}

void Mission::fail() {
    status_ = MissionStatus::Failed;
}

bool Mission::isRunning() const {
    return status_ == MissionStatus::Running;
}

bool Mission::isFinished() const {
    return status_ == MissionStatus::Completed || status_ == MissionStatus::Failed;
}

void Mission::printStatus() const {
    std::cout << "Mission: " << name_ << "\n";
    std::cout << "Type: " << type_ << "\n";
    std::cout << "Elapsed Time: " << elapsedTimeSeconds_ << " seconds\n";
    std::cout << "Status: ";

    switch (status_) {
        case MissionStatus::NotStarted:
            std::cout << "Not Started";
            break;
        case MissionStatus::Running:
            std::cout << "Running";
            break;
        case MissionStatus::Completed:
            std::cout << "Completed";
            break;
        case MissionStatus::Failed:
            std::cout << "Failed";
            break;
    }

    std::cout << "\n";
}