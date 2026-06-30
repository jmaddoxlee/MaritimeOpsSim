#pragma once

#include <string>

enum class MissionStatus {
    NotStarted,
    Running,
    Completed,
    Failed
};

class Mission {
    public:
        Mission(std::string name, std::string type);

        const std::string& getName() const;
        const std::string& getType() const;
        MissionStatus getStatus() const;
        double getElapsedTimeSeconds() const;

        void start();
        void update(double deltaTimeSeconds);
        void complete();
        void fail();

        bool isRunning() const;
        bool isFinished() const;

        void printStatus() const;
    
    private:
        std::string name_;
        std::string type_;
        MissionStatus status_;
        double elapsedTimeSeconds_;
};