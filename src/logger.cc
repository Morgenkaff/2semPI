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

#include "logger.h"

Logger::Logger() {
    
    // Reads log and deletes it if its older than 10 days
    char day[2]; // The oldes date is the first two chars in file
    std::ifstream log("log"); // Opens "log"
    log.read(day, sizeof(day)); // Reads the amount of chars day[] have space for (2) to day[]

    std::string str1 = day;
    std::string str2 = timeAsString().substr(0,2);
    
    if (str2>str1) {
        //std::cout << "slet log" << std::endl;
        remove("log");
    } else {
        //std::cout << "Do nothing" << std::endl;
    }
    
    //Vars used for logging - sat to 0 when logger gets constructed
    total_runtime_ = 0;
    runtime_start_time_ = 0;
    runtime_stop_time_ = 0;
    total_opens_ = 0;
    total_closes_ = 0;
    
}

bool Logger::log(char c, std::string str) {

    switch(c){
        case 'p': // Prints on screen
            std::cout << timeAsString() << " : " << str << std::endl;
            break;
        case 'f': // "Prints" to file
            printToFile(str);
            break;
        case 'b': // Both of the above
            std::cout << timeAsString() << " : " << str << std::endl;
            printToFile(str);
            break;
    }
}

std::string Logger::timeAsString() {
    
    // Storing current time in a string
    time_t rawtime;
    struct tm * timeinfo;
    char str_buffer[20]; //DD-MM-YYYY HH:MM:SS 19 chars + 1 extra for "something"
    
    time (&rawtime);
    timeinfo = localtime(&rawtime);
    
    strftime(str_buffer, sizeof(str_buffer),"%Y-%m-%d %H:%M:%S",timeinfo);
    std::string str(str_buffer);
        
    // Returns the string
    return str;
    
}

bool Logger::printToFile(std::string str) {
    
    std::ofstream log;
    log.open("log", std::ios::app);
    
    if (log.is_open()){
        
        log << timeAsString()
        << " : "
        << str << '\n';
        
        log.close();
        return 1;
    }
    else {
        
        return 0;
    }
    
}
