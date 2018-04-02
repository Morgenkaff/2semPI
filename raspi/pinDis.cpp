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
 *    Green is connected to pin2
 *    Orange is connected to pin3
 *    White is connected to pin4
 *    Yellow is conneced to pin17
 *    Blue is connected to pin27
 *    Red is connected to pin22
 */

#define GRN 2
#define ORG 3
#define WHT 4
#define YEL 17
#define BLU 27
#define RED 22

/*
 *  Defining the different kinds of output, eg.: HIGH, LOW
 * Could be used for different levels of dutycycles for pwm etc.
 */

#define HIGH 1
#define LOW 0

/*
 *  Different vars as value-holders:
 */


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
    
    cout << "Press return to turn off all GPIOs." << endl;
    cin.get();
    
    
    /*
     *  This tests if it is possible to initialise the GPIO library
     */
    
    if (gpioInitialise() < 0) exit(1);
    
    /*
     *  Now setting the in- and outputs used in the code
     */
    
    gpioSetMode(GRN, PI_OUTPUT); // pin2 yellow diode (blinky)
    gpioSetMode(ORG, PI_OUTPUT); // pin3 red diode (PWM)
    gpioSetMode(WHT, PI_OUTPUT); // pin4 blue diode (button diode)
    gpioSetMode(YEL, PI_INPUT); // pin17 physical switch (toggle)
    gpioSetMode(BLU, PI_INPUT); // pin27 blue "wire-switch" (test_mode control)
    gpioSetMode(RED, PI_INPUT); // pin22 red "wire-switch" (kill switch)
    
    gpioWrite(GRN, LOW);
    gpioWrite(ORG, LOW);
    gpioWrite(WHT, LOW);
    
    /*
     * Setting the inputs to HIGH as to "reset" them
     */
    
    gpioWrite(YEL, HIGH);
    gpioWrite(BLU, HIGH);
    gpioWrite(RED, HIGH);
    
    /*
     * And lastly terminating pigpio again
     */
    
    gpioTerminate();
    
}

