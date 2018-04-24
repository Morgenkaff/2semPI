// Built in libs
#include <iostream>
#include <thread>

// Included classes
#include "pin_ctrl.h"

// Should be omitted when finished
#include <pigpio.h>
#include "motor_ctrl.h"

using namespace std;
int main()
{
    cout << "Hello World!" << endl;
    
    
    bool motor_type = 0;
    bool motor_dir = 0;
    int motor_speed = 5;
    
    
    PinCtrl pin_ctrl;
    
    pin_ctrl.setMotorType(motor_type);
    pin_ctrl.setMotorSpeed(motor_speed);
    pin_ctrl.setMotorDirection(motor_dir);
    
    
    bool ready = pin_ctrl.init();
    
    if (ready) {
        cout << "GPIOs initialized! " << endl;
    } else {
        cout << "Error in initializing GPIOs" << endl;
    }
    pin_ctrl.run(2);
    
    
    return 0;
    
}
