#include "esphome.h"
#include <Keypad_I2C.h>
#include <Keypad.h>
#include <Wire.h>


#define I2CADDR 0x20 // Set the Address of the PCF8574

class KeypadSensor : public Component, public Sensor {

    public:

        static const byte ROWS = 4; // Set the number of Rows
        static const byte COLS = 4; // Set the number of Columns

        // Set the Key at Use (4x4)
        char keys[ROWS][COLS] = {
          {'1', '4', '7', '/'},
          {'2', '5', '8', '0'},
          {'3', '6', '9', '.'},
          {'A', 'B', 'C', 'D'}
        };
    
        bool keyPublished = false;

        static const unsigned int resetTime = 500;
        unsigned int lastPublish = 0;
    
        // define active Pin (4x4)
        byte rowPins[ROWS] = {0, 1, 2, 3}; // Connect to Keyboard Row Pin
        byte colPins[COLS] = {4, 5, 6, 7}; // Connect to Pin column of keypad.

        // makeKeymap (keys): Define Keymap
        // rowPins:Set Pin to Keyboard Row
        // colPins: Set Pin Column of Keypad
        // ROWS: Set Number of Rows.
        // COLS: Set the number of Columns
        // I2CADDR: Set the Address for i2C
        // PCF8574: Set the number IC
        Keypad_I2C myKeypad = Keypad_I2C ( makeKeymap (keys), rowPins, colPins, ROWS, COLS, I2CADDR, PCF8574);

        void setup() override {
        // This will be called by App.setup()
            Wire.begin();
            myKeypad.begin();
        }
        void loop() override {
        // This will be called by App.loop()
            char myKey = myKeypad.getKey();
            if (myKey != NO_KEY) {
                ESP_LOGD("custom","A key has been pressed!");
                int key = myKey - 48;
                publish_state(key);
                keyPublished = true;
                lastPublish = millis();
            }
            else {
                if (keyPublished && (millis() - lastPublish) >= resetTime) {
                    publish_state(NAN);
                    keyPublished = false;
                }
            }
        }
};
