// Built in libs
#include <iostream>
#include <thread>

// g++ main.cpp -lpigpio -lrt -lpthread -o test

// Included classes
//#include "pin_ctrl.h"

// Should be omitted when finished
#include <pigpio.h>
//#include "motor_ctrl.h"

using namespace std;
int main()
{
    cout << "PiGrip!" << endl;
    
    if(gpioInitialise() >= 0){
        
        // Ins
        gpioSetMode(2, PI_INPUT);        
        gpioSetMode(3, PI_INPUT);
        gpioSetMode(4, PI_INPUT);        
        gpioSetMode(17, PI_INPUT);
        gpioSetMode(27, PI_INPUT);       
        gpioSetMode(22, PI_INPUT);       
        gpioSetMode(10, PI_INPUT);       
        gpioSetMode(9, PI_INPUT);
        
        //Leds
        gpioSetMode(14, PI_OUTPUT);        
        gpioSetMode(15, PI_OUTPUT);        
        gpioSetMode(24, PI_OUTPUT);        
        gpioSetMode(23, PI_OUTPUT);
        
        // Trans
        gpioSetMode(16, PI_OUTPUT);        
        gpioSetMode(6, PI_OUTPUT);        
        gpioSetMode(20, PI_OUTPUT);        
        gpioSetMode(21, PI_OUTPUT);
        gpioSetMode(26, PI_OUTPUT);
        
        while (true){
            
            if (!gpioRead(2)){
                gpioWrite(23, 1);
                gpioDelay(500000);
                gpioWrite(23, 0);
                gpioDelay(500000);
            } else if (!gpioRead(3)){
                gpioWrite(24, 1);
                gpioDelay(500000);
                gpioWrite(24, 0);
                gpioDelay(500000);
            } else if (!gpioRead(4)){
                gpioWrite(14, 1);
                gpioDelay(500000);
                gpioWrite(14, 0);
                gpioWrite(15, 1);
                gpioDelay(500000);
                gpioWrite(15, 0);
            } else if (!gpioRead(17)){
                gpioWrite(14, 1);
                gpioWrite(24, 1);
                gpioDelay(500000);
                gpioWrite(24, 0);
                gpioWrite(14, 0);
            } else  if (!gpioRead(27)){
                gpioWrite(15, 1);
                gpioWrite(23, 1);
                gpioDelay(500000);
                gpioWrite(23, 0);
                gpioWrite(15, 0);
            } else if (!gpioRead(22)){
                gpioWrite(24, 1);
                gpioWrite(23, 1);
                gpioDelay(500000);
                gpioWrite(23, 0);
                gpioWrite(24, 0);
                gpioDelay(500000);
            } else {
            }
                
                
                
                
        }
    }
    
    gpioTerminate();
    
    
    return 0;
    
}
