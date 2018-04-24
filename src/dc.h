#ifndef DC_H
#define DC_H

#include "motor.h"

class Dc : public Motor {
private:
    
    // Vars used for setting readeble names for the GPIOs used by the DC motor:
    
    int run_open_;
    int run_close_;
    
public:
    Dc(); // Default constructor, sets GPIOs used
    ~Dc();
    
    void run(int&, bool&); // runs motor at given speed (1 - 5), in given direction 1 = opening 0 = closing
    
    void stop(); // Stops the motor by setting all used pins to 0 (low)
        
};
    

#endif // PIN_DC_H
