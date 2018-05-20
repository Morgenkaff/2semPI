#ifndef GRIPPER_CONN_H
#define GRIPPER_CONN_H

#include "motor.h"
#include "logger.h"
#include "timer.h"

class GripperConn {
private:
    
    Logger* log;
    Timer* timer;
    
    Motor* motor; // Pointer to a motor class. Used to changing motor types etc.
    
    bool is_running_; // Var used to store if motor is running
    bool direction_;  // store current direction sat
    bool motor_type_; // Stores motor type
    
    // Vars used to control GPIOs for the "end switches"
    int close_end_switch_;
    int open_end_switch_;
    
    // Vars used for logging:
    int total_runtime_;
    int total_starts_;
    int total_stops_;
    int total_releases_;
    
public:
    
    GripperConn() = delete; // Default constructor should not be used.
    
    GripperConn(bool&); // Constructiong and setting the motor type, speed and direction at once
                      // 1. bool is type (see motor_type_) int is speed (see speed_)
    
    ~GripperConn();

    void start(int&, bool&); // Starts the motor
                             // If motor is allready running in set direction it does nothing
                             // If motor is allready running in opposite direction it changes direction
    void stop(); // Stops the motor
    
    void releaseObject(int&, bool&); // Runs the motor for a short time in the open direction
    
    void changeMotor(bool&); // Changes the motor type (see motor_type_)
    
    bool isRunning(); // returns true if motor is running½
    
    bool getCloseEndSwitch(); // Returns true if close end switch on gripper if pressed
    
    bool getOpenEndSwitch(); // Returns true if open end switch on gripper if pressed
    
private:
    
    void initMotor(bool&); // Constructs (and if a motor exist destructs it before constructing new).
                           // bool determines motor type (see motor_type_)
    void termMotor();
    
    
};

#endif // GRIPPER_CONN_H
