#include "esphome.h"
#include <Keypad.h>
#include <Wire.h>
#include "Keypad_I2C/Keypad_I2C.h"  //downloaded library folder located in /src folder

#define I2CADDR 0x20 // Set the Address of the PCF8574

class KeypadTextSensor : public Component, public TextSensor {

    public:

        std::string keysequenz;

        static const byte ROWS = 4;
        static const byte COLS = 4;

        // Set the Key at Use (4x4)
        char keys[ROWS][COLS] = {
          {'1', '4', '7', '/'},
          {'2', '5', '8', '0'},
          {'3', '6', '9', '.'},
          {'*', 'B', 'C', '#'}
        };
    
        bool keyPressed = false;
    
        static const unsigned int resetTime = 300;
        unsigned int resetCounter = 0;
    
        // define active Pins (4x4)
        byte rowPins[ROWS] = {2, 4, 5, 6}; // Connect to Keyboard Row Pin
        byte colPins[COLS] = {7, 0, 1, 3}; // Connect to Pin column of keypad.

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
            if (myKey != NO_KEY){
                ESP_LOGD("custom","A key has been pressed!");
                
                if (myKey == '#'){
                    ESP_LOGD("custom","End sequence");
                    publish_state(keysequenz);
                    keysequenz.clear();
                    resetCounter = 0;
                    keyPressed = false;
                }
                else if (myKey == '*'){
                    keysequenz.clear();
                    ESP_LOGD("custom","Clear sequence");
                    publish_state(keysequenz);
                    resetCounter = 0;
                    keyPressed = false;
                }
                else {
                    keysequenz.push_back(myKey);
                    keyPressed = true;
                }
            }
            if (keyPressed){
                resetCounter++;
            }
            if (resetCounter >= resetTime){
                keysequenz.clear();
                publish_state(keysequenz);
                resetCounter = 0;
                keyPressed = false;
            }
        }
};
