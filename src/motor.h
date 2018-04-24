#ifndef MOTOR_H
#define MOTOR_H

class Motor {
    
public:
        
    virtual void run(int&, bool&) = 0; // runs motor at given speed (1 - 5), in given direction 1 = opening 0 = closing
    
    virtual void stop() = 0; // Stops the motor
        
};
    

#endif // MOTOR_H
