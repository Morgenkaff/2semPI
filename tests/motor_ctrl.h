#ifndef MOTOR_CTRL_H
#define MOTOR_CTRL_H

#include "motor.h"

class MotorCtrl {
    
    Motor* dc;
    Motor* step;
    
public:
    
    MotorCtrl();
    
    void sayHello(bool); // 1 should be dc, 0 should be step
    
    void hello(Motor*);
};

#endif
