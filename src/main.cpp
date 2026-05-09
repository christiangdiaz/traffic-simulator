#include <iostream> 
#include "traffic_light.h"
#include <chrono>
#include <thread>

int main() {
    try{
        Config config = load_config("config.json");
        
        std::cout << "Traffic Signal Simulator" << std::endl;
        std::cout << "Loaded config: red=" << config.red_duration
                  << "s, green=" << config.green_duration
                  << "s, yellow=" << config.yellow_duration << "s" << std::endl;

        TrafficLight light1(config.red_duration, config.green_duration, config.yellow_duration);

        for(int i =0; i<config.total_seconds; ++i){
            light1.render();        
            std::this_thread::sleep_for(std::chrono::seconds(1));
            light1.tick();
        }
        std::cout << std::endl;
    } catch (const std::exception& e){
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}