#ifndef PIN_BASE_H
#define PIN_BASE_H

/*
 *  This class is intented for control of the GPIOs of the Raspberry Pi
 * 
 *  It includes functions for initialisation and termination of the pins,
 *  definitions that sets the different pins to something more suiting
 *  for the different motors and functions used in the program for testing
 *  of the different motors. 
 */

/*
 *  Libraries:
 *  pigpio for the GPIO
 */
#include <pigpio.h>

/*
 *  First the wires:
 *
 *  ON THE HARDWARE:
 *   Red_1 is connected to +3.3vdc
 *   Black is connected to 0Vdc
 *    (Red and black is just for the electronics.)
 *   Green is connected to pin2
 *   Orange is connected to pin3
 *   White is connected to pin4
 *   Yellow is conneced to pin17
 *   Blue is connected to pin27
 *   Yellow+Black is connected to pin22
 * 
 *  Seperate stepper wires:
 *   Light blue is is connected to pin26
 *   Purple is connected to pin19
 *   Grey is connected to pin13
 *   White is connected to pin6
 *   
 */

// CONTROL IO
#define ST_LED 2 // Green wire
#define SW_OPEN 3 // Orange wire
#define SW_CLOSED 4 // White wire
#define SW_KILL 22 // Yellow+Black wire

// MOTOR IO
#define MOTOR_RUN 17 // Yellow wire
#define MOTOR_DIR 27 // Blue wire

// STEP_MOTOR IO
#define STEP_1 26 //Light blue
#define STEP_2 19 //Purple
#define STEP_3 13 //Grey
#define STEP_4 6 //White

/*
 *  Defining the different kinds of output, eg.: HIGH, LOW
 */
#define HIGH 1
#define LOW 0

class Pin_base {
// Member vars:
private: 
    bool _gpio_on;
    
// Member functions:
public:
    Pin_base();
    
    bool init(); //Init. pins - for now all used at the same time.
    
    bool term(); //"Resets" the pins and terminate the pigpio-lib
    
    void setLED(bool on); // BOOLS: True turns on, false turns of.
    
    bool getSw(int sw); // INT: SW_OPEN is 1, SW_CLOSED is 2, SW_KILL is 3.
    
};

#endif //PIN_BASE_H
