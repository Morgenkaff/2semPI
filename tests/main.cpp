// Biult in libs
#include <iostream>
#include <thread>

#include "motor_ctrl.h"

using namespace std;

int main()
{
    
    MotorCtrl* motor_ctrl = new MotorCtrl();    
    
    motor_ctrl->sayHello(1);
    
    return 0;
    
} 
