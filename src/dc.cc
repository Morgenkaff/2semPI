// Should be removed when in working order:
#include <iostream>


#include <pigpio.h>
#include "dc.h"

Dc::Dc(){
    
    // Setting the pins used:
    run_open_ = 19;
    run_close_ = 13;
    
    gpioSetMode(run_open_, PI_OUTPUT);
    gpioSetMode(run_close_, PI_OUTPUT);
    
    gpioPWM(run_open_, 0);
    gpioPWM(run_close_, 0);
        
    std::cout << "DC motor initiated" << std::endl;
    
}

Dc::~Dc(){
}
    

void Dc::run(int& speed, bool& direction){

    // If statement based on given value for direction determine which
    // pin to be set to given speed.
    
    if (direction){   
    std::cout << "DC is opening" << std::endl;                
                                 
        gpioPWM(run_close_,0);      // For safety is the pin for the opposite direction set to 0
        gpioPWM(run_open_, speed*80);    // Multiplies the given value for speed with 80, to get usefull value
                                    // in the range of 0 - 255 that is default for pigpio PWM
    } else {
    std::cout << "DC is closing" << std::endl;                
        
        gpioPWM(run_open_, 0);
        gpioPWM(run_close_, speed*80);
        
    }
    
}

void Dc::stop(){
    std::cout << "DC is stopped" << std::endl;
    
    gpioPWM(run_open_, 0);
    gpioPWM(run_close_, 0);
    
}
