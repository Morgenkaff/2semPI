#ifndef STEP_MOTOR_H
#define STEP_MOTOR_H

#include <pigpio.h> // Library used to connect to the gpios
#include "pin_base.h" // Base control of the gpios (led, switches) and definings for the pins

class Pin_step {
private:
    
    int _speed;
    bool _direction;
    int _step_case
    
public:
    Pin_step(); // Simple constructor. Nothing happens
    
    Pin_step(bool direction, int speed); // Constructiong and setting the speed and direction at once
        // Speed is sat by value from 0-255
        
    void setSpeed(int); // Stets the speed for the motor by value from 0-255
    int getSpeed(); // Stets the speed for the motor by value from 0-255
    void setDirection(bool); // Sets the direction of the motor
    bool getDirection(); // Sets the direction of the motor
    
private:
    void _runStepper(); // Should run in a loop ina seperate thread
                        // so its possible to change speed and such
    void _set_step(int);
    void _stepTraverse();
    void _loopCase();
};

#endif // STEP_MOTOR_H
