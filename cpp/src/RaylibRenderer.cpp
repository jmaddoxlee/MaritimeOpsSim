#include "RaylibRenderer.h"

#include "Vessel.h"

#include <cmath>
#include <string>

#include <raylib.h>

namespace {
    constexpr int screenWidth = 1280;
    constexpr int screenHeight = 900;

    constexpr float mapX = 30.0f;
    constexpr float mapY = 80.0f;
    constexpr float mapWidthPixels = 850.0f;
    constexpr float mapHeightPixels = 760.0f;

    constexpr float panelX = 910.0f;
    constexpr float panelY = 80.0f;
    constexpr float panelWidth = 340.0f;
    constexpr float panelHeight = 760.0f;

    float mapToScreenX(double worldX, double worldWidth) {
        return mapX + static_cast<float>(worldX / worldWidth) * mapWidthPixels;
    }

    float mapToScreenY(double worldY, double worldHeight) {
        return mapY + static_cast<float>(worldY / worldHeight) * mapHeightPixels;
    }

    Rectangle mapRectangleToScreen(
        double x,
        double y,
        double width,
        double height,
        double worldWidth,
        double worldHeight
    ) {
        return Rectangle{
            mapToScreenX(x, worldWidth),
            mapToScreenY(y, worldHeight),
            static_cast<float>(width / worldWidth) * mapWidthPixels,
            static_cast<float>(height / worldHeight) * mapHeightPixels
        };
    }

    bool isInsideRectangle(
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

    bool isInsideAnyRestrictedZone(
        Position position,
        const std::vector<RestrictedZoneConfig>& restrictedZones
    ) {
        for (const RestrictedZoneConfig& zone : restrictedZones) {
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

    bool isInsideMapBounds(
        Position position,
        const MissionMap& map
    ) {
        return
            position.x >= 0.0 &&
            position.y >= 0.0 &&
            position.x <= map.width &&
            position.y <= map.height;
    }

    void drawMapBackground(const ScenarioData& scenario) {
        DrawRectangleRec(
            Rectangle{mapX, mapY, mapWidthPixels, mapHeightPixels},
            Color{18, 31, 45, 255}
        );

        DrawRectangleLinesEx(
            Rectangle{mapX, mapY, mapWidthPixels, mapHeightPixels},
            2.0f,
            SKYBLUE
        );

        DrawText(
            "Mission Map",
            static_cast<int>(mapX),
            40,
            24,
            RAYWHITE
        );

        DrawText(
            TextFormat(
                "Map: %.0f x %.0f %s",
                scenario.map.width,
                scenario.map.height,
                scenario.map.unit.c_str()
            ),
            static_cast<int>(mapX),
            65,
            16,
            LIGHTGRAY
        );
    }

    void drawObstacles(const ScenarioData& scenario) {
        for (const ObstacleConfig& obstacle : scenario.obstacles) {
            Rectangle rect = mapRectangleToScreen(
                obstacle.x,
                obstacle.y,
                obstacle.width,
                obstacle.height,
                scenario.map.width,
                scenario.map.height
            );

            DrawRectangleRec(rect, Color{130, 90, 55, 255});
            DrawRectangleLinesEx(rect, 2.0f, BEIGE);

            DrawText(
                obstacle.id.c_str(),
                static_cast<int>(rect.x + 4.0f),
                static_cast<int>(rect.y + 4.0f),
                14,
                RAYWHITE
            );
        }
    }

    void drawRestrictedZones(const ScenarioData& scenario) {
        for (const RestrictedZoneConfig& zone : scenario.restrictedZones) {
            Rectangle rect = mapRectangleToScreen(
                zone.x,
                zone.y,
                zone.width,
                zone.height,
                scenario.map.width,
                scenario.map.height
            );

            DrawRectangleRec(rect, Fade(RED, 0.30f));
            DrawRectangleLinesEx(rect, 2.0f, RED);

            DrawText(
                zone.id.c_str(),
                static_cast<int>(rect.x + 4.0f),
                static_cast<int>(rect.y + 4.0f),
                14,
                RAYWHITE
            );
        }
    }

    void drawWaypoints(const ScenarioData& scenario) {
        for (const WaypointConfig& waypoint : scenario.waypoints) {
            const float x = mapToScreenX(waypoint.position.x, scenario.map.width);
            const float y = mapToScreenY(waypoint.position.y, scenario.map.height);

            DrawCircleV(Vector2{x, y}, 7.0f, YELLOW);
            DrawCircleLines(static_cast<int>(x), static_cast<int>(y), 10.0f, GOLD);

            DrawText(
                waypoint.id.c_str(),
                static_cast<int>(x + 10.0f),
                static_cast<int>(y - 7.0f),
                14,
                RAYWHITE
            );
        }
    }

    void drawDistressBeacon(const ScenarioData& scenario) {
        const float x = mapToScreenX(
            scenario.distressBeacon.position.x,
            scenario.map.width
        );

        const float y = mapToScreenY(
            scenario.distressBeacon.position.y,
            scenario.map.height
        );

        DrawCircleV(Vector2{x, y}, 11.0f, ORANGE);
        DrawCircleLines(static_cast<int>(x), static_cast<int>(y), 18.0f, ORANGE);

        DrawText(
            scenario.distressBeacon.id.c_str(),
            static_cast<int>(x + 14.0f),
            static_cast<int>(y - 8.0f),
            14,
            RAYWHITE
        );
    }

    void drawVessel(
        const VesselConfig& vesselConfig,
        Position currentPosition,
        const ScenarioData& scenario
    ) {
        constexpr double pi = 3.14159265358979323846;

        const float x = mapToScreenX(currentPosition.x, scenario.map.width);
        const float y = mapToScreenY(currentPosition.y, scenario.map.height);

        DrawCircleV(Vector2{x, y}, 12.0f, LIME);
        DrawCircleLines(static_cast<int>(x), static_cast<int>(y), 16.0f, GREEN);

        const double headingRadians = vesselConfig.heading * pi / 180.0;

        const Vector2 headingEnd{
            x + static_cast<float>(std::cos(headingRadians) * 28.0),
            y + static_cast<float>(std::sin(headingRadians) * 28.0)
        };

        DrawLineEx(Vector2{x, y}, headingEnd, 3.0f, GREEN);

        DrawText(
            vesselConfig.id.c_str(),
            static_cast<int>(x + 16.0f),
            static_cast<int>(y - 8.0f),
            14,
            RAYWHITE
        );
    }

    void drawTelemetryPanel(
        const ScenarioData& scenario,
        const VesselConfig& vesselConfig,
        Position currentPosition,
        double missionTimeSeconds,
        const std::string& statusText
    ) {
        DrawRectangleRec(
            Rectangle{panelX, panelY, panelWidth, panelHeight},
            Color{25, 25, 30, 255}
        );

        DrawRectangleLinesEx(
            Rectangle{panelX, panelY, panelWidth, panelHeight},
            2.0f,
            GRAY
        );

        int textX = static_cast<int>(panelX + 20.0f);
        int y = static_cast<int>(panelY + 20.0f);

        DrawText("Telemetry Panel", textX, y, 24, RAYWHITE);
        y += 45;

        DrawText(TextFormat("Mission: %s", scenario.mission.name.c_str()), textX, y, 16, LIGHTGRAY);
        y += 28;

        DrawText(TextFormat("Type: %s", scenario.mission.type.c_str()), textX, y, 16, LIGHTGRAY);
        y += 28;

        DrawText(TextFormat("Timer: %.1f sec", missionTimeSeconds), textX, y, 18, SKYBLUE);
        y += 42;

        DrawText("Vessel", textX, y, 20, RAYWHITE);
        y += 32;

        DrawText(TextFormat("ID: %s", vesselConfig.id.c_str()), textX, y, 16, LIGHTGRAY);
        y += 26;

        DrawText(TextFormat("X: %.1f", currentPosition.x), textX, y, 16, LIGHTGRAY);
        y += 26;

        DrawText(TextFormat("Y: %.1f", currentPosition.y), textX, y, 16, LIGHTGRAY);
        y += 26;

        DrawText(TextFormat("Speed: %.1f", vesselConfig.speed), textX, y, 16, LIGHTGRAY);
        y += 26;

        DrawText(TextFormat("Heading: %.1f deg", vesselConfig.heading), textX, y, 16, LIGHTGRAY);
        y += 26;

        DrawText(TextFormat("Battery: %.1f%%", vesselConfig.battery), textX, y, 16, LIGHTGRAY);
        y += 26;

        DrawText(TextFormat("Signal: %.1f%%", vesselConfig.signalStrength), textX, y, 16, LIGHTGRAY);
        y += 42;

        DrawText("Mission Objects", textX, y, 20, RAYWHITE);
        y += 32;

        DrawText(TextFormat("Waypoints: %zu", scenario.waypoints.size()), textX, y, 16, LIGHTGRAY);
        y += 26;

        DrawText(TextFormat("Obstacles: %zu", scenario.obstacles.size()), textX, y, 16, LIGHTGRAY);
        y += 26;

        DrawText(TextFormat("Restricted Zones: %zu", scenario.restrictedZones.size()), textX, y, 16, LIGHTGRAY);
        y += 42;

        DrawText("Status", textX, y, 20, RAYWHITE);
        y += 32;

        Color statusColor = LIME;

        if (statusText != "ACTIVE") {
            statusColor = ORANGE;
        }

        DrawText(statusText.c_str(), textX, y, 18, statusColor);
        y += 48;

        DrawText("Controls", textX, y, 20, RAYWHITE);
        y += 32;

        DrawText("ESC: Close window", textX, y, 16, LIGHTGRAY);
        y += 26;

        DrawText("S: Save screenshot", textX, y, 16, LIGHTGRAY);
    }
}

RaylibRenderer::RaylibRenderer() = default;

void RaylibRenderer::run(const ScenarioData& scenario) const {
    if (scenario.vessels.empty()) {
        throw std::runtime_error("Cannot start visual renderer: scenario has no vessels");
    }

    const VesselConfig& vesselConfig = scenario.vessels.front();

    Position currentPosition = vesselConfig.startPosition;

    InitWindow(screenWidth, screenHeight, "MaritimeOpsSim Visual Demo");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        const float deltaTime = GetFrameTime();
        const double missionTimeSeconds = GetTime();

        constexpr double pi = 3.14159265358979323846;
        const double headingRadians = vesselConfig.heading * pi / 180.0;

        currentPosition.x += std::cos(headingRadians) * vesselConfig.speed * deltaTime;
        currentPosition.y += std::sin(headingRadians) * vesselConfig.speed * deltaTime;

        std::string statusText = "ACTIVE";

        if (!isInsideMapBounds(currentPosition, scenario.map)) {
            statusText = "OUT OF MAP BOUNDS";
        } else if (isInsideAnyRestrictedZone(currentPosition, scenario.restrictedZones)) {
            statusText = "WARNING: RESTRICTED ZONE";
        }

        if (IsKeyPressed(KEY_S)) {
            TakeScreenshot("../assets/screenshots/week4_basic_visual.png");
        }

        BeginDrawing();

        ClearBackground(Color{10, 12, 16, 255});

        DrawText("MaritimeOpsSim - Week 4 Visual Demo", 30, 15, 28, RAYWHITE);

        drawMapBackground(scenario);
        drawRestrictedZones(scenario);
        drawObstacles(scenario);
        drawWaypoints(scenario);
        drawDistressBeacon(scenario);
        drawVessel(vesselConfig, currentPosition, scenario);
        drawTelemetryPanel(
            scenario,
            vesselConfig,
            currentPosition,
            missionTimeSeconds,
            statusText
        );

        EndDrawing();
    }

    CloseWindow();
}