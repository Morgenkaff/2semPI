#include <iostream>
#include "pin_base.h"
#include "pin_dc.h"

using namespace std;

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
    
    pin_dc.setSpeed(150);
    
    while (!pin_base.getSw(3)){
        //cout << "Running." << endl;
        if (pin_dc.getDirection() == 0 && pin_base.getSw(1)){
            pin_dc.setSpeed(0);
            pin_dc.setDirection(1);
        } else if (pin_dc.getDirection() == 1 && pin_base.getSw(2)){
            pin_dc.setSpeed(0);
            pin_dc.setDirection(0);
        } else if (pin_dc.getSpeed() == 0){
            
            char c;
            cin >> c;
            
            if (c=='y'){
                pin_dc.setSpeed(150);
            } else {
                // do nothing
            }
        }
        //gpioDelay(500);
    }
    
    pin_base.term();
    
    cout << "Stopped." << endl;
    
    
    return 0;
    
}
