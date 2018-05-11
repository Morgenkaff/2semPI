#include <pigpio.h>
#include "ur_conn.h"


#include <iostream> // For debuggin

UrConn::UrConn(){
    
// Declaring the pins
    
    // Inputs
    open_grip_ur_ = 9;
    close_grip_ur_ = 11;
    
    // Output
    is_ready_ = 16;
    
// Setting GPIO modes
    
    // Inputs
    gpioSetMode(open_grip_ur_, PI_INPUT);
    gpioSetMode(close_grip_ur_, PI_INPUT);
    
    // Output
    gpioSetMode(is_ready_, PI_OUTPUT);
    
// Setting the default values for the pins
    
    // Inputs
    gpioWrite(open_grip_ur_, 0);
    gpioWrite(close_grip_ur_, 0);
    
    // Outputs
    gpioWrite(is_ready_, 0);

}

UrConn::~UrConn() {
    
    // Inputs
    gpioSetMode(open_grip_ur_, 0);
    gpioSetMode(close_grip_ur_, 0);
    
    // Output
    gpioWrite(is_ready_, 1);
    
}

void UrConn::isReady(bool b){
          //  std::cout << "send ready" << b<< std::endl;
    gpioWrite(is_ready_, b);
}

bool UrConn::getOpenGrip(){
        //    std::cout << "get open"<< std::endl;
    return gpioRead(open_grip_ur_);
}

bool UrConn::getCloseGrip(){
          //  std::cout << "get close"<< std::endl;
    return gpioRead(close_grip_ur_);
}
