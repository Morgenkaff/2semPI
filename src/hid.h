#ifndef HID_H
#define HID_H

#include <pigpio.h> // Library used to connect to the gpios

class Hid {
private: // Private vars
    
// Ints setting the pins used for easier reading:
    
    // Inputs:
    int kill_sw_; // The red switch on front
    int open_grip_; // Right white switch. Starts the motor in "opening direction"
    int close_grip_; // Left white switch. Starts the motor in "closing direction"
    
    // Buttons on the side of the box. Used for controlls as switching to standby mode,
    // changing motor type, speed etc.
    int top_side_; // Upper button on the left side
    int bottom_side_; // Lower button on the left side
    
    // Outputs:
    int green_led_; // Green bi-led
    int red_led_; // Red bi-led
    int blue_led_; // Blue LED on front
    int yellow_led_; // Yellow LED on front
        
public: // Public functions (+constructor)
    Hid(); // The constructor declares names for the pins used and indicates "ready" (green led).
    ~Hid(); // Destructor should turn off leds and switches
    
    
    // Setting the LEDs:
    void setGreenLed(bool); //Sets led. 1 = on, 0 = off
    void setRedLed(bool); //As above
    void setOpenLed(bool); //As above
    void setCloseLed(bool); //As above
    
    // Getting the inputs from the switches
    bool getKillSwitch(); // Returns the state of the kill switch (red on front).
                          // If pressed = 1, if not pressed = 0
    bool getOpenGrip(); // Returns the state of the switch to open the gripper. (Right white on front.)
                        // If pressed = 1, if not pressed = 0
    bool getCloseGrip(); // Returns the state of the switch to close the gripper. (Left white on front.)
                         // If pressed = 1, if not pressed = 0
    bool getTopSide(); // Returns the state of the lower switch on top left side.
                       // If pressed = 1, if not pressed = 0
    bool getBottomSide(); // Returns the state of the upper switch on top left side.
                          // If pressed = 1, if not pressed = 0
    
    // FUNCTION WISH LIST:
    
    
    
private: // Private functions
};

#endif // HID_H
