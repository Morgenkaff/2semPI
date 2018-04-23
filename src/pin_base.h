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

// HID/BOX IOs
#define KILL_SW 14 // The red switch on front
#define GREEN_LED 6 // Green bi-led
#define RED_LED 13 // Red bi-led
#define IS_OPENING 19 // Yellow LED on front
#define IS_CLOSING 26 // Blue LED on front
#define HID_CLOSED_END 2 // HID version of CLOSED_END in KLO IO
#define HID_OPEN_END 3 // HID version of CLOSED_END in KLO IO
#define HID_CLOSE_KLO 17 // HID version of CLOSE_KLO in UR IO
#define HID_OPEN_KLO 27 // HID version of OPEN_KLO in UR IO

// UR IOs
#define OPEN_KLO 23 // Signal from UR to open the gripper (hardwaired to left white button on front)
#define CLOSE_KLO 24 // Signal from UR to open the gripper (hardwaired to left white button on front)
#define KLO_READY 25 // The connectiuon used to send "ready-signalk" to UR

// KLO IO
#define CLOSED_END 15 // This input gets HIGH when the "closed-switch" is pressed
#define OPEN_END 18 // This input gets HIGH when the "open-switch" is pressed
#define DC_CLOCKWISE 8 // The signal to turn the dc motor clockwise
#define DC_C_CLOCKWISE 7 // The signal to turn the dc motor counter clockwise
#define STEP_1 12 // 1 of 4 pins to control stepper motor
#define STEP_2 16 // 2 of 4 pins to control stepper motor
#define STEP_3 20 // 3 of 4 pins to control stepper motor
#define STEP_4 21 // 4 of 4 pins to control stepper motor

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
