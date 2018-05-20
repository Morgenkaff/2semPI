// Built in libs
#include <fstream>
#include <string>
#include <iostream>

// Included classes
#include "pin_ctrl.h"
#include "logger.h" // Class used to write logs

using namespace std;

bool readSettings();
bool default_motor_;
int default_motor_speed_;
Logger log;

int main()
{    
    
    //Logger log; //log(*print (p), file (f) or both (b) : char, *String to log* : string);
    log.log('b', "Grip-control started.");

    
    //bool settings_read = readSettings();
        
    if (!readSettings()){
        
        log.log('b', "Unable to read settings file");
        
        // If values could not be read, they are sat to 0
        bool default_motor_ = 1; // 1 = stepper, 0 = dc
        int default_motor_speed_ = 2; // 1 fast, 2 medium, 3 slow
        log.log('b', "Motor type sat to: stepper");
        log.log('b', "Motor speed sat to: 2");
    } else {
        
        log.log('b', "Settings read from settings file.");
        if (default_motor_ == 1){
            log.log('b', "Motor type sat to: stepper");
        } else if (default_motor_ == 0){
            log.log('b', "Motor type sat to: dc");
        }
        log.log('b', ("Motor speed sat to: "+std::to_string(default_motor_speed_)));
    }
            
    // Constructing the class controlling the GPIOs
    PinCtrl* pin_ctrl = new PinCtrl;
    
    // These function calls should be defined and controllod in conjunction with OPC in future
    pin_ctrl->setMotorType(default_motor_);
    pin_ctrl->setMotorSpeed(default_motor_speed_);
    
    // Initializing pin_ctrl and stores "success" in bool
    bool ready = pin_ctrl->init();
    
    if (!ready) {
        
        log.log('b', "Unable to initialize pigpio library.");
        
        exit(1);
    } else {
        
        log.log('b', "Pigpio library initialized.");
    }
    
        
    pin_ctrl->run(1); // 1 is working loop, 2 is standby
    
    // Logging the total seconds motor have been running
    log.log('b', "Motor runtime in seconds: "+std::to_string(pin_ctrl->getMotorRuntime()));
    
    // Logging the amount of open-commands to the gripper
    log.log('b', "Amount of open commands: "+std::to_string(pin_ctrl->getMotorOpens()));
    
    // Logging the amount of close-commands to the gripper
    log.log('b', "Amount of close commands: "+std::to_string(pin_ctrl->getMotorCloses()));
    
    // Deletion of PinCtrl class
    delete pin_ctrl;        
    log.log('b', "PinCtrl class deleted.");
    
    //system("sudo halt");
    
    return 0;
    
}

bool readSettings(){
    
    std::ifstream settings;
    
    settings.open("settings");
    
    if (settings.is_open()){
        
        std::string line;
        
        while (getline(settings, line)){
            
            if (line.size() == 0){ // Skips empty lines
                //Do nothing
            } else if (line.front() == '#'){ // Skips lines with #
                //Do nothing
            } else if (line.substr(0,4).compare("type") == 0) {
                
                if (line.at(7) == '1'){
                    default_motor_ = 1;
                } else if (line.at(7) == '0'){
                    default_motor_ = 0;
                }
                
            } else if (line.substr(0,5).compare("speed") == 0) {
                if ((0 < (line.at(8) - 48) && (line.at(8) - 48) < 4)) {
                    default_motor_speed_ = (line.at(8) - 48);
                }
            }
            
        }
    
        settings.close();
        
        return 1;
    
    } else {
        
        return 0;
        
    }
    
}
