
/*
 *  Class for interfacing with the motor. It does not interact directly with the GPIOs, instead it
 *  constructs either a stepper or dc class, depending on parametres in its own constructor, or by a 
 *  member function.
 *  This method is choosen over eg a interface/abstract class to prevent situation with drastically 
 *  different "gripper methods" such as electro magnets and such, and because this class then can be used
 *  to store loggin data about motor travel, torque etc, keep the speed between motors etc.
 *  Might be usefull if the motor will be runned in seperate thread..
 *  
 */

#include <iostream>
#include <pigpio.h>
#include "motor_ctrl.h"
#include "dc.h"
#include "stepper.h"

MotorCtrl::MotorCtrl(bool& motor, bool& dir, int& speed){
    direction_ = dir;
    speed_ = speed;
    initMotor(motor);
}

MotorCtrl::~MotorCtrl(){
    termMotor();
}

void MotorCtrl::start(){
    motor_->run(speed_, direction_);
}

void MotorCtrl::stop(){
    motor_->stop();
}

bool MotorCtrl::changeMotor(bool& b){
    termMotor();
    initMotor(b);
}

void MotorCtrl::setSpeed(int& i){
    speed_ = i;
    motor_->run(speed_, direction_);
}

int MotorCtrl::getSpeed(){
    return speed_;
}

void MotorCtrl::setDirection(bool b){
    motor_->run(speed_, b);
}

bool MotorCtrl::getDirection(){
    return direction_;
}

/*
void Motor::runMotor(){ // Probably redundant
}*/

bool MotorCtrl::initMotor(bool& type){
    if (type){
        motor_ = new Stepper();
        return 1;
    } else if (!type) {
        motor_ = new Dc();
        return 1;
    } else {
        return 0;
    }
}
    
bool MotorCtrl::termMotor(){
    delete motor_;
}
