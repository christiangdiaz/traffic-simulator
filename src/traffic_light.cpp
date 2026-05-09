#include "traffic_light.h"
#include <iostream>
#include "json.hpp"
#include <fstream>
#include <stdexcept>

using json = nlohmann::json;

TrafficLight::TrafficLight(int red_duration, int green_duration, int yellow_duration)
    : red_duration_(red_duration),
      green_duration_(green_duration),
      yellow_duration_(yellow_duration),
      current_state_(LightState::RED),
      time_in_current_state_(0){}

LightState TrafficLight::state() const {
    return current_state_;
}

int TrafficLight::duration_for(LightState s) const {
    switch (s){
        case LightState::RED: return red_duration_;
        case LightState::GREEN: return green_duration_;
        case LightState::YELLOW: return yellow_duration_;
    }
    return 0;
}

LightState TrafficLight::next_state(LightState s) const { 
    switch (s) {
        case LightState::RED: return LightState::GREEN;
        case LightState::YELLOW: return LightState::RED;
        case LightState::GREEN: return LightState::YELLOW;
    }
    return LightState::RED;
} 

void TrafficLight::tick(){
    time_in_current_state_+=1;

    if(time_in_current_state_ >= duration_for(current_state_)){
        current_state_ = next_state(current_state_);
        time_in_current_state_ = 0;
    }
}

void TrafficLight::render() const {
    const char* color = "";
    const char* state_str = "";

    switch(current_state_){
        case LightState::RED: color = "\033[31m"; state_str = "RED"; break;
        case LightState::GREEN: color = "\033[32m"; state_str = "GREEN"; break;
        case LightState::YELLOW: color = "\033[33m"; state_str = "YELLOW"; break;
    }

    std::cout << "\r\033[K"
              << "Light: " << color << "● " << state_str << "\033[0m" 
              <<" (time in state: " << time_in_current_state_ << ")" 
              << std::flush;
}

Config load_config(const std::string& path){
    std::ifstream file(path);
    if(!file.is_open()) {
        throw std::runtime_error("Could not open config file: " + path);
    }

    json data = json::parse(file);

    Config c;
    c.red_duration = data.at("red_duration").get<int>();
    c.green_duration = data.at("green_duration").get<int>();
    c.yellow_duration = data.at("yellow_duration").get<int>();
    c.total_seconds = data.at("total_seconds").get<int>();

    return c;
}