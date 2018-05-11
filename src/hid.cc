#include <pigpio.h> // Library used to connect to the gpios
#include <iostream>
//#include <thread> // For blining LEDs, indipendent from rest
#include "hid.h"

Hid::Hid(){
    
// Declaring the used pins as readable names (read docs/readme.md)
    
    // Inputs pins:
    kill_sw_ = 4; // Red switch. Stops motor, independent of direction.
        
    open_grip_ = 2; // Right white switch. Starts the motor in "opening direction"
    close_grip_= 3; // Left white switch. Starts the motor in "closing direction"
    
    // Buttons on the side of the box. Used for controlls as switching to standby mode,
    // changing motor type, speed etc.
    top_side_ = 27; // Upper button on the left side
    bottom_side_ = 17; // Lower button on the left side
    
    // Output pins:
    green_led_ = 14;  // Green and red LEDs is used to indicate "ready", "standby" etc.
    red_led_ = 15;    // Green and red LEDs cannot be on simultanious. (Bi-led)
    blue_led_ = 23;   // Blue LED is used to indicate that motor is opening the gripper
    yellow_led_ = 24; // Yellow LED is used to indicate that the motor is closening the gripper
    
// Pin declarations end
    
// Setting the GPIO modes for the different pins
    
    // Inputs
    gpioSetMode(kill_sw_, PI_INPUT);
    gpioSetMode(top_side_, PI_INPUT);
    gpioSetMode(bottom_side_, PI_INPUT);
    gpioSetMode(open_grip_, PI_INPUT);
    gpioSetMode(close_grip_, PI_INPUT);
    
    // Outputs
    gpioSetMode(green_led_, PI_OUTPUT);
    gpioSetMode(red_led_, PI_OUTPUT);
    gpioSetMode(blue_led_, PI_OUTPUT);
    gpioSetMode(yellow_led_, PI_OUTPUT);
    
// Mode declarations end
    
// Setting all the default values of LEDs and switches IO (switches are pull down, why they are set to high)
    
    // Inputs (All inputs are pulled up, switches shorting to gnd)
    gpioWrite(kill_sw_, 1);
    gpioWrite(top_side_, 1);
    gpioWrite(bottom_side_, 1);
    gpioWrite(open_grip_, 1);
    gpioWrite(close_grip_, 1);
    
    // Outputs (outputs are driving LEDs. So low (led off) as standart)
    gpioWrite(green_led_, 0);
    gpioWrite(red_led_, 0);
    gpioWrite(blue_led_, 0);
    gpioWrite(yellow_led_, 0);
    
//     std::cout << "HID init" << std::endl;
    setGreenLed(1); // Turning green led on, to indicate "ready"
    
    
}
Hid::~Hid(){
    
// Turning off the LEDs and switches (switches are "off" at high (pull down))
    
    // Inputs
    gpioWrite(kill_sw_, 1);
    gpioWrite(top_side_, 1);
    gpioWrite(bottom_side_, 1);
    gpioWrite(open_grip_, 1);
    gpioWrite(close_grip_, 1);
    
    // Outputs
    gpioWrite(green_led_, 0);
    gpioWrite(red_led_, 0);
    gpioWrite(blue_led_, 0);
    gpioWrite(yellow_led_, 0);
    
//     std::cout << "HID term" << std::endl;
    
    
}
    

void Hid::setGreenLed(bool b){
    gpioWrite(red_led_, 0); // Turns off the red led in the bi-led
    
    gpioWrite(green_led_, b);
}

void Hid::setRedLed(bool b){
    gpioWrite(green_led_, 0); // Turns off the green led in the bi-led
    
    gpioPWM(red_led_, (int)b*10);   // The red LED is a bit brighter than the green, so pwm is
                                    // used insted of changing resistor. 
}

void Hid::setOpenLed(bool b){
    gpioWrite(blue_led_, b);
}

void Hid::setCloseLed(bool b){
    gpioWrite(yellow_led_, b);
}


// Functions for switches:
// All returning negative (!), beacause they are wired as pull down.
// Switch pressed gives 0 (low) on input.

bool Hid::getKillSwitch(){
    return !gpioRead(kill_sw_);
}

bool Hid::getOpenGrip(){
    return !gpioRead(open_grip_);
}

bool Hid::getCloseGrip(){
    return !gpioRead(close_grip_);
}

bool Hid::getTopSide(){
    return !gpioRead(top_side_);
}

bool Hid::getBottomSide(){
    return !gpioRead(bottom_side_);
}



