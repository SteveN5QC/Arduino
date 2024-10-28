/*
 * 30 Days - Lost in Space
 * Day 5 - Creative Day 1
 *
 * Learn more at https://learn.inventr.io/adventure
 *
 
 */


#include "Arduino.h"  // include information about our HERO



byte switchState = 0;

void setup() {
    pinMode(2, INPUT);
    pinMode(3, INPUT);
    pinMode(4, INPUT);
    pinMode(10, OUTPUT);  // Rewritten to use pins 10, 11, 12  -- This line WAS pinMode(9, OUTPUT);
    pinMode(11, OUTPUT);  // Rewritten to use pins 10, 11, 12  -- This line WAS pinMode(10, OUTPUT);
    pinMode(12, OUTPUT);  // Rewritten to use pins 10, 11, 12  -- This line WAS pinMode(11, OUTPUT);
}

void loop() {
    // Read the DIP switch state and create a binary number
    //  Flip left to right WAS:  switchState = (digitalRead(2) << 2) | (digitalRead(3) << 1) | digitalRead(4);
    switchState = (digitalRead(4) << 2) | (digitalRead(3) << 1) | digitalRead(2);

    // Turn LEDs on or off based on the switchState value
    digitalWrite(10, switchState & 0b001 ? HIGH : LOW);   // LED on pin 10 -- Rewritten to use pins 10, 11, 12 This line WAS LED on pin 9
    digitalWrite(11, switchState & 0b010 ? HIGH : LOW);  // LED on pin 11 -- Rewritten to use pins 10, 11, 12 This line WAS LED on pin 10
    digitalWrite(12, switchState & 0b100 ? HIGH : LOW);  // LED on pin 12 -- Rewritten to use pins 10, 11, 12 This line WAS LED on pin 11
}
