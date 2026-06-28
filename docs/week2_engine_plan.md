# Week 2 Engine Plan

## Goal

Build the basic C++ simulation engine structure for MaritimeOpsSim.

## Week 2 Core Modules

### Vessel

Represents an unmanned surface vessel.

Initial fields:

- id
- x position
- y position
- speed
- heading
- battery

Initial behavior:

- store vessel state
- update vessel position
- print vessel telemetry

### Mission

Represents the current mission.

Initial fields:

- mission name
- mission type
- mission status
- elapsed time

Initial behavior:

- start mission
- update mission time
- track mission status

### SimulationEngine

Coordinates the simulation loop.

Initial behavior:

- initialize mission
- initialize vessel
- run update loop
- advance simulation time
- update vessel state
- print console telemetry

## Week 2 Definition of Done

Week 2 is complete when:

- Vessel class exists
- Mission class exists
- SimulationEngine class exists
- main.cpp uses SimulationEngine
- one simulated USV moves from one point to another
- console telemetry output works
- project builds with CMake
- project runs successfully
