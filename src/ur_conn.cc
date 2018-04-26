#include <pigpio.h>
#include "ur_conn.h"

UrConn::UrConn(){
    
// Declaring the pins
    
    // Inputs
    open_grip_ur_ = 11;
    close_grip_ur_ = 0;
    
    // Output
    is_ready_ = 26;
    
// Setting GPIO modes
    
    // Inputs
    gpioSetMode(open_grip_ur_, PI_INPUT);
    gpioSetMode(close_grip_ur_, PI_OUTPUT);
    
    // Output
    gpioSetMode(is_ready_, PI_OUTPUT);
    
// Setting the default values for the pins
    
    // Inputs
    gpioWrite(open_grip_ur_, 1);
    gpioWrite(close_grip_ur_, 1);
    
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

UrConn::isReady(bool b){
    gpioWrite()is_ready_, b);
}

UrConn::getOpenGrip(){
    return !gpioRead(open_grip_ur_);
}

UrConn::getCloseGrip(){
    return !gpioRead(close_grip_ur_);
}
