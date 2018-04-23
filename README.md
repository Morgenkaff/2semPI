# 2semPI

 #### This is a simple program for controlling the GPIOs of the Raspberry Pi 3 with C++.
 
 The code should have sufficient comments to grasp the in and outs.
 
 Naming should follow the "Google C++ Style Guide".
 
 Documentation is underway.
 
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
   open_end_grip|22 23|green_led
            3.3v|-- 24|red_led
 closed_end_grip|10 --|GND
   close_grip_ur| 9 25|blue_led
    open_grip_ur|11  8|yellow_led
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
</pre>
