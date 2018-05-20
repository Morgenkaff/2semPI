#ifndef PIN_CTRL_H
#define PIN_CTRL_H

#include "hid.h" // headerfile for the HID
#include "ur_conn.h" // headerfile for the class connecting with UR
#include "gripper_conn.h" // Headerfile for the motor control class
#include <thread>


class PinCtrl {
private:
    
    Logger* log; // Used for debuggin
    
    Hid* hid; // Pointer used for constructing the hid class on the stack.
    
    UrConn* ur_conn; // Pointer used for constructing the UrConn class
    
    GripperConn* gripper_conn; // Pointer to the motor control class
    
    std::thread* input_scan_thread;
    
    // Vars used by the input scanner
    bool scan_inputs_; // Bool for controlling scanning loop. 1 = running, 0 = stopped
    int scan_freq_; // Sets how many times pr second, the scanning loop should run (approx)
    int input_ ; // Set the value to corresponding input. (See input table in documentation)
    
    // Vars (maybe?) used for handling the motor (type, speed etc): - saved for when moto class is written
    
    bool motor_type_;   // Bool: 1 = stepper, 0 = dc.
                        // Could be changed to eg int, if we get more than 2 motor types
    int speed_;         // Speed is set in a range of 1 - 3 (1 is fastes 3 is slowest)
    bool direction_;    // 1 is closing, 0 is opening
    
    
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
    
    // True if termination functioin have been run
    bool terminated_;
    
public:
    PinCtrl(); // Simple constructor. Nothing happens
    ~PinCtrl();
    
    bool init(); // Initialises the GPIOs. Returns 1 if success.
    
    void run(int); // int sets run state (see int run_state_ above)
    
    void working();
    
    void standby();
    
    void terminate();
    
    void setMotorType(bool&); // (see motor_type_)
     
    void setMotorSpeed(int); // (see speed_)
    
private:
    
    void inputScanner();
    
};

#endif // PIN_CTRL_H
