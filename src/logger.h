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
#include <string>
#include "timer.h"

class Logger {

private:
    
    char dest_; // Used to set destination for log ('p'rint (screen), 'f'ile, 'b'oth)
    std::string file_name_;
    
public:
    
    Logger(char); // If only a char is given (for print, or by error)
    
    Logger(char, std::string); // Char sets destination ('p'rint (screen), 'f'ile, 'b'oth)
                          // string sets name of log-file
    
    bool write(std::string);  // string: string to print
    
private:
    
    static std::string timeAsString(); // Used to print the time of logging
    bool printToFile(std::string); // Prints given string to file in same folder as program (log)
    
};

#endif
