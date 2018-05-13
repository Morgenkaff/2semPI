#ifndef STEP_MOTOR_H
#define STEP_MOTOR_H

#include "motor.h"
#include <thread>

class Stepper : public Motor {
private:

    // Vars used for setting readeble names for the GPIOs used by the DC motor:
    
    int step_1_;
    int step_2_;
    int step_3_;
    int step_4_;
    
    // Vars used for driving the stepper
    
    int step_speed_;      // The amount of ms the loop should "sleep" to give the
                          // preferred speed
    bool step_direction_; // Used to multiply with step_traverser_ for direction
                          // Should be set as 1 or -1
    bool step_traverser_; // Int used to control for loop
    
    int step_case_;       // Used to set case in the case switch (used to drive stepper)
    
    int this_run_steps_;  // Hold the amount of steps taken since last stop
    long total_steps_;    // The total amount of steps since class constructed
        
    std::thread* step_thread_;
    bool thread_started_;
    
public:
    Stepper(); // Default constructor, sets GPIOs used
    
    void run(int&, bool&); // runs motor at given speed (1 - 5), in given direction 1 = opening 0 = closing
    
    void stop(); // Stops the motor by setting all used pins to 0 (low)
    
    int getThisRunSteps(); // Returns the total amount of steps taken since motors last stop
    int getTotaltSteps();  // Returns the total amount of steps the motor has taken since class constructed
    
private:
<<<<<<< HEAD
    void stepDriver();     // Should run in a loop ina seperate thread
                           // so its possible to change speed and such
    void set_step(int&);
    void stepTraverse();
    void loopCase();
=======
    void stepDriver();  // Should run in a loop ina seperate thread
                        // so its possible to change speed and such
>>>>>>> 37a593ae0387b6d11f8d26c9645415af5effafea
};

#endif // STEP_MOTOR_H
