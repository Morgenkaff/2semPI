#ifndef PIN_CTRL_H
#define PIN_CTRL_H

#include <pigpio.h> // Library used to connect to the gpios

class PinCtrl {
private:
    
    // Vars (maybe?) used for handling the motor (type, speed etc): - saved for when moto class is written
    // bool default_motor_; 
    // bool motor_type_;
    // int speed_;
    // bool direction_;
    
public:
    PinCtrl(); // Simple constructor. Nothing happens
    
    bool init(); // Initialises the GPIOs. Returns 1 if success.
    void reset(); // Resets all the pins to their default state.
    
    
    // MORE FUNCTIUONS FOR MOTORS
    
    
private:
    
};

#endif // PIN_CTRL_H
