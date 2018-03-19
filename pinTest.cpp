/*
*  Program for testing c++ on the Pi and how to control the GPIOs with it.
*  The library for using GPIOs is pigpio (http://abyz.me.uk/rpi/pigpio).
*
*  To build the code, use the command:
*
*    g++ -o "name_of_output_file" "name_of_input_file".cpp -lpigpio -lrt
*
*  lpigpio includes the pigpio library and lrt is to include the library for realtime functionality
*  (required by pigpio).
*/

/*
*  Libraries:
*  iostream used for on screen feedback and debuggin
*  pigpio for the GPIO
*/
#include <iostream>
#include <pigpio.h>

//Variables and constants:
using namespace std;

/*
*  First the wires:
*
*   ON THE HARDWARE:
*    Red is connected to +5vdc
*    Black is connected to 0Vdc
*	Red and black will not (cannot?) be declared and is for now just for the electronics.
*
*    Green is connected to pin3
*    Orange is connected to pin4
*    Yellow is conneced to pin17
*    Blue is connected to pin27
*/

#define GRN 3
#define ORG 4
#define YEL 17
#define BLU 27


/*
*  Defining the different kinds of output, eg.: HIGH, LOW
*/

#define HIGH 1
#define LOW 0

/*
*  Main function:
*  For starter, a simple hello.
*  Next step will be blinky LED.
*/
int main() {

/*
*  Output of some text, to determine that something works
*  Could be used for something wore usefull
*/

	cout << "Hello" << endl;

/*
*  This tests if it is possible to initialise the GPIO library
*/

	if (gpioInitialise() < 0) exit(1);

/*
*  Now setting the in- and outputs used in the code
*/

	gpioSetMode(YEL, PI_OUTPUT); // Sets pin17 as output (3.3v)

/*
*  This loop should set the yellow wire (YEL) as HIGH, wait half a second (500000 uS),
*  set the yellow wire as LOW, wait half a second again. That should loop 10 times.
*/

	for(int i; i < 10; i++){

		gpioWrite(YEL, HIGH);
		gpioDelay(500000);
		gpioWrite(YEL, LOW);
		gpioDelay(500000);
	}

/*
*  At last a termination of the GPIOs again.
*/

	gpioTerminate();

}

