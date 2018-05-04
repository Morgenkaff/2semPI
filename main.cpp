// Built in libs
#include <iostream>
#include <thread>

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

	
	gpioSetMode(4, PI_INPUT);

	gpioSetMode(19, PI_OUTPUT);
	gpioSetMode(13, PI_OUTPUT);
gpioSetMode(5, PI_OUTPUT);
gpioSetMode(6, PI_OUTPUT);

while (gpioRead(4)){
gpioWrite(20, 1);
gpioWrite(16, 1);
gpioWrite(5, 1);
gpioWrite(6, 1);
}
}

	gpioTerminate();

    
    return 0;
    
}
