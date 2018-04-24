/*
 * Class used to control the GPIO and belonging classes.
 */

#include <pigpio.h> // Library used to connect to the gpios
#include <thread> // Used to run hid in seperate thread.
#include <iostream>

#include "motor_ctrl.h"

#include "pin_ctrl.h" // Own header file

PinCtrl::PinCtrl(){
}

PinCtrl::~PinCtrl(){
    terminate();
}

bool PinCtrl::init(){
    
    if (gpioInitialise() >= 0){
        
        hid = new Hid;
        
        hid->setGreenLed(1);
        
        motor_ctrl = new MotorCtrl(motor_type_, direction_, speed_);
        
        
        
        return 1;
        
    } else {
        return 0;
    }
}

void PinCtrl::run(int state){
    
    running_ = 1;
    run_state_ = state;
    
    while (running_){
        
        switch(run_state_){
            case 1:
                
                working();
                break;
                
            case 2:
                
                standby();
                break;
                
            //default:
                
                // Do nothing
                //std::cout << "default state" << std::endl;
                        
        }
        
    }
    
}

void PinCtrl::working(){ //When motor is set and all
    
    
    in_working_loop_ = 1;
    //std::cout << "working loop" << std::endl;
    if (hid->getKillSwitch()) {
        hid->setRedLed(1);
        gpioSleep(PI_TIME_RELATIVE, 3, 0);
        if (hid->getKillSwitch()){
            run_state_ = 2;
            hid->setRedLed(0);
            hid->setCloseLed(0);
            hid->setOpenLed(0);
            in_working_loop_ = 0;
            gpioSleep(PI_TIME_RELATIVE, 1, 0);
        } else {
            hid->setGreenLed(1);
        }
    } else if (hid->getOpenGrip()) {
        hid->setCloseLed(0);
        hid->setOpenLed(1);
        motor_ctrl->setDirection(1);
        
    } else if (hid->getCloseGrip()) {
        hid->setOpenLed(0);
        hid->setCloseLed(1);
        motor_ctrl->setDirection(0);
        
    } else if (hid->getOpenEnd()) {
        hid->setOpenLed(0);
        motor_ctrl->stop();
        
    } else if (hid->getCloseEnd()) {
        hid->setCloseLed(0);
        motor_ctrl->stop();
    }
    
    //gpioSleep(PI_TIME_RELATIVE, 1, 0);
    
}

void PinCtrl::standby(){ // For problems(?) and motor change and such
    in_standby_loop_ = 1;    
    
    while (in_standby_loop_){ // Loop is not nescessary now. But might be later, so its let be for now
        
        hid->setRedLed(1);
        
        //std::cout << "standby loop" << std::endl;
        if (hid->getCloseGrip() && hid->getOpenGrip()) {
            hid->setOpenLed(1);
            gpioSleep(PI_TIME_RELATIVE, 1, 0);
            if (hid->getCloseGrip() && hid->getOpenGrip()){
                hid->setCloseLed(1);
                gpioSleep(PI_TIME_RELATIVE, 1, 0);
                if (hid->getCloseGrip() && hid->getOpenGrip()) {
                    if (motor_type_) {
                        motor_type_ = 0;
                    } else if (!motor_type_) {
                        motor_type_ = 1;
                    }
                    motor_ctrl->changeMotor(motor_type_);
                    gpioSleep(PI_TIME_RELATIVE, 1, 0);
                    hid->setOpenLed(0);
                    hid->setCloseLed(0);
                    run_state_ = 1;
                    in_standby_loop_ = 0;
                } 
            }
            
            hid->setOpenLed(0);
            hid->setCloseLed(0);
            
        } else if (hid->getKillSwitch()) {
            gpioSleep(PI_TIME_RELATIVE, 2, 0);
            if (hid->getKillSwitch()){
                hid->setRedLed(0);
                gpioSleep(PI_TIME_RELATIVE, 0, 500000);
                hid->setGreenLed(1);
                gpioSleep(PI_TIME_RELATIVE, 1, 0);
                run_state_ = 1;
                in_standby_loop_ = 0;
            }
        } else if (hid->getCloseEnd() && hid->getOpenEnd()) {
            hid->setOpenLed(1);
            gpioSleep(PI_TIME_RELATIVE, 1, 0);
            if (hid->getCloseEnd() && hid->getOpenEnd()){
                hid->setCloseLed(1);
                gpioSleep(PI_TIME_RELATIVE, 1, 0);
                if (hid->getCloseEnd() && hid->getOpenEnd()) {
                    // Change default motor
                    gpioSleep(PI_TIME_RELATIVE, 1, 0);
                    hid->setOpenLed(0);
                    hid->setCloseLed(0);
                    exit(1);
                } 
            }
            
            hid->setOpenLed(0);
            hid->setCloseLed(0);
            
        } else {
            // Do nothing
        }
        gpioSleep(PI_TIME_RELATIVE, 1, 0);
        
        hid->setGreenLed(1);
        
        gpioSleep(PI_TIME_RELATIVE, 0, 200000); // sleep commands used for timing of led.
                                                // Could be controlled in seperate thread?
        
    }
    
}

void PinCtrl::reset(){
    delete hid;
    hid = new Hid;
}

bool PinCtrl::terminate(){
    //scan_inputs_ = false; // Stops the inputScanThread while loop scanning for inputs
    delete hid;
    gpioTerminate();
}

void PinCtrl::setMotorType(bool& b){
    motor_type_ = b;
}
     
void PinCtrl::setMotorSpeed(int& i){
    speed_ = i;
}
    
void PinCtrl::setMotorDirection(bool& b){
    direction_ = b;
}
