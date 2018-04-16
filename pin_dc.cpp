
/*
 *  Program for testing c++ on the Pi and how to control the GPIOs with it.
 *  The library for using GPIOs is pigpio (http://abyz.me.uk/rpi/pigpio).
 *
 *  To build the code, use the command:
 *
 *    g++ -o "name_of_output_file" "name_of_input_file".cpp -lpigpio -lrt
 *
 *  lpigpio includes the pigpio library and lrt is to include the library for realtime functionality
 *  (required by pigpio).
 */

/*
 *  Libraries:
 *  iostream used for on screen feedback and debuggin
 *  pigpio for the GPIO
 */
#include <pigpio.h>
#include "pin_base.h"
#include "pin_dc.h"

Pin_dc::Pin_dc(){
    _speed = 0;
    _direction = 0;
    gpioWrite(MOTOR_DIR, _direction);
}

Pin_dc::Pin_dc(bool direction, int speed){
    if (0 < speed < 256){
        _direction = direction;
        _speed = speed;
    } else {
        _speed = 0;
        _direction = 0;
    }
        
    gpioWrite(MOTOR_DIR, _direction);
    gpioPWM(MOTOR_RUN, _speed);
}

void Pin_dc::setSpeed(int speed){
    if (0 < speed < 256){
        _speed = speed;
    } else {
        // Do nothing
    }
    gpioPWM(MOTOR_RUN, _speed);
}

int Pin_dc::getSpeed(){
    return _speed;
}

void Pin_dc::setDirection(bool direction){
    _direction = direction;
    gpioWrite(MOTOR_DIR, _direction);
}

bool Pin_dc::getDirection(){
    return _direction;
}
