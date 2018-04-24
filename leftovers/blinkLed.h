#ifndef BLINK_LED_H
#define BLINK_LED_H

#include <pigpio.h> // Library used to connect to the gpios

class BlinkLed {
private:
    
    void blinkLed(int, int, int); // Blink led
                                 // 1. int determines led (1 for bi-led)
                                 // 2. int is rate (see below), 3. is duration in ms.
    
    // The rate of blinking is set as:
    // 0: slow blink (500ms between shifts)
    // 1: fast blink (250ms between shifts)
    
    bool run_standby_blink_;
    void standbyBlink(bool); // bool: 1=start 0=stop
    
    
    void blinkBiLed(int, int); // Blinks between green and red led.
                               // 1. int is rate (see above), 2. int is duration in s
    void blinkBlueLed(int, int); // Blinks blue led
                               // 1. int is rate (see above), 2. int is duration in s
    
    
    
public:
    Pin_step(); // Simple constructor. Nothing happens
    
    Pin_step(bool direction, int speed); // Constructiong and setting the speed and direction at once
        // Speed is sat by value from 0-255
        
    void setSpeed(int); // Stets the speed for the motor by value from 0-255
    int getSpeed(); // Stets the speed for the motor by value from 0-255
    void setDirection(bool); // Sets the direction of the motor
    bool getDirection(); // Sets the direction of the motor
    
private:
    void _runStepper(int, bool); // Should run in a loop ina seperate thread
                        // so its possible to change speed and such
    void _set_step(int&);
    void _stepTraverse();
    void _loopCase();
};
                           // True = on, false = off
    int rate_balance_; // Used to tune the rate of the blinking of the LEDs
    
    bool standbyBlinkStop_;


void Hid::blinkLed(int led, int rate, int duration){
    if (led == 1) {
        std::thread (&Hid::blinkBiLed, this, rate, duration).detach();
    } else if (led == 2) {
        std::thread (&Hid::blinkBlueLed, this, rate, duration).detach();
    } else {
        // Do nothing
    }
}

void Hid::blinkBlueLed(int rate, int duration){
    int balance = (rate+1)*250;
    int iterations = duration*1000/balance;
    for (int i = 0; i < iterations ; i++){
        Hid::setOpenLed(1);
        gpioSleep(PI_TIME_RELATIVE, 0, balance*1000);
        Hid::setOpenLed(0);
        gpioSleep(PI_TIME_RELATIVE, 0, balance*1000);
    }
}

void Hid::standbyBlink(bool b){
        run_standby_blink_ = 1;
        std::thread standbyThread(&Hid::blinkBiLed, this, 1, 5);
    if (b){
        standbyThread.join();
    } else {
        // Do nothing
    }
}    

void Hid::blinkBiLed(int rate, int duration){
    int balance = (rate+1)*250;
    int iterations = duration*1000/balance;
    for (int i = 0; i < iterations ; i++){
        Hid::setGreenLed(1);
        gpioSleep(PI_TIME_RELATIVE, 0, balance*1000);
        Hid::setRedLed(1);
        gpioSleep(PI_TIME_RELATIVE, 0, balance*1000);
    }
}

#endif // BLINK_LED_H
