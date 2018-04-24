/*
 *  Class for running a stepper motor (kind of) as a normal dc motor.
 *
 *  For use with 2semPi at https://github.com/Morgenkaff/2semPI
 */

// Should be removed when in working order:
#include <iostream>

#include <pigpio.h> // Library used to connect to the gpios
#include "stepper.h" // Header file for this class
#include <thread>

Stepper::Stepper(){
    
    step_1_ = 19;
    step_2_ = 13;
    step_3_ = 6;
    step_4_ = 5;
    
    std::cout << "Stepper motor initiated" << std::endl;
    
}

void Stepper::run(int& i, bool& b) {
    
    step_speed_ = 1;
    step_direction_ = b;
    step_traverser_ = 1;
    
    thread_ = new std::thread(&Stepper::stepDriver,this);
    
}

void Stepper::stop(){
    
    
    step_traverser_ = 0;
    
    thread_->join();
    
    std::cout << "stepper stopped" << std::endl;
    
}

void Stepper::stepDriver(){
    
    while (step_traverser_){
        std::cout << "stepper is: " << step_direction_ << std::endl;
        gpioSleep(PI_TIME_RELATIVE, 1, 0);
    }
    
    /*
    for (step_traverser_ ; step_traverser_ < 9 ; step_traverser_ + step_direction_) {
        std::cout << "stepper" << step_traverser_ << std::endl;
    }
    */
}
