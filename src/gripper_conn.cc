
/*
 *  Class for interfacing with the motor. It does not interact directly with the GPIOs to control the motor.
 *  Instead it constructs either a stepper or dc class, depending on parametres in its own constructor, or by a 
 *  member function. It does however control the GPIOs for the "end switches" on the gripper.
 *  This method is choosen over eg a interface/abstract class to prevent situation with drastically 
 *  different "gripper methods" such as electro magnets and such, and because this class then can be used
 *  to store loggin data about motor travel, torque etc, keep the speed between motors etc.
 *  Might be usefull if the motor will be runned in seperate thread..
 */

#include <pigpio.h>
#include "gripper_conn.h"
#include "dc.h"
#include "stepper.h"
#include <iostream>

GripperConn::GripperConn(bool& motor){
    
    log = new Logger('b', "motor.log");
    timer = new Timer();
    // Switch on gripper, that shorts to gnd when gripper is fully closed:
    close_end_switch_ = 22;
    gpioSetMode(close_end_switch_, PI_INPUT);
    
    // Switch on gripper, that shorts to gnd when gripper is fully open:
    open_end_switch_ = 10;
    gpioSetMode(open_end_switch_, PI_INPUT);
    
    // Constructing motor
    initMotor(motor);
    
    log->write("Motor initialized");
    
    total_runtime_ = 0;
    total_starts_ = 0;
    total_stops_ = 0;
    total_releases_ = 0;
    
}

GripperConn::~GripperConn(){
    
    termMotor();    
    log->write("                             ");
    log->write("  Terminating motor, stats:  ");
    log->write("-----------------------------");
    if (motor_type_){
        log->write("Motor type: stepper motor");
    } else {
        log->write("Motor type: dc motor");
    }
    log->write("Total starts of motor: "+std::to_string(total_starts_));
    log->write("Total stops of motor: "+std::to_string(total_stops_));
    log->write("Total releases by motor: "+std::to_string(total_releases_));
    log->write("Total runtime of motor: "+std::to_string(total_runtime_));
    log->write("-----------------------------");
}

void GripperConn::start(int& speed, bool& direction){
    if (!is_running_){ // Motor not running
        motor->run(speed, direction); // Starts in set direction
        is_running_ = 1;
        timer->start(); // Starts the timer, to track motor runtime
        total_starts_ ++;
    } else if (is_running_ && direction_ == direction){  // is running in set direction
        // Do nothing
    } else if (is_running_ && direction_ != direction) { // is running in opp. direction
        motor->stop(); // Stops the motor, to prevent possible complications with conflicting signals
        motor->run(speed, direction); // Starts (again) in new set direction
    }
}

void GripperConn::stop(){
    
    if (is_running_) { // Only send stop command if motor is running
        motor->stop();
        total_runtime_ += timer->stop();
        is_running_ = 0;
        total_stops_ ++;
    }
}

void GripperConn::releaseObject(int& speed, bool& direction){
    motor->run(speed, direction); // direction is used here too, (if pin_ctrl should change something)
    timer->start(); // Starts the timer, to track motor runtime
    is_running_ = 1;
    gpioSleep(PI_TIME_RELATIVE, 1, 500000);
    motor->stop();
    total_runtime_ += timer->stop();
    is_running_ = 0;
    total_releases_ ++;
}

void GripperConn::changeMotor(bool& type){
    termMotor();
    initMotor(type);
    if (motor_type_){
        log->write("Motor type changed to stepper motor");
    } else {
        log->write("Motor type changed to dc motor");
    }
}

bool GripperConn::isRunning(){
    return is_running_;
}

bool GripperConn::getCloseEndSwitch() {
    return !gpioRead(close_end_switch_); // Negated as switch short to gnd. (low "converted" to true)
}

bool GripperConn::getOpenEndSwitch() {
    return !gpioRead(open_end_switch_); // Negated as switch short to gnd. (low "converted" to true)
}

// Privates:
void GripperConn::initMotor(bool& type){
    
    motor_type_ = type;
    
    if (motor_type_){
        motor = new Stepper();
    } else if (!motor_type_) {
        motor = new Dc();
    } else {
    }
}
    
void GripperConn::termMotor(){
    
    delete motor;
}
