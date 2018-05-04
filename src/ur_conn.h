#ifndef UR_CONN_H
#define UR_CONN_H

class UrConn {
private: // Private vars
    
// Ints setting the pins used for easier reading:
    
    // Inputs
    int open_grip_ur_;
    int close_grip_ur_;
    
    // Outputs
    int is_ready_;
    
public: // Public functions (+constructor)
    UrConn();
    ~UrConn();
    
    void isReady(bool b); // Sending ready signal to the robot
    
    bool getOpenGrip(); // Getting signal from robot to open gripper
    
    bool getCloseGrip(); // Getting signal from robot to close gripper
    
};

#endif // UR_CONN_H
