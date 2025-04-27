# The arduino motion alarm with keypad.

## What you will need:

- arduino (obviously)
- pir motion sensor
- led (red)
- piezo buzzer
- 4x4 keypad
- 10 male to male wires
- 3 male to female wires
- 10 ohm resistor

## pinout
 hook up the pir to vcc and ground, and the out to pin 2
 hook the buzzer onto pin 3 and ground,
 hook the keypad  to pins 10-4 (colum pins: 10, 9, 8. row pins: 7, 6, 5, 4)
 hook up the led to pin 11 then ground (use resistor also)
## code
use the motion_alarm_circuit_with_keypad.ino file  in the arduino ide. 

you can edit the passcode at line 16 to your liking.

when you're done, just upload to your arduino.
'
# need help?

there will be a screenshot of the same thing just visualised in tinkercad.
