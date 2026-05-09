#pragma once
#include <string>

struct Config{
    int red_duration;
    int green_duration;
    int yellow_duration;
    int total_seconds;
};

Config load_config(const std::string& path);



enum class LightState {
    RED,
    GREEN,
    YELLOW
};

class TrafficLight {
public: 
    TrafficLight(int red_duration, int green_duration, int yellow_duration);

    void tick();

    void render() const;

    LightState state() const;

private:
    int red_duration_;
    int green_duration_;
    int yellow_duration_;
    LightState current_state_;
    int time_in_current_state_;
    int duration_for(LightState s) const;
    LightState next_state(LightState s) const;
};