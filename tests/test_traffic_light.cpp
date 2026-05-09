#include "../src/traffic_light.h"
#include <iostream>
#include <string>

int tests_passed = 0;
int tests_failed = 0;

#define ASSERT_EQ(actual, expected, name) \
    do { \
        if((actual) == (expected)) {\
        std::cout << " PASS: " << name << std::endl; \
        tests_passed++; \
    } else { \
        std::cout << " Fail: " << name << std::endl; \
        tests_failed++; \
    } \
    } while(0)

const char* state_name(LightState s){
    switch(s) {
        case LightState::RED: return "RED";
        case LightState::GREEN: return "GREEN";
        case LightState::YELLOW: return "YELLOW";
    }
    return "UNKNOWN";
}

void test_initial_state_is_red() {
    std::cout << "Test: initial state is RED" << std::endl;
    TrafficLight light(5,4,2);
    ASSERT_EQ(light.state(), LightState::RED, "starts in RED");
}

void test_red_to_green(){
    std::cout << "Test: RED transitions to GREEN after red_duration ticks" << std::endl;
    TrafficLight light(5,4,1);

    light.tick();
    light.tick();
    light.tick();
    light.tick();

    ASSERT_EQ(light.state(), LightState::RED, "Still RED after 4 ticks");

    light.tick();

    ASSERT_EQ(light.state(), LightState::GREEN, "Changed to GREEN on the fifth tick");
}

void test_green_to_yellow() {
    std::cout << "Test: GREEN goes to YELLOW after green_duration ticks" << std::endl;
    TrafficLight light(1,3,2);

    light.tick();
    light.tick();
    light.tick();

    ASSERT_EQ(light.state(), LightState::GREEN, "Light is green after 4 ticks (1 tick extra from starting at red)");

    light.tick();

    ASSERT_EQ(light.state(), LightState::YELLOW, "Light is yellow on the next tick");
}

void test_yellow_to_red(){
    std::cout << "Test: YELLOW goes to RED after yellow_duration ends" << std::endl;
    TrafficLight light(5,4,2);

    for(int i = 0; i<9;i++){
        light.tick();
    }

    ASSERT_EQ(light.state(), LightState::YELLOW, "Light is yellow after red green durations");

    light.tick();
    light.tick();

    ASSERT_EQ(light.state(), LightState::RED, "Light is red after the yellow_duration ticks");
}

void test_full_cycle(){
    std::cout << "Test: full cycles starts and ends at RED" <<std::endl;
    TrafficLight light(3,3,1);

    for(int i = 0; i<7; i++){
        light.tick();
    }

    ASSERT_EQ(light.state(), LightState::RED, "Light is RED after the full cycle");
}

int main(){
    std::cout << "Running Traffic Light tests..." << std::endl;
    std::cout << "==============================" << std::endl;

    test_initial_state_is_red();
    test_red_to_green();
    test_green_to_yellow();
    test_yellow_to_red();
    test_full_cycle();

    std::cout << "==============================" << std::endl;
    std::cout << "Results: " << tests_passed << " passed, "
              << tests_failed << " failed." << std::endl;
    
    return tests_failed > 0 ? 1 : 0;
}