
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
}

Pin_dc::Pin_dc(bool direction, int speed){
    if (0 < speed < 256){
        _direction = direction;
        _speed = speed;
    } else {
        _speed = 0;
        _direction = 0;
    }
        
    runMotor(_speed, _direction);
}

void Pin_dc::runMotor(int& speed, bool& direction){
    if (direction == 0) {
        gpioPWM(MOTOR_RUN_L, 0);
        gpioPWM(MOTOR_RUN_R, _speed);
    } else if (_direction == 1) {
        gpioPWM(MOTOR_RUN_L, _speed);
        gpioPWM(MOTOR_RUN_R, 0);
    }
}

void Pin_dc::setSpeed(int speed){
    if (0 < speed < 256){
        _speed = speed;
    } else {
        // Do nothing
    }
        
    runMotor(_speed, _direction);
}

int Pin_dc::getSpeed(){
    return _speed;
}

void Pin_dc::setDirection(bool direction){
    _direction = direction;
        
    runMotor(_speed, _direction);
}

bool Pin_dc::getDirection(){
    return _direction;
}
