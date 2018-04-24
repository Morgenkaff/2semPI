#include "motor_ctrl.h"
#include "dc.h"
#include "stepper.h"

MotorCtrl::MotorCtrl(){
    dc = new Dc();
    step = new Stepper();
}

void MotorCtrl::sayHello(bool m){
    if (m){
        hello(dc);
    } else if (!m) {
        hello(step);
    }
}

void MotorCtrl::hello(Motor* m){
    m->hello();
}
