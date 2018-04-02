
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

bool running = true;
char user_input_char;
int motor_speed;
int pwm_step;
int kill_switch_control;
bool kill_switch = false;

bool good_input = false;

/*
 *  Main function:
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
    
    gpioSetMode(GRN, PI_OUTPUT); // pin2 yellow diode (blinky)
    gpioSetMode(ORG, PI_OUTPUT); // pin3 red diode (PWM)
    gpioSetMode(WHT, PI_OUTPUT); // pin4 blue diode (button diode)
    gpioSetMode(YEL, PI_INPUT); // pin17 physical switch (toggle)
    gpioSetMode(BLU, PI_INPUT); // pin27 blue "wire-switch" (test_mode control)
    gpioSetMode(RED, PI_INPUT); // pin22 red "wire-switch" (kill switch)
    
    /*
     *  This loop will "control" the program, in that sense that its looping until the "kill switch" is pressed.
     *  The loop will start with a case where it's doin nothin, until the switch at the green wire is pressed.
     *  Then another case, with the test-sequence will be used instead, until the kill switch is pressed.
     */
    
    while (running){
        
        kill_switch = false;
        
        cout << "Test of DC motor. Press Enter to continue." << endl;
        cin.get();
        
        do {
            cout << "Choose speed for motor (int between 1-5), or exit (q)" << endl;
            cin >> user_input_char;
            
            if (user_input_char == 'q') {
                kill_switch = true;
                running = false;
                break;
            }
            
            motor_speed = ((int)user_input_char)-48;
            
            if (0 < motor_speed < 6) {
                cout << "Choosen motor speed is: " << motor_speed << " is it correct? Y/N ";
                cin >> user_input_char;
                
                if (user_input_char == 'Y' || user_input_char == 'y'){
                    good_input = true;    
                    cout << "Setting motor speed to: " << motor_speed << endl;
                }
                else if (user_input_char == 'N' || user_input_char == 'n'){
                    good_input = false;
                }
                else {
                    cout << "Please choose Y(es) or (N)o" << endl;
                    good_input = false;
                }
            }
            
        } while (!good_input);
        
        // Start of pwn_loop
        
        while (!kill_switch){
            
            gpioWrite(GRN, HIGH);
            gpioPWM(ORG, ((motor_speed*50)+5) );
            
            kill_switch_control = gpioRead(RED);
            
            if (kill_switch_control == 0) {
                
                gpioPWM(ORG, 0);
                
                kill_switch = true;
                
            } else {
                
                //Do nothing
                
            }
            
        } //End of pwn_loop
            gpioDelay(500000);
            gpioWrite(GRN, LOW);
        
    }
    
    /*
     *  At last a termination of the GPIOs again.
     */
    
    gpioTerminate();
    
}

