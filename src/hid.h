#ifndef HID_H
#define HID_H

#include <pigpio.h> // Library used to connect to the gpios

class Hid {
private: // Private vars
    
// Ints setting the pins used for easier reading:
    
    // Inputs:
    int kill_sw_; // The red switch on front
    int open_end_hid_; // HID version of CLOSED_END in KLO IO
    int close_end_hid_; // HID version of CLOSED_END in KLO IO
    int open_grip_hid_; // HID version of CLOSE_KLO in UR IO
    int close_grip_hid_; // HID version of OPEN_KLO in UR IO
    
    // Outputs:
    int green_led_; // Green bi-led
    int red_led_; // Red bi-led
    int is_opening_led_; // Blue LED on front
    int is_closing_led_; // Yellow LED on front
    
    bool bi_led_state_; // Holds state (colour of bi-led): true = green, false = red
                        // Used to ensure that they are not on both at the same time.
    bool hid_grip_ends_state_; // Holds state for end-switches on box. (Used for testing.)
    
    
public: // Public functions (+constructor)
    Hid(); // Simple constructor. Nothing happens.
    ~Hid(); // Destructor should turn off leds and switches
    
    
    // Setting the LEDs:
    
    void setGreenLed(bool); //Sets led. 1 = on, 0 = off
    void setRedLed(bool); //As above
    void setOpenLed(bool); //As above
    void setCloseLed(bool); //As above
    
    bool getKillSwitch(); // Returns the state of the kill switch (red on front).
                          // If pressed = 1, if not pressed = 0
    bool getOpenGrip(); // Returns the state of the switch to open the gripper. (Right white on front.)
                        // If pressed = 1, if not pressed = 0
    bool getCloseGrip(); // Returns the state of the switch to close the gripper. (Left white on front.)
                         // If pressed = 1, if not pressed = 0
    bool getOpenEnd(); // Returns the state of the switch to simulate gripper is closed. (Bottom left side.)
                       // If pressed = 1, if not pressed = 0
    bool getCloseEnd(); // Returns the state of the switch to simulate gripper is open. (Top left side.)
                        // If pressed = 1, if not pressed = 0
    
    // FUNCTION WISH LIST:
    
    
    
private: // Private functions
};

#endif // HID_H
