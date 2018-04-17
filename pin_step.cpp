/*
 *  Class for running a stepper motor (kind of) as a normal dc motor.
 *
 *  For use with 2semPi at https://github.com/Morgenkaff/2semPI
 */

#include <pigpio.h> // Library used to connect to the gpios
#include "pin_base.h" // Base control of the gpios (led, switches) and definings for the pins
#include "pin_step.h" // Header file for this class

Pin_step::pin_step();{
    _speed = 0;
    _direction = 0;
    _runStepper(_speed, _direction);
}

Pin_step::pin_step(bool direction, int speed);{
    if (0 < speed < 256){
        _direction = direction;
        _speed = speed;
    } else {
        _speed = 0;
        _direction = 0;
    }
    
    _runStepper(_speed, _direction);
}



void Pin_dc::setSpeed(int speed){
    if (0 < speed < 256){
        _speed = speed;
    } else {
        // Do nothing
    }
    
    _runStepper(_speed, _direction);
}

int Pin_dc::getSpeed(){
    return _speed;
}

void Pin_dc::setDirection(bool direction){
    _direction = direction;
    
    _runStepper(_speed, _direction);
}

bool Pin_dc::getDirection(){
    return _direction;
}

void _runStepper(){
    
    int delay_time = 5000 - (_speed * (4300/255));
    _step_case = 1;
    
    while (_speed != 0) {
        _set_step(_step_case);
        _stepTraverse();
        _loopCase();
        gpioDelay(delay_time);
    }

void _set_step(int& step_case){
        switch(step_case){
            case 0:
                gpioWrite(STEP_1, LOW); 
                gpioWrite(STEP_2, LOW);
                gpioWrite(STEP_3, LOW);
                gpioWrite(STEP_4, HIGH);
                break; 
            case 1:
                gpioWrite(STEP_1, LOW); 
                gpioWrite(STEP_2, LOW);
                gpioWrite(STEP_3, HIGH);
                gpioWrite(STEP_4, HIGH);
                break; 
            case 2:
                gpioWrite(STEP_1, LOW); 
                gpioWrite(STEP_2, LOW);
                gpioWrite(STEP_3, HIGH);
                gpioWrite(STEP_4, LOW);
                break; 
            case 3:
                gpioWrite(STEP_1, LOW); 
                gpioWrite(STEP_2, HIGH);
                gpioWrite(STEP_3, HIGH);
                gpioWrite(STEP_4, LOW);
                break; 
            case 4:
                gpioWrite(STEP_1, LOW); 
                gpioWrite(STEP_2, HIGH);
                gpioWrite(STEP_3, LOW);
                gpioWrite(STEP_4, LOW);
                break; 
            case 5:
                gpioWrite(STEP_1, HIGH); 
                gpioWrite(STEP_2, HIGH);
                gpioWrite(STEP_3, LOW);
                gpioWrite(STEP_4, LOW);
                break; 
            case 6:
                gpioWrite(STEP_1, HIGH); 
                gpioWrite(STEP_2, LOW);
                gpioWrite(STEP_3, LOW);
                gpioWrite(STEP_4, LOW);
                break; 
            case 7:
                gpioWrite(STEP_1, HIGH); 
                gpioWrite(STEP_2, LOW);
                gpioWrite(STEP_3, LOW);
                gpioWrite(STEP_4, HIGH);
                break; 
            default:
                gpioWrite(STEP_1, LOW); 
                gpioWrite(STEP_2, LOW);
                gpioWrite(STEP_3, LOW);
                gpioWrite(STEP_4, LOW);
                break; 
        }
}

/*
 * This function traverse the step_case, depending on the direction.
 */
void _stepTraverse(){
    if(_direction==1){ _step_case++;}
    if(_direction==0){ _step_case--;}
}

/*
 * This function changes the var step_case, securing that the case switch
 * will "loop around".
 */
void _loopCase(){    
    if(_step_case>7){_step_case=0;}
    if(_step_case<0){_step_case=7;}
}

