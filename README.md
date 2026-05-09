# Traffic Signal Simulator 
A configurable, console-based traffic light state machine simulator written in C++.

## What it does
Simulates a single traffic light cycling `RED -> GREEN -> YELLOW -> RED`, driven by a JSON config file that controls
each phase's duration and how long the simulation runs for. Output is console-only (the embedded way!), with the current
state and elapsed time printed each second.

## Build and run
Prereqs: C++17 compatible compiler, GNU Make. Tested on macOS with Apple Clang and GNU Make.

```
make
make run
```

To clean build artifacts, run:
```
make clean
```
### Testing
To run tests, use 
```
make test
```
Tests verify initial state, transitions, and full cycle

## Configuration
The program reads `config.json` from the current working directory at startup.
| Field | Type | Description |
| ------ | ------ | ------ |
| `red_duration` | int | Length of red light (seconds) |
| `green_duration` | int | Length of green light (seconds) | 
| `yellow_duration` | int | Length of yellow light (seconds) | 
| `total_seconds` | int | Total runtime (seconds) of simulation | 

All fields are required. Edit any field and re-run; no rebuild required.

Example `config.json`:

```json
{
  "red_duration": 5,
  "green_duration": 4,
  "yellow_duration": 2,
  "total_seconds": 25
}
```

## Design Overview
The core abstraction is a state machine with three states: `RED`, `GREEN`, and `YELLOW`. At runtime, `main` loads the configuration,
constructs a `TrafficLight`, and runs a loop that ticks the state machine forward, renders the current state to the console, and sleeps 
for one second. The state machine controls all logic, `main` only advances time.

The code is split across three files. `traffic_light.h` declares the `TrafficLight` class, the `LightState` enum, and the `Config` struct. `traffic_light.cpp` implements the class and the config loader. `main.cpp` connects it and runs the simulation loop.

I want to point out as well, I chose to implement the flow as `RED -> GREEN -> YELLOW -> RED` which is the real world order. This original assignment listed it as `RED->YELLOW->GREEN`. I wanted to flag this here for clarity.

I used JSON over INI or YAML because `nlohmann/json` is just a single header so there's no build changes or third party installs.

The unreachable default in `next_state` returns `RED` rather than something else, because if something ever does go wrong, the safer failure is everyone stops, not everyone goes.

## What's not implemented (and ideas for future improvement)
A few things were left out of this version to maintain the time budget.
- **Intersections.** I focused on getting the single-direction state machine working and well documented first. The single-light version is the foundation that a multi-light intersection would build on. 
- **Vehicle sensors and adaptive timing.** Real intersections can shorten or extend phases based on traffic. This version is purely time based. My idea for this would be to have an array of cars for each light, if a certain threshold is reached, the current timer would be halved.
- **Pedestrian crossing buttons.** This would, at the end of the current cycle at an intersection, turn all the lights red for a set period of time, allowing pedestrians to freely cross.

## How I used AI
This was my first C++ project, so I leaned heavily on AI for syntax and idioms. The design and decisions were all mine.

I chose to use Claude for this project:
- C++ syntax I didn't know, such as header guards and little things that differentiate C from C++.
- Makefile structure and an explanation of each piece.
- Library selection, like using `nlohmann/json` over other libraries.
- Code review, improving what I had, telling me what was old style vs modern, etc.
- README structure and editing. Words are my own but AI assisted with section structure and formatting.

Did myself:
- The state machine design, what to track, cycle order, tick algorithm.
- Every line of code typed, not pasted or autocompleted.
- Config schema, error handling.