/*
 * Prints string given as parameter or saves it to a file,
 * depending on given parameter:
 * 
 * Time is based on system time
 * 
 * log(*print (p), file (f) or both (b) : char, *String to log* : string);
 * 
 */

// basic file operations
#include <iostream>
#include <ctime>
#include <fstream>
#include <sstream> 
#include <string>

#include "logger.h"

Logger::Logger(char c) {
    
    dest_ = 'p'; // If no filename is given, it is forced to screen print
    
    if (c != 'p'){
        write("No filename given, forced to screen print");
    }
    
    // Could be nicer regarding overload and chars..
    
}

Logger::Logger(char c, std::string name) {
    
    dest_ = c;
    file_name_ = name;
        
        // Reads log and deletes it if its older than 10 days
        char day[2]; // The oldes date is the first two chars in file
        std::ifstream old_log(file_name_); // Opens "log"
        old_log.read(day, sizeof(day)); // Reads the amount of chars day[] have space for (2) to day[]
        
        std::string str1 = day;
        std::string str2 = timeAsString().substr(0,2);
        
        if (str2>str1) { // IOf "today" is bigger than "day in log"
            //std::cout << "slet log" << std::endl;
            std::remove(file_name_.c_str()); // c_str() is needed to convert to char* (cstring)
        } else {
            //std::cout << "Do nothing" << std::endl;
        }
        
        old_log.close();
    
}

bool Logger::write(std::string str) {
    
    switch(dest_){
        case 'p': // Prints on screen
            std::cout << timeAsString() << ": " << str << std::endl;
            break;
        case 'f': // "Prints" to file
            printToFile(str);
            break;
        case 'b': // Both of the above
            std::cout << timeAsString() << ": " << str << std::endl;
            printToFile(str);
            break;
    }
}

// Private functions

std::string Logger::timeAsString() {
    
    // Storing current time in a string
    time_t rawtime;
    struct tm * timeinfo;
    char str_buffer[20]; //DD-MM-YYYY HH:MM:SS 19 chars + 1 extra for "something"
    
    time (&rawtime);
    timeinfo = localtime(&rawtime);
    
    strftime(str_buffer, sizeof(str_buffer),"%d-%m-%Y %H:%M:%S",timeinfo);
    std::string str(str_buffer);
    
    // Returns the string
    return str;
    
}

bool Logger::printToFile(std::string str) {
    
    std::ofstream log(file_name_, std::ios::app); // opens for writing file
    
    if (log.is_open()){
        
        log << timeAsString()
        << ": "
        << str << '\n';
        
        return 1;
    }
    else {
        
        return 0;
    }
    
}
