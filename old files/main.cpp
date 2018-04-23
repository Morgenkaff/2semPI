#include <iostream>
#include "pin_base.h"
#include "pin_dc.h"

using namespace std;

// bool waiting();
// 
// bool run();

int main()
{
    cout << "Hello World!" << endl;
    
    Pin_base pin_base;
    
    cout << "Pin initialized: " << pin_base.init() << endl;
    
    Pin_dc pin_dc;
    
    cout << "DC motor class constructed." << endl;
    
    char c;
    cin >> c;
    
    if (c=='y'){
        pin_base.setLED(true);
    } else if (c=='n') {
        pin_base.setLED(false);
    } else {
        // do nothing
    }
    
    int motorSpeed = 250;
    
    pin_dc.setSpeed(motorSpeed);
    
    while (true){
        
        while (pin_dc.getSpeed() != 0){
            if (pin_dc.getDirection() == 0 && pin_base.getSw(1)){
                pin_dc.setSpeed(0);
                pin_dc.setDirection(1);
            } else if (pin_dc.getDirection() == 1 && pin_base.getSw(2)){  
                pin_dc.setSpeed(0);
                pin_dc.setDirection(0);
            } else if (pin_dc.getSpeed() == 0){
                
                
                //gpioDelay(500);
            }
        }
        
        while (true){
            if (pin_base.getSw(3)){
                pin_dc.setSpeed(motorSpeed);
                break;
            } else if (!pin_base.getSw(3)){
            }
            
        }
    }
    
    pin_base.term();
    
    cout << "Stopped." << endl;
    
    
    return 0;
    
}

// bool run(){
//         return true;
// }
