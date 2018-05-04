# 2semPI

 #### This is a simple program for controlling the GPIOs of the Raspberry Pi 3 with C++.
 
 Compile with:
 
 <code>
 g++ src/*.cc -lpigpio -lrt -lpthread
 </code>
 
 -lpigpio is for the pigpio library, used for the GPIOs (http://abyz.me.uk/rpi/pigpio).
 -lrt is required by pigpio. Used for realtime.
 -lpthread is used to seperate a thread for checking inputs independent from the main program.
 
 The code should have sufficient comments to grasp the in and outs.
 
<pre>
  _________________________________
 |        PINS ON HARDWARE:        |
  ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯
                 _____
            3.3v|-- --|--
    open_end_hid| 2 --|--
  closed_end_hid| 3 --|GND
         kill_sw| 4 14|--
             GND|-- 15|--
  close_grip_hid|17 18|--
   open_grip_hid|27 --|--
   open_end_grip|22 23|yellow_led
            3.3v|-- 24|blue_led
 closed_end_grip|10 --|GND
   close_grip_ur| 9 25|green_led
    open_grip_ur|11  8|red_led
             GND|--  7|--
              --|-- --|--
          step_4| 5 --|GND
          step_3| 6 12|--
          step_2|13 --|GND
          step_1|19 16|--
   grip_ready_ur|26 20|--
             GND|-- 21|--
                 ¯¯¯¯¯
 
 ('--' indicates that pin is not used/connected on hardware.)
 (step_# is used either by the stepper motor OR the dc motor. The dc only uses step_1 and step_2. Better names could be found..)
</pre>
 
 ## TODO:
 
- There should be a style guide
- All "#define's" for the pins should be replaced with vars of type int.
- Class diagram and documentation of classes.
- ...
