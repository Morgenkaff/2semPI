#include <pigpio.h> // Library used to connect to the gpios
#include <iostream>
//#include <thread> // For blining LEDs, indipendent from rest
#include "hid.h"

Hid::Hid(){
    
// Declaring the used pins as readable names (read docs/readme.md)
    
    // Inputs pins:
    kill_sw_ = 4;
    open_end_hid_ = 2;
    close_end_hid_ = 3;
    open_grip_hid_ = 27;
    close_grip_hid_ = 17;
    
    // Output pins:
    green_led_ = 25;
    red_led_ = 8;
    is_opening_led_ = 24;
    is_closing_led_ = 23;
    
// Pin declarations end
    
// Setting the GPIO modes for the different pins
    
    // Inputs
    gpioSetMode(kill_sw_, PI_INPUT);
    gpioSetMode(open_end_hid_, PI_INPUT);
    gpioSetMode(close_end_hid_, PI_INPUT);
    gpioSetMode(open_grip_hid_, PI_INPUT);
    gpioSetMode(close_grip_hid_, PI_INPUT);
    
    // Outputs
    gpioSetMode(green_led_, PI_OUTPUT);
    gpioSetMode(red_led_, PI_OUTPUT);
    gpioSetMode(is_opening_led_, PI_OUTPUT);
    gpioSetMode(is_closing_led_, PI_OUTPUT);
    
// Mode declarations end
    
// Setting all the default values of LEDs and switches IO (switches are pull down, why they are set to high)
    
    // Inputs
    gpioWrite(kill_sw_, 1);
    gpioWrite(open_end_hid_, 1);
    gpioWrite(close_end_hid_, 1);
    gpioWrite(open_grip_hid_, 1);
    gpioWrite(close_grip_hid_, 1);
    
    // Outputs
    gpioWrite(green_led_, 0);
    gpioWrite(red_led_, 0);
    gpioWrite(is_opening_led_, 0);
    gpioWrite(is_closing_led_, 0);
    
    std::cout << "HID init" << std::endl;
    setGreenLed(1); // Turning green led on, to indicate "ready"
    
    
}
Hid::~Hid(){
    
// Turning off the LEDs and switches (switches are "off" at high (pull down))
    
    // Inputs
    gpioWrite(kill_sw_, 1);
    gpioWrite(open_end_hid_, 1);
    gpioWrite(close_end_hid_, 1);
    gpioWrite(open_grip_hid_, 1);
    gpioWrite(close_grip_hid_, 1);
    
    // Outputs
    gpioWrite(green_led_, 0);
    gpioWrite(red_led_, 0);
    gpioWrite(is_opening_led_, 0);
    gpioWrite(is_closing_led_, 0);
    
    std::cout << "HID term" << std::endl;
    
    
}
    

void Hid::setGreenLed(bool b){
    gpioWrite(red_led_, 0); // Turns off the red led in the bi-led
    
    gpioWrite(green_led_, b);
}

void Hid::setRedLed(bool b){
    gpioWrite(green_led_, 0); // Turns off the green led in the bi-led
    
    gpioPWM(red_led_, (int)b*10); // Should change resistor instead og this ........
}

void Hid::setOpenLed(bool b){
    gpioWrite(is_opening_led_, b);
}

void Hid::setCloseLed(bool b){
    gpioWrite(is_closing_led_, b);
}


// Functions for switches:

bool Hid::getKillSwitch(){
    return !gpioRead(kill_sw_);
}

bool Hid::getOpenGrip(){
    return !gpioRead(open_grip_hid_);
}

bool Hid::getCloseGrip(){
    return !gpioRead(close_grip_hid_);
}

bool Hid::getOpenEnd(){
    return !gpioRead(open_end_hid_);
}

bool Hid::getCloseEnd(){
    return !gpioRead(close_end_hid_);
}



