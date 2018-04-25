#ifndef MOTOR_CTRL_H
#define MOTOR_CTRL_H

#include "motor.h"


class MotorCtrl {
private:
    
    bool motor_type_; // Bool: 1 = stepper, 0 = dc.
                      // Could be changed to eg int, if we get more than 2 motor types
    bool direction_; // 1 = opening, 0 = closing
    int speed_; // Speed is set in a range of 1 - 3 (1 is slowest 3 is fastest)
    
    Motor* motor_;
    
    // Vars used to control GPIOs for the "end switches"
    int open_end_grip_;
    int close_end_grip_;
    
public:
    
    MotorCtrl() = delete; // Default constructor should not be used.
    
    MotorCtrl(bool&, bool&, int&); // Constructiong and setting the motor type, speed and direction at once
                            // 1. bool is type (see motor_type_), 2. bool is direction (see direction_)
                            // int is speed (see speed_)
    
    ~MotorCtrl();

    void start(); // Starts the motor
    void stop(); // Stops the motor
    
    bool changeMotor(bool&); // Changes the motor type (see motor_type_)
    void setSpeed(int); // int is speed (see speed_)
    int getSpeed(); // Returns the value of speed_
    void setDirection(bool); // bool is direction (see direction_)
    bool getDirection(); // Returns the value of direction_
    
    bool getOpenEnd();
    bool getCloseEnd();
    
private:
    void runMotor(int&, bool&); // Function used to run motor 
    // Probably redundant
    
    bool initMotor(bool&); // Constructs (and if a motor exist destructs it before constructing new).
                           // bool determines motor type (see motor_type_)
    bool termMotor();
    
    
};

#endif // MOTOR_CTRL_H