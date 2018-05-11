#ifndef MOTOR_CTRL_H
#define MOTOR_CTRL_H

#include "motor.h"


class MotorCtrl {
private:
    
    Motor* motor_; // Pointer to a motor class. Used to changing motor types etc.
    
    bool is_running_; // Var used to store if motor is running
    
    // Vars used to control GPIOs for the "end switches"
    int close_end_switch_;
    int open_end_switch_;
    
public:
    
    MotorCtrl() = delete; // Default constructor should not be used.
    
    MotorCtrl(bool&); // Constructiong and setting the motor type, speed and direction at once
                      // 1. bool is type (see motor_type_) int is speed (see speed_)
    
    ~MotorCtrl();

    void start(int&, bool&); // Starts the motor
    void stop(); // Stops the motor
    
    bool changeMotor(bool&); // Changes the motor type (see motor_type_)
    
    bool isRunning(); // returns true if motor is running½
    
    bool getCloseEndSwitch(); // Returns true if close end switch on gripper if pressed
    
    bool getOpenEndSwitch(); // Returns true if open end switch on gripper if pressed
    
private:
    
    bool initMotor(bool&); // Constructs (and if a motor exist destructs it before constructing new).
                           // bool determines motor type (see motor_type_)
    bool termMotor();
    
    
};

#endif // MOTOR_CTRL_H
