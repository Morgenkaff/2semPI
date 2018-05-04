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
    
    step_1_ = 20;
    step_2_ = 16;
    step_3_ = 5;
    step_4_ = 6;
    
    
    gpioSetMode(step_1_, PI_OUTPUT);
    gpioSetMode(step_2_, PI_OUTPUT);
    gpioSetMode(step_3_, PI_OUTPUT);
    gpioSetMode(step_4_, PI_OUTPUT);
    
    gpioWrite(step_1_, 0);
    gpioWrite(step_2_, 0);
    gpioWrite(step_3_, 0);
    gpioWrite(step_4_, 0);
    
    
    thread_started_ = 0;
    std::cout << "Stepper motor initiated" << std::endl;
    
}

void Stepper::run(int& i, bool& b) {
    
    step_speed_ = i;
    step_direction_ = b;
    
    step_traverser_ = 1;
    
    step_thread_ = new std::thread(&Stepper::stepDriver,this);
    thread_started_ = 1;
    std::cout << "stepper is: " << step_direction_ << std::endl;
    
}

void Stepper::stop(){
    
    
    step_traverser_ = 0;
    //_USE JOINABLE INSTEAD?_
    if (thread_started_){ // Checks if step_thread is started (if the motor is running) 
        step_thread_->join();
    }
    
    step_case_ = 0; // Reset the step_case (case loop)
    
    gpioWrite(step_1_, 0); // Turns off all the pins used for the stepper
    gpioWrite(step_2_, 0);
    gpioWrite(step_3_, 0);
    gpioWrite(step_4_, 0);
    
    std::cout << "stepper stopped" << std::endl;
    thread_started_ = 0;
    
}

void Stepper::stepDriver(){
    
    step_case_ = 0;
    
    while (step_traverser_){
        switch(step_case_){
            case 0:
                gpioWrite(step_1_, 0); 
                gpioWrite(step_2_, 0);
                gpioWrite(step_3_, 0);
                gpioWrite(step_4_, 1);
                break; 
            case 1:
                gpioWrite(step_1_, 0); 
                gpioWrite(step_2_, 0);
                gpioWrite(step_3_, 1);
                gpioWrite(step_4_, 1);
                break; 
            case 2:
                gpioWrite(step_1_, 0); 
                gpioWrite(step_2_, 0);
                gpioWrite(step_3_, 1);
                gpioWrite(step_4_, 0);
                break; 
            case 3:
                gpioWrite(step_1_, 0); 
                gpioWrite(step_2_, 1);
                gpioWrite(step_3_, 1);
                gpioWrite(step_4_, 0);
                break; 
            case 4:
                gpioWrite(step_1_, 0); 
                gpioWrite(step_2_, 1);
                gpioWrite(step_3_, 0);
                gpioWrite(step_4_, 0);
                break; 
            case 5:
                gpioWrite(step_1_, 1); 
                gpioWrite(step_2_, 1);
                gpioWrite(step_3_, 0);
                gpioWrite(step_4_, 0);
                break; 
            case 6:
                gpioWrite(step_1_, 1); 
                gpioWrite(step_2_, 0);
                gpioWrite(step_3_, 0);
                gpioWrite(step_4_, 0);
                break; 
            case 7:
                gpioWrite(step_1_, 1); 
                gpioWrite(step_2_, 0);
                gpioWrite(step_3_, 0);
                gpioWrite(step_4_, 1);
                break; 
            default:
                gpioWrite(step_1_, 0); 
                gpioWrite(step_2_, 0);
                gpioWrite(step_3_, 0);
                gpioWrite(step_4_, 0);
                break; 
        }
        if(step_direction_==1){ step_case_++;}
        if(step_direction_==0){ step_case_--;}
        if(step_case_>7){step_case_=0;}
        if(step_case_<0){step_case_=7;}
        gpioDelay(700+(step_speed_*200)); // 400+(step_speed_*200)
        //std::cout << "step: " << step_case_ << std::endl;
    }
}
