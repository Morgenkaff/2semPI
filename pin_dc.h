#ifndef PIN_DC_H
#define PIN_DC_H

#include <pigpio.h> // Library used to connect to the gpios
#include "pin_base.h" // Base control of the gpios (led, switches) and definings for the pins

class Pin_dc {
private:
    
    int _speed;
    bool _direction;
    
public:
    Pin_dc(); // Simple constructor. Nothing happens
    
    Pin_dc(bool direction, int speed); // Constructiong and setting the speed and direction at once
        // Speed is sat by value from 0-255
        
    void setSpeed(int); // Stets the speed for the motor by value from 0-255
    int getSpeed(); // Stets the speed for the motor by value from 0-255
    void setDirection(bool); // Sets the direction of the motor
    bool getDirection(); // Sets the direction of the motor
};
    

#endif // PIN_DC_H
