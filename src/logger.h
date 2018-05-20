/*
 * Prints string given as parameter or saves it to a file,
 * depending on given parameter:
 * 
 * log(*print (p), file (f) or both (b) : char, *String to log* : string);
 * 
 */

#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>

class Logger {
public:
    
    Logger();
    
    bool log(char, std::string); // char: 'p'rint, 'f'ile, 'b'oth. 
                            // string: string to print
    
    //Vars used for logging of motor
    int total_opens_; // Amount of times the open command have been called
    int total_closes_; // Amount of times the close command have been called
    
private:
    
    static std::string timeAsString(); // Used to print the time of logging
    bool printToFile(std::string); // Prints given string to file in same folder as program (log)
    
};

#endif
