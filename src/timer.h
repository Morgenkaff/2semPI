/*
 * Prints string given as parameter or saves it to a file,
 * depending on given parameter:
 * 
 * log(*print (p), file (f) or both (b) : char, *String to log* : string);
 * 
 */

#ifndef TIMER_H
#define TIMER_H

#include <iostream>

class Logger {
private:
    
    //Vars used for timer
    long int total_runtime_; // Stores total run time for motor, in seconds, since program start
    long int runtime_start_time_; // Used to store seconds since epoch at motor-start
    long int runtime_stop_time_; // Used to store seconds since epoch at motor-stop
        
    
public:
    
    Timer();
    
    void start(); // Used to start the timer
    long int stop(); // Used to stop the timer, and return the duration
    
private:
    
};

#endif
