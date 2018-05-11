// Built in libs
#include <iostream>
#include <thread>

// Included classes
#include "pin_ctrl.h"

// Should be omitted when finished
#include <pigpio.h>
//#include "motor_ctrl.h"

using namespace std;
int main()
{
    cout << "PiGrip!" << endl;
    
private:
    // These vars should be defined and controllod in conjunction with OPC in future
    bool default_motor_ = 1;
    bool default_motor_dir_ = 0;
    int default_motor_speed_ = 1; // 1 fast, 2 medium, 3 slow
    
    // Constructing the class controlling the GPIOs
    PinCtrl* pin_ctrl = new PinCtrl;
    
    // These function calls should be defined and controllod in conjunction with OPC in future
    pin_ctrl->setMotorType(default_motor_);
    pin_ctrl->setMotorSpeed(default_motor_speed_);
    pin_ctrl->setMotorDirection(default_motor_dir_);
    
    bool ready = pin_ctrl->init();
    
    if (!ready) {
        cout << "Error in initializing GPIOs" << endl;
        exit(1);
    }
        
    pin_ctrl->run(1); // 1 is working loop, 2 is standby
    
    cout << "pin_ctrl->run finised" << endl;
    
    delete pin_ctrl;
    
    cout << "pin_ctrl deleted" << endl;
    
    //system("sudo halt");
    
    return 0;
    
}
