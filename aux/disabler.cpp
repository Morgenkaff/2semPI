// Built in libs
#include <iostream>

// g++ disabler.cpp -lpigpio -lrt -lpthread -o disablePins

#include <pigpio.h>

using namespace std;
int main()
{
    cout << "Disabling GPIOs!" << endl;
    
    if(gpioInitialise() >= 0){
        
        // Inner row
        gpioSetMode(2, PI_INPUT);        
        gpioSetMode(3, PI_INPUT);
        gpioSetMode(4, PI_INPUT);        
        gpioSetMode(17, PI_INPUT);
        gpioSetMode(27, PI_INPUT);       
        gpioSetMode(22, PI_INPUT);       
        gpioSetMode(10, PI_INPUT);       
        gpioSetMode(9, PI_INPUT);
        gpioSetMode(11, PI_INPUT);
        gpioSetMode(5, PI_INPUT);        
        gpioSetMode(6, PI_INPUT);        
        gpioSetMode(13, PI_INPUT);        
        gpioSetMode(19, PI_INPUT);
        gpioSetMode(26, PI_INPUT);        
        
        // Outer row
        gpioSetMode(14, PI_INPUT);        
        gpioSetMode(15, PI_INPUT);        
        gpioSetMode(18, PI_INPUT);
        gpioSetMode(23, PI_INPUT);
        gpioSetMode(24, PI_INPUT);
        gpioSetMode(25, PI_INPUT);
        gpioSetMode(8, PI_INPUT);
        gpioSetMode(7, PI_INPUT);
        gpioSetMode(12, PI_INPUT);
        gpioSetMode(16, PI_INPUT);
        gpioSetMode(20, PI_INPUT);
        gpioSetMode(21, PI_INPUT);
        
        
        // Inner row
        gpioWrite(2, 0);
        gpioWrite(3, 0);
        gpioWrite(4, 0);
        gpioWrite(17, 0);
        gpioWrite(27, 0);
        gpioWrite(22, 0);
        gpioWrite(10, 0);
        gpioWrite(9, 0);
        gpioWrite(11, 0);
        gpioWrite(5, 0);
        gpioWrite(6, 0);
        gpioWrite(13, 0);
        gpioWrite(19, 0);
        gpioWrite(26, 0);
        
        // Outer row
        gpioWrite(14, 0);
        gpioWrite(15, 0);
        gpioWrite(18, 0);
        gpioWrite(23, 0);
        gpioWrite(24, 0);
        gpioWrite(25, 0);
        gpioWrite(8, 0);
        gpioWrite(7, 0);
        gpioWrite(12, 0);
        gpioWrite(16, 0);
        gpioWrite(20, 0);
        gpioWrite(21, 0);
        
        
        while (true){
        
        // Inner row
        gpioWrite(2, 0);
        gpioWrite(3, 0);
        gpioWrite(4, 0);
        gpioWrite(17, 0);
        gpioWrite(27, 0);
        gpioWrite(22, 0);
        gpioWrite(10, 0);
        gpioWrite(9, 0);
        gpioWrite(11, 0);
        gpioWrite(5, 0);
        gpioWrite(6, 0);
        gpioWrite(13, 0);
        gpioWrite(19, 0);
        gpioWrite(26, 0);
        
        // Outer row
        gpioWrite(14, 0);
        gpioWrite(15, 0);
        gpioWrite(18, 0);
        gpioWrite(23, 0);
        gpioWrite(24, 0);
        gpioWrite(25, 0);
        gpioWrite(8, 0);
        gpioWrite(7, 0);
        gpioWrite(12, 0);
        gpioWrite(16, 0);
        gpioWrite(20, 0);
        gpioWrite(21, 0);
                
        gpioSleep(PI_TIME_RELATIVE, 99360, 0);
                
        }
    }
    
    gpioTerminate();
    
    
    return 0;
    
}
