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

#define GRN 2
#define ORG 3
#define YEL 17
#define BLU 27


/*
*  Defining the different kinds of output, eg.: HIGH, LOW
* Could be used for different levels of dutycycles for pwm etc.
*/

#define HIGH 1
#define LOW 0

/*
*  Different vars as value-holders:
*/

int pwm_step;
int blue_led_on;

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

	cout << "Hello v2" << endl;

/*
*  This tests if it is possible to initialise the GPIO library
*/

	if (gpioInitialise() < 0) exit(1);

/*
*  Now setting the in- and outputs used in the code
*/

	gpioSetMode(YEL, PI_OUTPUT); // Sets pin17 as output (3.3v), for blinking LED
	gpioSetMode(GRN, PI_OUTPUT); // pin3 will be used for PWM-tests
	gpioSetMode(ORG, PI_INPUT); // pin4 has a button for input-tests
	gpioSetMode(BLU, PI_OUTPUT); // pin 27 will be output feedback for the input-tests

/*
*  This loop should run 10 times.
*/

	for(int i; i < 10; i++){

/*
*  First a counter for traverse-nr of loop:
*/

		cout << "Loop-count: " << i +1 << endl;

/*
*  This part should set the yellow wire (YEL) as HIGH, wait half a second (500000 uS),
*  set the yellow wire as LOW, wait half a second again.
*  That will be used as a "headless" feedback, for when the loop is running.
*/


		gpioWrite(GRN, HIGH);
		gpioDelay(500000);
		gpioWrite(GRN, LOW);
		gpioDelay(500000);

/*
*  This part of the loop will read the input of the orange wire, set the var blue_led_on to 1 if
*  the button is pressed and 0 if not. Then set the pgioWrite accordingly.
*  Input will be high (1) as default. So input is low (0) when button is pressed.
*  It toggles between keeping the values if button is not pressed.
*/

		cout << "GPIO on orange wire is: " << gpioRead(ORG) << endl;

		if (blue_led_on == 0 & gpioRead(ORG) == 0){

			blue_led_on = 1;

		} else if (blue_led_on == 1 & gpioRead(ORG) == 0) {

			blue_led_on = 0;

		} else {

			//Do nothing

		}

		cout << "blue_led_on is: " << blue_led_on << endl;
		gpioWrite(BLU, blue_led_on);

/*
*  This part of the loop will "pulse" the output on the yellow wire via PWM.
*  The output defaults to 0-255 as range for the PWM duty cycle. The loop "loops" 10 times, so
*  the range will be divided in 10 steps traversing from 0 to 250 and back again. We can
*  live without the last 5 values for the range.
*/

		if (i < 5){

			pwm_step = 0 + i * 50; // calculates and sets the dutyc. value for the PWM

		} else if (i > 4) {

			pwm_step = 250 - (i-4) * 50;

		}

// clutter turned of
//		cout << "The value for the dutycaycle is: " << pwm_step << endl;

		gpioPWM(YEL, pwm_step);


	} // End of 10s-loop


/*
*  At last a termination of the GPIOs again.
*/

	gpioTerminate();

}

