/*
 * Class used to control the GPIO and belonging classes.
 */

#include <pigpio.h> // Library used to connect to the gpios
#include <thread> // Used to run hid in seperate thread.
#include <iostream> // For debuggin

#include "motor_ctrl.h" // 
//#include "ur_conn.h"
#include "pin_ctrl.h" // Own header file

PinCtrl::PinCtrl(){
}

PinCtrl::~PinCtrl(){
    //gpioTerminate();
    terminate();        
    std::cout << "GPIOs terminated" << std::endl;
}

bool PinCtrl::init(){
    
    bool ready = gpioInitialise() >= 0;
    
    if (ready){
        
        hid = new Hid; // Constructing the HID class
        
        ur_conn = new UrConn; // Constructing the UrConn class
        
        motor_ctrl = new MotorCtrl(motor_type_, direction_, speed_); // Constructing the motor control class 
        
        motor_running_ = 0; // Motor not yes started
        temp_direction_ = direction_;
        
        input_scan_thread = new std::thread(&PinCtrl::inputScanner,this);
        std::cout << "Thread created! " << std::endl;
        
        
        return 1;
        
    } else {
        return 0;
    }
}

void PinCtrl::reset(){
    delete hid;
    hid = new Hid;
}

bool PinCtrl::terminate(){
    scan_inputs_ = 0; // Stops the inputScanThread while loop scanning for inputs
    input_scan_thread->join();;
    std::cout << "Thread joined! " << std::endl;
    
    delete hid;
    delete ur_conn;
    gpioTerminate();
}


void PinCtrl::run(int state){
    
    running_ = 1;
    run_state_ = state;
    
    while (running_){
        
        switch(run_state_){
            case 1: // Working loop should be created
            std::cout << "working"<< std::endl;
                
                
                working();
                break;
                
            case 2:
                
            std::cout << "standby"<< std::endl;
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
    ur_conn->isReady(1); // Signals to UR that it is ready
    
    while (in_working_loop_){
    
    if (input_ == 1) { // "Killing signal"
        hid->setRedLed(1);
        gpioSleep(PI_TIME_RELATIVE, 3, 0);
        if (input_ == 1){
            motor_ctrl->stop();
            motor_running_ = 0;
            hid->setRedLed(0);
            hid->setCloseLed(0);
            hid->setOpenLed(0);
            run_state_ = 2;
            in_working_loop_ = 0;
            gpioSleep(PI_TIME_RELATIVE, 1, 0);
        } else {
            hid->setGreenLed(1);
        }
    } else if (input_ == 2) { // Close gripper
        // Checks if allready set direction, or if motor not running (button works as "start" besides set direction).
        //(Only calls the motor once)
        if (temp_direction_ != 0 || motor_running_ != 1) {
            temp_direction_ = 0;
            ur_conn->isReady(0); // not ready when motor is running
            hid->setOpenLed(0);
            hid->setCloseLed(1);
            motor_ctrl->setDirection(temp_direction_);
            motor_running_ = 1;
        }        
        
    } else if (input_ == 3) { // Open gripper
        // Checks if allready set direction, or if motor not running (button works as "start" besides set direction).
        //(Only calls the motor once)
        if (temp_direction_ != 1 || motor_running_ != 1) {
            temp_direction_ = 1;
            ur_conn->isReady(0); // not ready when motor is running 
            hid->setOpenLed(1);
            hid->setCloseLed(0);
            motor_ctrl->setDirection(temp_direction_);
            motor_running_ = 1;
        }
        
    } else if (input_ == 4) { // Stopping the motor
            if (motor_running_) {
                hid->setCloseLed(0);
                hid->setOpenLed(0);
                motor_ctrl->stop();
                motor_running_ = 0;
            }
        
    } else if (input_ == 5) { // Stoppen the closing of gripper by gripper_switch
        if (temp_direction_ == 0) { // Checks if allready set direction. (Only calls the motor once)
            if (motor_running_) {
                hid->setCloseLed(0);
                motor_ctrl->stop();
                motor_running_ = 0;
                gpioDelay(500000); // Delays for 0,5 second before signallilng "ready"
                ur_conn->isReady(1); 
            }
        }
    }
    else {
        // Do nothing
    }
    
    //gpioSleep(PI_TIME_RELATIVE, 1, 0);
    }
    
}

void PinCtrl::standby(){ // For problems(?) and motor change and such
    in_standby_loop_ = 1;    
    ur_conn->isReady(0); // Not ready when in stadnby
    
    while (in_standby_loop_){ // Loop is not nescessary now. But might be later, so its let be for now
        
        hid->setRedLed(1);
        
        gpioSleep(PI_TIME_RELATIVE, 0, 300000); // sleep commands used for timing of led.
        // Could be controlled in seperate thread?        
        hid->setRedLed(0);
        
        //std::cout << "standby loop" << std::endl;
        if (input_ == 6) { // This changes the motor in motor_ctrl
            hid->setRedLed(1);
            hid->setOpenLed(1);
            gpioSleep(PI_TIME_RELATIVE, 1, 0);
            if (input_ == 6){
                hid->setCloseLed(1);
                gpioSleep(PI_TIME_RELATIVE, 1, 0);
                if (input_ == 6) {
                    if (motor_type_) {
                        motor_type_ = 0;
                    } else if (!motor_type_) {
                        motor_type_ = 1;
                    }
                    temp_direction_ = 0; // Solve problem with directions not working by first press of button..
                    motor_ctrl->changeMotor(motor_type_);
                    hid->setRedLed(0);
                    hid->setOpenLed(0);
                    hid->setCloseLed(0);                    
                    gpioSleep(PI_TIME_RELATIVE, 1, 0);
                    
                    hid->setGreenLed(1);
                    run_state_ = 1;
                    in_standby_loop_ = 0;
                } 
            }
            
            hid->setOpenLed(0);
            hid->setCloseLed(0);
            
        } else if (input_ == 1) { // Start working loop
            hid->setRedLed(1);
            gpioSleep(PI_TIME_RELATIVE, 1, 0);
            if (input_ == 1){
                hid->setRedLed(0);
                gpioSleep(PI_TIME_RELATIVE, 1, 0);
                hid->setGreenLed(1);
                run_state_ = 1;
                in_standby_loop_ = 0;
            }
        } else if (input_ == 7) { // Closes program
            hid->setRedLed(1);
            hid->setOpenLed(1);
            gpioSleep(PI_TIME_RELATIVE, 1, 0);
            if (input_ == 7){
                hid->setCloseLed(1);
                gpioSleep(PI_TIME_RELATIVE, 1, 0);
                if (input_ == 7) {
                    hid->setRedLed(0);
                    hid->setOpenLed(0);
                    hid->setCloseLed(0);   
                    gpioSleep(PI_TIME_RELATIVE, 1, 0);
                    
                    running_ = 0;
                    in_standby_loop_ = 0;
                } 
            }
            
            hid->setOpenLed(0);
            hid->setCloseLed(0);
            
            
        } else if (false) { // Set speed
            hid->setRedLed(0);
            bool speed_loop = 1;
            while (speed_loop) {
                if (input_ == 1){
                    hid->setGreenLed(1);                    
                    hid->setCloseLed(0);
                    hid->setOpenLed(0);
                    setMotorSpeed(1);
                    motor_ctrl->setSpeed(1);
                    gpioSleep(PI_TIME_RELATIVE, 1, 0);
                    
                } else if (input_ == 2){
                    hid->setGreenLed(0);                    
                    hid->setCloseLed(1);
                    hid->setOpenLed(0);
                    setMotorSpeed(2);
                    motor_ctrl->setSpeed(2);
                    gpioSleep(PI_TIME_RELATIVE, 1, 0);
                } else if (input_ == 3){
                    hid->setGreenLed(0);                    
                    hid->setCloseLed(0);
                    hid->setOpenLed(1);
                    setMotorSpeed(3);
                    motor_ctrl->setSpeed(3);
                    gpioSleep(PI_TIME_RELATIVE, 1, 0);
                } else if (input_ == 1){
                } else if (input_ == 0){
                    speed_loop = 0;
                }
            }
            hid->setGreenLed(0);                    
            hid->setCloseLed(0);
            hid->setOpenLed(0);
            
            
        } else {
            // Do nothing
        }
        
        gpioSleep(PI_TIME_RELATIVE, 0, 700000);
        
    }
}

void PinCtrl::setMotorType(bool& b){
    motor_type_ = b;
}

void PinCtrl::setMotorSpeed(int i){
    speed_ = i;
}

void PinCtrl::setMotorDirection(bool& b){
    direction_ = b;
}

void PinCtrl::inputScanner(){ // Scans for input from different classes AND differentiates between multiple buttons pressed etc
    scan_inputs_ = true;
    scan_freq_ = 100;
    while (scan_inputs_){
        if (hid->getOpenEnd() && hid->getCloseEnd()){ // Changing state between working and standby
            std::cout << "kill"<< std::endl;
            input_ = 1;
        } else if (hid->getCloseGrip() || ur_conn->getCloseGrip()) { //
            std::cout << "close"<< std::endl;
            input_ = 2;
        } else if (hid->getOpenGrip() || ur_conn->getOpenGrip()) { // 
            std::cout << "open"<< std::endl;
            input_ = 3;
        } else if (hid->getKillSwitch()) { // stop motor
            std::cout << "hid stop"<< std::endl;
            input_ = 4;
        } else if (motor_ctrl->getEndSwitch()) {
            std::cout << "grip stop"<< std::endl;
            input_ = 5;
        } else if (false) {
            input_ = 6;
        } else if (false) {
            input_ = 7;
        } else if (ur_conn->getCloseGrip()) {
            std::cout << "ur_close"<< std::endl;
            input_ = 8;
        } else if (ur_conn->getOpenGrip()) {
            std::cout << "ur_open"<< std::endl;
            input_ = 9;
        } else if (false) {
            input_ = 10;
        } else {
            input_ = 0;
        }
        
        gpioSleep(PI_TIME_RELATIVE, 0, (1000000/scan_freq_)); // gpioSleep, takes uS as parameter
    }
}
