#include "esphome.h"
#include <Key.h>
#include <Keypad.h>
#include <Keypad_I2C.h>

#define I2CADDR 0x20 // Set the Address of the PCF8574

class KeypadTextSensor : public Component, public TextSensor {

    public:

    std::string keysequenz;

    static const byte n_rows = 4;
    static const byte n_cols = 4;

    static const unsigned int resetTime = 300;
    unsigned int resetCounter = 0;
    bool keyPressed = false;
    
  // Set the Key at Use (4x4)
    char keys[n_rows][n_cols] = {
      {'1', '4', '7', '/'},
      {'2', '5', '8', '0'},
      {'3', '6', '9', '.'},
      {'*', 'B', 'C', '#'}
    };
    
    byte colPins[n_cols] = {0, 1, 2, 3};
    byte rowPins[n_rows] = {4, 5, 6, 7};
    
    // makeKeymap (keys): Define Keymap
    // rowPins: Set Pin to Keyboard Row
    // colPins: Set Pin Column of Keypad
    // n_rows: Set Number of Rows.
    // n_cols: Set the number of Columns
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
            if (myKey == '#'){
                publish_state(keysequenz);
                keysequenz.clear();
                resetCounter = 0;
                keyPressed = false;
            }
            else if (myKey == '*'){
                keysequenz.clear();
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