#include "pin_base.h"

Pin_base::Pin_base(){
}

bool Pin_base::init(){
    if (gpioInitialise()){
        
        // Setting the modes for std control (switches, leds etc)
        gpioSetMode(ST_LED, PI_OUTPUT); // pin2 
        gpioSetMode(SW_OPEN, PI_INPUT); // pin3 
        gpioSetMode(SW_CLOSED, PI_INPUT); // pin4 
        gpioSetMode(SW_KILL, PI_INPUT); // pin22 
        
        // Setting the modes for controlling the dc motor or magnet
        gpioSetMode(MOTOR_RUN, PI_OUTPUT); // pin17 
        gpioSetMode(MOTOR_DIR, PI_OUTPUT); // pin27 
        
        // Setting the modes for the stepper motor
        gpioSetMode(STEP_1, PI_OUTPUT); // pin26
        gpioSetMode(STEP_2, PI_OUTPUT); // pin19
        gpioSetMode(STEP_3, PI_OUTPUT); // pin13
        gpioSetMode(STEP_4, PI_OUTPUT); // pin6
        
        _gpio_on = true; //Not used right now, might be used for dif. inits later
        
        return true;
    } else {
        return false;
    }
}

bool Pin_base::term(){
    
    // Setting the modes for std control (switches, leds etc)
    gpioWrite(ST_LED, LOW); // pin2 
    gpioWrite(SW_OPEN, HIGH); // pin3 
    gpioWrite(SW_CLOSED, HIGH); // pin4  
    gpioWrite(SW_KILL, HIGH); // pin22 
    
    // Setting the modes for controlling the dc motor or magnet
    gpioWrite(MOTOR_RUN, LOW); // pin17 
    gpioWrite(MOTOR_DIR, LOW); // pin27 
    
    // Setting the modes for the stepper motor
    gpioWrite(STEP_1, LOW); // pin26
    gpioWrite(STEP_2, LOW); // pin19
    gpioWrite(STEP_3, LOW); // pin13
    gpioWrite(STEP_4, LOW); // pin6
    
    /*
     * And lastly terminating pigpio again
     */
    gpioTerminate();
}

void Pin_base::setLED(bool on){
    gpioWrite(ST_LED, on);
}

bool Pin_base::getSw(int sw){
    switch(sw){
        case 1:
            return !gpioRead(SW_OPEN);
            break;
        case 2:
            return !gpioRead(SW_CLOSED);
            break;
        case 3:
            return !gpioRead(SW_KILL);
            break;
        default:
            return false;
            break;
    }
}
    
    
    
    
