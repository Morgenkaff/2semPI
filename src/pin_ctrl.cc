/*
 *  Class for running a stepper motor (kind of) as a normal dc motor.
 *
 *  For use with 2semPi at https://github.com/Morgenkaff/2semPI
 */

#include <pigpio.h> // Library used to connect to the gpios
#include "pin_ctrl.h" 

PinCtrl::PinCtrl(){
}

bool Pin_step::init(){
    if (gpioInitialise()){
        return true;
    } else {
        return false;
    }
}

void reset(){
    // Do nothing for now
}
