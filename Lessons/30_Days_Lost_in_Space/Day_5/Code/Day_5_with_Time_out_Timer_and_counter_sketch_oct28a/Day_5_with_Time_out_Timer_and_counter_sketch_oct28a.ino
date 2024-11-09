/*
 * 30 Days - Lost in Space
 * Day 5 - Creative Day 1 -- Embellished with Time Out Timer and Counter
 *
 * Learn more at https://learn.inventr.io/adventure
 *
 
 */


#include "Arduino.h"  // include information about our HERO

byte switchState = 0;
byte previousSwitchState = 0; // Store the previous switch state
unsigned long lastSwitchChangeTime = 0;
bool isCounting = false;       // Flag to switch between modes
byte counter = 0;

void setup() {
    // Set up pins for DIP switch and LEDs
    pinMode(2, INPUT);
    pinMode(3, INPUT);
    pinMode(4, INPUT);
    pinMode(10, OUTPUT);
    pinMode(11, OUTPUT);
    pinMode(12, OUTPUT);
}

void loop() {
    // Read the DIP switch state
    switchState = (digitalRead(4) << 2) | (digitalRead(3) << 1) | digitalRead(2);

    // Check if switch state has changed
    if (switchState != previousSwitchState) {
        previousSwitchState = switchState;     // Update previous state
        lastSwitchChangeTime = millis();       // Reset the timer
        isCounting = false;                    // Stay in DIP switch mode
        displaySwitchState(switchState);       // Display current switch state
    }

    // Check the elapsed time to determine mode
    if (millis() - lastSwitchChangeTime > 15000) {  // After 15 seconds
        isCounting = true;
    }

    if (isCounting) {
        displayBinaryCounter();
    } else {
        displaySwitchState(switchState);  // Display switch state within 15 seconds
    }
}

// Function to display DIP switch state
void displaySwitchState(byte state) {
    digitalWrite(10, state & 0b001 ? HIGH : LOW); // LED on pin 10 (1)
    digitalWrite(11, state & 0b010 ? HIGH : LOW); // LED on pin 11 (2)
    digitalWrite(12, state & 0b100 ? HIGH : LOW); // LED on pin 12 (4)
}

// Function to display binary counter from 0 to 7
void displayBinaryCounter() {
    digitalWrite(10, counter & 0b001 ? HIGH : LOW);  // LED on pin 10
    digitalWrite(11, counter & 0b010 ? HIGH : LOW);  // LED on pin 11
    digitalWrite(12, counter & 0b100 ? HIGH : LOW);  // LED on pin 12

    delay(3000); // Hold each counter state for 1 second -->  Changed to 3 seconds
    counter = (counter + 1) % 8;  // Loop back to 0 after reaching 7
}
