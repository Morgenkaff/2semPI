
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
#include "motor_ctrl.h"
#include "dc.h"
#include "stepper.h"

MotorCtrl::MotorCtrl(bool& motor){
    
    // Switch on gripper, that shorts to gnd when gripper is fully closed:
    close_end_switch_ = 22;
    gpioSetMode(close_end_switch_, PI_INPUT);
    
    // Switch on gripper, that shorts to gnd when gripper is fully open:
    open_end_switch_ = 10;
    gpioSetMode(open_end_switch_, PI_INPUT);
    
    // Constructing motor
    initMotor(motor);
    
}

MotorCtrl::~MotorCtrl(){
    termMotor();
}

void MotorCtrl::start(int& speed, bool& direction){
    motor_->run(speed, direction);
    is_running_ = 1;
}

void MotorCtrl::stop(){
    motor_->stop();
    is_running_ = 0;
}

void MotorCtrl::changeMotor(bool& type){
    termMotor();
    initMotor(type);
}

bool MotorCtrl::isRunning(){
    return is_running_;
}

bool MotorCtrl::getCloseEndSwitch() {
    return !gpioRead(close_end_switch_); // Negated as switch short to gnd. (low "converted" to true)
}

bool MotorCtrl::getOpenEndSwitch() {
    return !gpioRead(open_end_switch_); // Negated as switch short to gnd. (low "converted" to true)
}

// Privates:
void MotorCtrl::initMotor(bool& type){
    if (type){
        motor_ = new Stepper();
    } else if (!type) {
        motor_ = new Dc();
    } else {
    }
}
    
void MotorCtrl::termMotor(){
    delete motor_;
}
