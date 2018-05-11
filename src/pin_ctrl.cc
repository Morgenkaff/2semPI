/*
 * Class used to control the GPIO and belonging classes.
 */

#include <pigpio.h> // Library used to connect to the gpios
#include <thread> // Used to run hid in seperate thread.
#include <iostream> // For debuggin

#include "pin_ctrl.h" // Own header file

PinCtrl::PinCtrl(){
}

PinCtrl::~PinCtrl(){
    //gpioTerminate();
    terminate();        
    //     std::cout << "GPIOs terminated" << std::endl;
}

bool PinCtrl::init(){
    
    bool ready = gpioInitialise() >= 0; // Checks if pigpio is started correctly
    
    if (ready){
        
        hid = new Hid; // Constructing the HID class
        
        ur_conn = new UrConn; // Constructing the UrConn class
        
        motor_ctrl = new MotorCtrl(motor_type_); // Constructing the motor control class 
        
        input_scan_thread = new std::thread(&PinCtrl::inputScanner,this);
        
        
        return 1;
        
    } else {
        return 0;
    }
}

bool PinCtrl::terminate(){
    scan_inputs_ = 0; // Stops the inputScanThread while loop scanning for inputs
    input_scan_thread->join();;
    
    delete motor_ctrl;
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
                
                //              std::cout << "working"<< std::endl;                
                working();
                break;
                
            case 2:
                
                //              std::cout << "standby"<< std::endl;
                standby();
                break;
                
                
        }
        
    }
    
}

void PinCtrl::working(){ //When motor is set and all
    
    in_working_loop_ = 1;
    hid->setGreenLed(1); // Indicates ready on HID
    ur_conn->isReady(1); // Signals to UR that it is ready
    
    while (in_working_loop_){
        
        if (input_ == 1) { // "Standby signal"
            hid->setRedLed(1);
            gpioSleep(PI_TIME_RELATIVE, 3, 0);
            if (input_ == 1){
                motor_ctrl->stop();
                hid->setRedLed(0);
                hid->setCloseLed(0);
                hid->setOpenLed(0);
                run_state_ = 2;
                in_working_loop_ = 0;
                gpioSleep(PI_TIME_RELATIVE, 1, 0);
            } else {
                hid->setGreenLed(1);
            }
        } else if (input_ == 2) { // Close gripper (direction = 0)
            
            // Checks if other direction set or motor not running
            // Button works as "start" besides set/change direction.
            // And should only call the motor once.
            if (direction_ != 0 || !motor_ctrl->isRunning()) {
                direction_ = 0;
                ur_conn->isReady(0); // not ready when motor is running
                hid->setOpenLed(0);
                hid->setCloseLed(1);
                motor_ctrl->stop();
                motor_ctrl->start(speed_, direction_);
            }        
            
        } else if (input_ == 3) { // Open empty gripper (direction = 1)
            
            // Opening the gripper can be done in 2 ways:
            // 1 If the gripper holds an object, to release it.
            // 2 If the gripper doesn't hold an object, to open fully.
            // Nr 2 is done here, nr 1 is next if-statement
            
            // Checks if other direction set or motor not running
            // Button works as "start" besides set/change direction.
            // And should only call the motor once.
            if (direction_ != 1 || !motor_ctrl->isRunning()) {
                direction_ = 1;
                ur_conn->isReady(0); // not ready when motor is running 
                hid->setOpenLed(1);
                hid->setCloseLed(0);
                motor_ctrl->stop();
                motor_ctrl->start(speed_, direction_);
            }
            
            
        } else if (input_ == 6){
            
            // This if-statement reacts to the gripper is holding an object and set to open.
            // Its starting openening the gripper. Running a while loop until the switch on gripper 
            // is not pressed any longer, short delay and stops the motor
            direction_ = 1;
            ur_conn->isReady(0); // not ready when motor is running 
            hid->setOpenLed(1);
            hid->setCloseLed(0);
            motor_ctrl->stop();
            motor_ctrl->start(speed_, direction_);
            
            do {
                gpioSleep(PI_TIME_RELATIVE, 2, 0);
            } while (input_ == 5 || input_ == 6);
            
            motor_ctrl->stop();
            hid->setOpenLed(0);
            
            
        } else if (input_ == 4) { // Stopping the motor
            if (motor_ctrl->isRunning()) {
                hid->setCloseLed(0);
                hid->setOpenLed(0);
                motor_ctrl->stop();
            }
            
        } else if (input_ == 5) { // Stops the closing of gripper by gripper_switch
                if (direction_ == 0 && motor_ctrl->isRunning()) { // Only send the stop command if closing
                    hid->setCloseLed(0);
                    motor_ctrl->stop();
                    gpioDelay(500000); // Delays for 0,5 second before signallilng "ready"
                    ur_conn->isReady(1); 
                }
        } else if (input_ == 8) { // Stops the opening of gripper by gripper_switch
                if (direction_ == 1 && motor_ctrl->isRunning()) { // Only send the stop command if opening
                    hid->setOpenLed(0);
                    motor_ctrl->stop();
                    gpioDelay(500000); // Delays for 0,5 second before signallilng "ready"
                    ur_conn->isReady(1); 
                }
        } else {
            // Do nothing
        }
        
        //gpioSleep(PI_TIME_RELATIVE, 1, 0); // Slowing loop down for debuggin
    }
    
}

void PinCtrl::standby(){ // For problems(?) and motor change and such
    in_standby_loop_ = 1;    
    ur_conn->isReady(0); // Not ready when in standby
    
    while (in_standby_loop_){ // Loop only nescesary for not sett ur_conn->isReady constantly
        
        hid->setRedLed(1);
        
        gpioSleep(PI_TIME_RELATIVE, 0, 300000); // sleep commands used for timing of led.
        // Could be controlled in seperate thread?        
        hid->setRedLed(0);
        
        //std::cout << "standby loop" << std::endl;
        
        if (input_ == 1) { // Start working loop
            hid->setRedLed(1);
            gpioSleep(PI_TIME_RELATIVE, 1, 0); // Waits for a second, to prevent premature starts
            if (input_ == 1){
                hid->setRedLed(0);
                gpioSleep(PI_TIME_RELATIVE, 1, 0); // as last sleep
                hid->setGreenLed(1);
                run_state_ = 1; // Changes state to the state with running loop
                in_standby_loop_ = 0; // 
            }
            
        } else if (input_ == 4) { // Set speed
            hid->setRedLed(1);
            gpioSleep(PI_TIME_RELATIVE, 1, 0); // Delays the loop a bit (1s)
            // Giving time to release switch
            hid->setRedLed(0);
            gpioSleep(PI_TIME_RELATIVE, 0, 500000); // Delays the loop a bit (1s)
            // Giving time to release switch
            
            bool setSpeed = true;
            while (setSpeed){
                
                // First sets the led after wich speed is currently set
                if (speed_ == 1){
                    hid->setCloseLed(1);
                    hid->setOpenLed(0);
                } else if(speed_ == 2){
                    hid->setCloseLed(1);
                    hid->setOpenLed(1);
                } else if (speed_ == 3) {
                    hid->setCloseLed(0);
                    hid->setOpenLed(1);
                }
                
                // Waits a bit, giving time to release switch before input based reaction
                gpioSleep(PI_TIME_RELATIVE, 0, 200000); 
                
                // Next react based on input
                if (input_ == 2){ // Left white swicht decreases speed by 1
                    if (speed_>1){
                        --speed_;
                        //                         std::cout << speed_ << std::endl;
                    }
                } else if (input_ == 3){ // Right white swicht increases speed by 1
                    if (speed_<3){
                        ++speed_;
                        //                         std::cout << speed_ << std::endl;
                    }
                } else if (input_ == 4){
                    gpioSleep(PI_TIME_RELATIVE, 1, 0); // Waits for 1s, to prevent premature quits
                    
                    hid->setCloseLed(0);
                    hid->setOpenLed(0);
                    hid->setRedLed(1);
                    
                    gpioSleep(PI_TIME_RELATIVE, 1, 0); // Waits for 0,5s more, giving time to react  
                    
                    if (input_ == 4){
                        setSpeed = false;
                        
                        hid->setRedLed(0);
                        
                        gpioSleep(PI_TIME_RELATIVE, 1, 0);  // Waits for second, 
                        // Time to release switch  
                    }
                    
                    hid->setRedLed(0);
                    
                }
                
            } // setSpeed while loop
            
        } else if (input_ == 9) { // Motor change
            hid->setRedLed(1);
            hid->setOpenLed(1);
            gpioSleep(PI_TIME_RELATIVE, 1, 0); // Waits for a second, to prevent unintended motor change
            if (input_ == 9){
                hid->setCloseLed(1);
                gpioSleep(PI_TIME_RELATIVE, 1, 0); // Waits for a second more
                if (input_ == 9) {
                    
                    motor_type_ = !motor_type_; // motor_type is bool (only two motors)
                    
                    motor_ctrl->changeMotor(motor_type_);
                    
                    hid->setRedLed(0);
                    hid->setOpenLed(0);
                    hid->setCloseLed(0);                    
                    
                    gpioSleep(PI_TIME_RELATIVE, 1, 0); // Waits for 1s, give time to release switch
                    
                    // Returning to working loop (run state 1)          
                    run_state_ = 1;
                    in_standby_loop_ = 0;
                } 
            }
            
            hid->setOpenLed(0);
            hid->setCloseLed(0);
            
        } else if (input_ == 10) { // Closes program
            hid->setRedLed(1);
            hid->setOpenLed(1);
            gpioSleep(PI_TIME_RELATIVE, 1, 0); // Waits for a second, to prevent unintended quit
            if (input_ == 10){
                hid->setCloseLed(1);
                gpioSleep(PI_TIME_RELATIVE, 1, 0); // Waits for a second more
                if (input_ == 10) {
                    hid->setRedLed(0);
                    hid->setOpenLed(0);
                    hid->setCloseLed(0);   
                    gpioSleep(PI_TIME_RELATIVE, 1, 0);
                    
                    
                    // Exits running loop entirely
                    running_ = 0;
                    in_standby_loop_ = 0;
                } 
            }
            
            hid->setOpenLed(0);
            hid->setCloseLed(0);
            
            
        } else {
            // Do nothing
        }
        
        gpioSleep(PI_TIME_RELATIVE, 0, 700000);
        
    }
}

void PinCtrl::setMotorType(bool& type){ //
    motor_type_ = type;
}

void PinCtrl::setMotorSpeed(int speed){
    speed_ = speed;
}

void PinCtrl::setMotorDirection(bool& direction){
    direction_ = direction;
}
// Scans for input from different classes AND differentiates between multiple buttons pressed etc
// Going to get pretty messy. Clean up when inputs needed ios sorted out
// (Highest amount of simultanious buttons first, and highest priority (grip_sw))
void PinCtrl::inputScanner(){
    scan_inputs_ = true;
    while (scan_inputs_){
        if ((hid->getCloseGrip() && hid->getOpenGrip()) && (hid->getBottomSide() && hid->getTopSide())) {
            //                         std::cout << "aux 1"<< std::endl;
            input_ = 7;
        } else if ((hid->getBottomSide() && (hid->getCloseGrip() && hid->getOpenGrip()))) {
            //             std::cout << "close program"<< std::endl;
            input_ = 10;
        } else if (hid->getCloseGrip() && hid->getOpenGrip()) {
            //             std::cout << "change motor"<< std::endl;
            input_ = 9;
        } else if (hid->getTopSide() && hid->getBottomSide()){ 
            // Changing state between working and standby
            //                         std::cout << "Standby switch"<< std::endl;
            input_ = 1;
        } else if ((hid->getOpenGrip() || ur_conn->getOpenGrip()) && motor_ctrl->getCloseEndSwitch()) {
            // Open gripper when colsed/holding object (grip_sw pressed)
            //                         std::cout << "Grip full - opening"<< std::endl;
            input_ = 6;
        } else if ((hid->getOpenGrip() || ur_conn->getOpenGrip()) && !motor_ctrl->getOpenEndSwitch()) { 
            // Starts the motor in "opening direction" 
            //                         std::cout << "open"<< std::endl;
            input_ = 3;
        } else if ((hid->getCloseGrip() || ur_conn->getCloseGrip()) && !motor_ctrl->getCloseEndSwitch()) { 
            // Starts the motor in "closing direction"
            //                         std::cout << "close"<< std::endl;
            input_ = 2;
        } else if (hid->getKillSwitch()) { 
            // Stops motor independent of direction
            //                         std::cout << "hid stop"<< std::endl;
            input_ = 4;
        } else if (motor_ctrl->getCloseEndSwitch()) {
            // Stops motor when fully closed (empty or on object)
            //                         std::cout << "Grip stop closing"<< std::endl;
            input_ = 5;
        } else if (motor_ctrl->getOpenEndSwitch()) {
            // Stops motor when fully open
            //std::cout << "Full open"<< std::endl;
            input_ = 8;
        } else {
            input_ = 0;
        }
        
        gpioSleep(PI_TIME_RELATIVE, 0, 10000); // gpioSleep, takes uS as parameter
    }
}
