# ESPhome Keypad
Two custom sensors to use 3x4 matrix keypads with [ESPhome](https://github.com/esphome/esphome). Uses the Arduino [Keypad Library](https://github.com/Chris--A/Keypad).

Two further custom sensors to use 4x4 matrix keypads with PCF8574 using I2C with [ESPHome](https://github.com/esphome/esphome).  Uses the Arduino [Keypad I2C Library](https://github.com/joeyoung/arduino_keypads/tree/master/Keypad_I2C).

## KeypadSensor
This sensor instantly publishes the numerical value of the pressed key. * becomes -6, # becomes -13, because of the ASCII value. After 500ms the value is reset to "Unknown".

## KeypadSensorI2C
This sensor operates the same as the KeypadSensor, but is configured for using the PCF8574 I/O I2C expander.

## KeypadTextSensor
This sensor gathers all pressed numbers in a string and publishes the hole string when # is pressed. The string is reset, when * is pressed. 
The string is automatically reset after some time.

## KeypadTextSensorI2C
This sensor operates the same as the KeypadTextSensor, but is configured for using the PCF8574 I/O I2C expander.
