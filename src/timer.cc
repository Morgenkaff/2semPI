/*
 * Counts time between start- and stop-functions have been called in seconds.
 * Stop functions returns the duration as long int
 * 
 * Time is based on system time
 * 
 * void start();
 * long int stop();
 * 
 */

// Includes ctime, to get time
#include <ctime>
#include "timer.h"

Timer::Timer() {
    
    //Vars used for timer
    total_runtime_ = 0;
    runtime_start_time_ = 0;
    runtime_stop_time_ = 0;
    
}

void Timer::start(){
    
    runtime_start_time_ = static_cast<long int>(std::time(nullptr));
    
}

int Timer::stop(){
    
    runtime_stop_time_ = static_cast<long int>(std::time(nullptr));
    // std::cout << "runtime stop: " << runtime_stop_time_ << std::endl;
    
    int time_diff = runtime_stop_time_ - runtime_start_time_;
    // std::cout << "Time difference: " << time_diff << std::endl;
    
    total_runtime_ += time_diff;
    // std::cout << "runtime total: " << total_runtime_ << std::endl;
    
    return total_runtime_;
}
