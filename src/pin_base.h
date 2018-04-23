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
 * ___________________________________
 *        PINS ON HARDWARE:
 * 
 *                 _____
 *            3.3v|-- --|--
 *    open_end_hid| 2 --|--
 *  closed_end_hid| 3 --|GND
 *         kill_sw| 4 14|--
 *             GND|-- 15|--
 * closed_grip_hid|17 18|--
 *   open_grip_hid|27 --|--
 *     open_end_sw|22 23|green_led
 *            3.3v|-- 24|red_led
 *   closed_end_sw|10 --|GND
 *   close_grip_ur| 9 25|blue_led
 *    open_grip_ur|11  8|yellow_led
 *             GND|--  7|--
 *              --|-- --|--
 *          step_4| 5 --|GND
 *          step_3| 6 12|--
 *          step_2|13 --|GND
 *          step_1|19 16|--
 *   grip_ready_ur|26 20|--
 *             GND|-- 21|--
 *                 ¯¯¯¯¯
 * 
 * (Chars '--' indicates pin is not used/connected on hardware.)
 * 
 */

// HID/BOX IOs
#define KILL_SW 4 // The red switch on front
#define GREEN_LED 23 // Green bi-led
#define RED_LED 24 // Red bi-led
#define IS_OPENING 25 // Blue LED on front
#define IS_CLOSING 8 // Yellow LED on front
#define OPEN_END_HID 2 // HID version of CLOSED_END in KLO IO
#define CLOSE_END_HID 3 // HID version of CLOSED_END in KLO IO
#define OPEN_GRIP_HID 17 // HID version of CLOSE_KLO in UR IO
#define CLOSE_GRIP_HID 27 // HID version of OPEN_KLO in UR IO

// UR IOs
#define OPEN_GRIP_UR 23 // Signal from UR to open the gripper (hardwaired to left white button on front)
#define CLOSE_GRIP_UR 24 // Signal from UR to open the gripper (hardwaired to left white button on front)
#define GRIP_READY_UR 25 // The connectiuon used to send "ready-signalk" to UR

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
