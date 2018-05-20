// Build with:

//  g++ src/*.cc -lpigpio -lrt -lpthread -o grip-control

// Built in libs
#include <fstream>
#include <iostream>
#include <string>

// Included classes
#include "pin_ctrl.h"
#include "logger.h" // Class used to write logs
#include "timer.h"  // Used to log runtime of program

//using namespace std;

bool readSettings(); // Function to read basic settings from file

bool default_motor_;
int default_motor_speed_;
bool halt_after_stop_;

int main()
{    
    
    Logger* log = new Logger('b', "grip-control.log");
    Timer* timer = new Timer();
    
    timer->start();
    log->write("Grip-control started.");
    
    
    //bool settings_read = readSettings();
    
    if (!readSettings()){
        
        log->write("Unable to read settings file");
        
        // If values could not be read, they are sat to 0
        bool default_motor_ = 1; // 1 = stepper, 0 = dc
        int default_motor_speed_ = 2; // 1 fast, 2 medium, 3 slow
        log->write("Motor type sat to: stepper");
        log->write("Motor speed sat to: 2");
    } else {
        
        log->write("Settings read from settings file.");
        if (default_motor_ == 1){
            log->write("Motor type sat to: stepper");
        } else if (default_motor_ == 0){
            log->write("Motor type sat to: dc");
        }
        log->write(("Motor speed sat to: "+std::to_string(default_motor_speed_)));
    }
    
    // Constructing the class controlling the GPIOs
    PinCtrl* pin_ctrl = new PinCtrl;
    
    // These function calls should be defined and controllod in conjunction with OPC in future
    pin_ctrl->setMotorType(default_motor_);
    pin_ctrl->setMotorSpeed(default_motor_speed_);
    
    // Initializing pin_ctrl and stores "success" in bool
    bool ready = pin_ctrl->init();
    
    if (!ready) {
        
        log->write("Unable to initialize pigpio library.");
        
        exit(1);
    }
    
    log->write("Pigpio library initialized.");
    
    
    pin_ctrl->run(1); // 1 is working loop, 2 is standby
    
    delete pin_ctrl;
    log->write("Pigpio have been terminated.");
    int time = timer->stop();
    log->write("Runtime of grip-control: "+std::to_string((time/60)/60)+":"+std::to_string(time/60)+":"+std::to_string(time));
    
    if (halt_after_stop_){
        log->write("Systems going to halt.");
        system("sudo halt");
    }
    
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
                
                if (line.at(7) == '0'){
                    default_motor_ = 0;
                } else {
                    default_motor_ = 1; // Sets to stepper, if no setting is made (or is 1)
                }
                
            } else if (line.substr(0,5).compare("speed") == 0) {
                if ((0 < (line.at(8) - 48) && (line.at(8) - 48) < 4)) {
                    default_motor_speed_ = (line.at(8) - 48);
                }
            } else if (line.substr(0,4).compare("halt") == 0) {
                
                if (line.at(7) == '1'){
                    halt_after_stop_ = 1;
                } else {
                    halt_after_stop_ = 0; // Sets to 0 (no halt), if no setting is made (or setting is 0)
                }
                
            }
            
        }
        
        settings.close();
        
        return 1;
        
    } else {
        
        return 0;
        
    }
    
}
