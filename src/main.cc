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
    
    
    // These vars should be defined and controllod in conjunction with OPC in future
    bool motor_type = 0;
    bool motor_dir = 0;
    int motor_speed = 3;
    
    
    PinCtrl* pin_ctrl = new PinCtrl;
    
    // These function calls should be defined and controllod in conjunction with OPC in future
    pin_ctrl->setMotorType(motor_type);
    pin_ctrl->setMotorSpeed(motor_speed);
    pin_ctrl->setMotorDirection(motor_dir);
    
    bool ready = pin_ctrl->init();
    
    if (!ready) {
        cout << "Error in initializing GPIOs" << endl;
        exit(1);
    }
        
    pin_ctrl->run(2);
    
    cout << "pin_ctrl->run finised" << endl;
    
    delete pin_ctrl;
    
    cout << "pin_ctrl deleted" << endl;
    
    system("sudo shutdown -P now");
    
    return 0;
    
}