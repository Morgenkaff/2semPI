/*
 *  Program for testing c++ on the Pi and how to control the GPIOs with it.
 *  The library for using GPIOs is pigpio (http://abyz.me.uk/rpi/pigpio).
 *
 *  To build the code, use the command:
 *
 *    g++ -o "name_of_output_file" "name_of_input_file".cpp -lpigpio -lrt
 *
 *  lpigpio includes the pigpio library and lrt is to include the library for realtime functionality
 *  (required by pigpio).
 */

/*
 *  Misc vars as for user interaction:
 */

bool good_input = false;
char user_input_char;
int user_input_int;

/*
 * Misc vars for controlling the program.
 */

bool run_program = true; // True when the program-loop should be running
bool run_motor = false; // True when the motor should be turning
bool direction; // Sets wich direction to turn the motor
int step_case; // Sets wich case in the switch to set the pins to
int kill_switch_control; // Input for a potential kill switch
bool kill_switch = false; // Is true when kill switch have been pressed

/*
 * This function sets the GPIO used for the stepper motor.
 * This in a loop with the functions stepTraverse and loopCase, will it run
 * the stepper motor continuosly.
 */
void stepper(){
        switch(step_case){
            case 0:
                gpioWrite(BLU, LOW); 
                gpioWrite(GRN, LOW);
                gpioWrite(ORG, LOW);
                gpioWrite(WHT, HIGH);
                break; 
            case 1:
                gpioWrite(BLU, LOW); 
                gpioWrite(GRN, LOW);
                gpioWrite(ORG, HIGH);
                gpioWrite(WHT, HIGH);
                break; 
            case 2:
                gpioWrite(BLU, LOW); 
                gpioWrite(GRN, LOW);
                gpioWrite(ORG, HIGH);
                gpioWrite(WHT, LOW);
                break; 
            case 3:
                gpioWrite(BLU, LOW); 
                gpioWrite(GRN, HIGH);
                gpioWrite(ORG, HIGH);
                gpioWrite(WHT, LOW);
                break; 
            case 4:
                gpioWrite(BLU, LOW); 
                gpioWrite(GRN, HIGH);
                gpioWrite(ORG, LOW);
                gpioWrite(WHT, LOW);
                break; 
            case 5:
                gpioWrite(BLU, HIGH); 
                gpioWrite(GRN, HIGH);
                gpioWrite(ORG, LOW);
                gpioWrite(WHT, LOW);
                break; 
            case 6:
                gpioWrite(BLU, HIGH); 
                gpioWrite(GRN, LOW);
                gpioWrite(ORG, LOW);
                gpioWrite(WHT, LOW);
                break; 
            case 7:
                gpioWrite(BLU, HIGH); 
                gpioWrite(GRN, LOW);
                gpioWrite(ORG, LOW);
                gpioWrite(WHT, HIGH);
                break; 
            default:
                gpioWrite(BLU, LOW); 
                gpioWrite(GRN, LOW);
                gpioWrite(ORG, LOW);
                gpioWrite(WHT, LOW);
                break; 
        }
}

/*
 * This function traverse the step_case, depending on the direction.
 */
void stepTraverse(){
    if(direction==1){ step_case++;}
    if(direction==0){ step_case--;}
}

/*
 * This function changes the var step_case, securing that the case switch
 * will "loop around".
 */
void loopCase(){    
    if(step_case>7){step_case=0;}
    if(step_case<0){step_case=7;}
}

/*
 * base function for running the stepper motor.
 * It takes a bool parameter for the direction, 1 for clockwise 0 for counter.
 */
void run_step_motor(bool p_direction){
    
    // Sets the direction as given
    direction = p_direction;
    run_motor = true;
    
    while (run_motor) {
        stepper();
        
}

