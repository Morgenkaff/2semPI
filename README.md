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
       open_grip| 2 --|--
      close_grip| 3 --|GND
         kill_sw| 4 14|green_led
             GND|-- 15|red_led
     bottom_side|17 18|--
        top_side|27 --|--
close_end_switch|22 23|blue_led
            3.3v|-- 24|yellow_led
 open_end_switch|10 --|GND
    open_grip_ur| 9 25|--
   close_grip_ur|11  8|--
             GND|--  7|--
              --|-- --|--
              --| 5 --|GND
          step_3| 6 12|--
              --|13 --|GND
              --|19 16|is_ready
          step_1|26 20|step_4
             GND|-- 21|step_2
                 ¯¯¯¯¯
 
 The names are the same used for the vars used for the pin names in teh code.
 ('--' indicates that pin is not used/connected on hardware.)
 (step_# is used either by the stepper motor OR the dc motor. The dc only uses step_1 and step_2. 
 Better names could be found..)
</pre>
 
 ## TODO:
 
- There should be a style guide
- All "#define's" for the pins should be replaced with vars of type int.
- Class diagram and documentation of classes.
- ...
