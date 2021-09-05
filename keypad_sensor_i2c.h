#include "esphome.h"
#include <Key.h>
#include <Keypad.h>
#include <Keypad_I2C.h>

#define I2CADDR 0x20 // Set the Address of the PCF8574

class KeypadSensor : public Component, public Sensor {

    public:

    const byte n_rows = 4; // Set the number of Rows
    const byte n_cols = 4; // Set the number of Columns

    // Set the Key at Use (4x4)
    char keys[n_rows] [n_cols] = {
      {'1', '4', '7', '/'},
      {'2', '5', '8', '0'},
      {'3', '6', '9', '.'},
      {'A', 'B', 'C', 'D'}
    };
    
    bool keyPublished = false;

    static const unsigned int resetTime = 500;
    unsigned int lastPublish = 0;
    
    // define active Pin (4x4)
    byte rowPins[n_rows] = {0, 1, 2, 3}; // Connect to Keyboard Row Pin
    byte colPins[n_cols] = {4, 5, 6, 7}; // Connect to Pin column of keypad.

    // makeKeymap (keys): Define Keymap
    // rowPins:Set Pin to Keyboard Row
    // colPins: Set Pin Column of Keypad
    // ROWS: Set Number of Rows.
    // COLS: Set the number of Columns
    // I2CADDR: Set the Address for i2C
    // PCF8574: Set the number IC
    Keypad_I2C myKeypad = Keypad(makeKeymap (keys), rowPins, colPins, n_rows, n_cols, I2CADDR, PCF8574);

    void setup() override {
    // This will be called by App.setup()
    }
    void loop() override {
    // This will be called by App.loop()
        char myKey = myKeypad.getKey();
        if (myKey != NO_KEY){
            int key = myKey - 48;
            publish_state(key);
            keyPublished = true;
            lastPublish = millis();
        }
        else{
            if (keyPublished && (millis() - lastPublish) >= resetTime){
                publish_state(NAN);
                keyPublished = false;
            }
        }

    }
};
