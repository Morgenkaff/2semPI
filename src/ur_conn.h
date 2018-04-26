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
    
    isReady(bool b); // Sending ready signal to the robot
    
    getOpenGrip(); // Getting signal from robot to open gripper
    
    getCloseGrip(); // Getting signal from robot to close gripper

#endif // UR_CONN_H
