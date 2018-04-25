#ifndef PIN_CTRL_H
#define PIN_CTRL_H

#include "hid.h" // headerfile for the HID
#include "motor_ctrl.h" // Headerfile for the motor control class
#include <thread>


class PinCtrl {
private:
    
    Hid* hid; // Pointer used for constructing the hid class on the stack.
    
    MotorCtrl* motor_ctrl; // Pointer to the motor control class
    
    std::thread* input_scan_thread;
    
    // Vars used by the input scanner
    bool scan_inputs_; // Bool for controlling scanning loop. 1 = running, 0 = stopped
    int scan_freq_; // Sets how many times pr second, the scanning loop should run (approx)
    int input_ ; // Set the value to corresponding input. (See input table in documentation)
    
    // Vars (maybe?) used for handling the motor (type, speed etc): - saved for when moto class is written
    
    bool motor_type_;   // Bool: 1 = stepper, 0 = dc.
                        // Could be changed to eg int, if we get more than 2 motor types
    int speed_;         // Speed is set in a range of 1 - 3 (1 is slowest 5 is fastest)
    bool direction_;    // 1 is closing, 0 is opening
    bool motor_running_; // Used to check if motor is stopped (in working_loop)
    bool temp_direction_;
    
    
    // Vars for state switch:
    bool running_;
    int run_state_;
    
    // Run state:
    // 1: working
    // 2: standby
    
    //Vars for working loop:
    bool in_working_loop_;
    
    //Vars for standby loop:
    bool in_standby_loop_;
    
public:
    PinCtrl(); // Simple constructor. Nothing happens
    ~PinCtrl();
    
    bool init(); // Initialises the GPIOs. Returns 1 if success.
    
    void run(int); // int sets run state (see int run_state_ above)
    
    void working();
    
    void standby();
    
    void reset(); // Resets all the pins to their default state.
    
    bool terminate();
    
    void getInputs();
    
    void setMotorType(bool&); // (see motor_type_)
     
    void setMotorSpeed(int); // (see speed_)
    
    void setMotorDirection(bool&); // (see direction_)
    
    
    
private:
    
    void inputScanner();
    
};

#endif // PIN_CTRL_H
