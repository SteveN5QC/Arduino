/*
 * 
 *  First Working Version
 *
 *  Modified Versiob
 *
 *  Explanation of Key Updates

    # as a Special Character:
        In getPINInput(), # is used to indicate the end of the PIN entry and is not included in pinBuffer. When the user presses #, it checks if the PIN length is within the allowed range (4-8 characters) and finalizes the input.

    * to Trigger PIN Change:
        In loop(), pressing * prompts the user to enter the current PIN to gain access to change the PIN. This special character is ignored in the actual PIN entry.
 *
 */

#include "Arduino.h"
#include <Keypad.h>

// Constants for the minimum and maximum PIN length
const int minPinLength = 4;
const int maxPinLength = 8;
const int maxAttempts = 5;

// Define what characters will be returned by each button
const char BUTTONS[4][4] = {
  { '1', '2', '3', 'A' },
  { '4', '5', '6', 'B' },
  { '7', '8', '9', 'C' },
  { '*', '0', '#', 'D' }
};

const byte ROW_PINS[4] = { 5, 4, 3, 2 };
const byte COL_PINS[4] = { 6, 7, 8, 13 };

Keypad heroKeypad = Keypad(makeKeymap(BUTTONS), ROW_PINS, COL_PINS, 4, 4);

const byte BUZZER_PIN = 12;
const byte RED_PIN = 11;
const byte GREEN_PIN = 10;
const byte BLUE_PIN = 9;

char currentPIN[maxPinLength + 1];
int attemptCount = 0;

void setup() {
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
  displayColor(128, 0, 0);

  Serial.begin(9600);
  Serial.println("Set a new PIN (4-8 characters). End with #:");
  setupNewPIN();
}

void loop() {
  char button_character = heroKeypad.getKey();

  if (button_character == '*') {          // Trigger new PIN setup
    giveInputFeedback();
    Serial.println("Access current PIN to set new PIN:");
    if (validatePIN()) {
      setupNewPIN();
    } else {
      Serial.println("Access Denied. Incorrect PIN.");
    }
  } else if (button_character == '#') {   // Trigger PIN validation for access
    giveInputFeedback();
    if (validatePIN()) {
      Serial.println("Access Granted!");
      giveSuccessFeedback();
      attemptCount = 0;
    } else {
      attemptCount++;
      Serial.print("Incorrect PIN. Attempts remaining: ");
      Serial.println(maxAttempts - attemptCount);
      giveErrorFeedback();

      if (attemptCount >= maxAttempts) {
        Serial.println("Too many failed attempts. Access locked.");
        while (true);  // Lock system after too many attempts
      }
    }
  }
}

// Set up a new PIN with verification
void setupNewPIN() {
  char tempPIN[maxPinLength + 1];

  Serial.println("Enter new PIN:");
  if (getPINInput(tempPIN)) {
    Serial.println("Re-enter new PIN for verification:");

    char verifyPIN[maxPinLength + 1];
    if (getPINInput(verifyPIN) && strcmp(tempPIN, verifyPIN) == 0) {
      strcpy(currentPIN, tempPIN);
      Serial.println("New PIN set successfully!");
      giveSuccessFeedback();
    } else {
      Serial.println("PINs did not match. Restart setup.");
      setupNewPIN();
    }
  }
}

// Get PIN input with "#" to end entry
bool getPINInput(char* pinBuffer) {
  int charIndex = 0;
  while (true) {
    char key = heroKeypad.getKey();
    if (key) {
      if (key == '#') {  // End of PIN entry
        pinBuffer[charIndex] = '\0';
        if (charIndex >= minPinLength && charIndex <= maxPinLength) {
          return true;
        } else {
          Serial.println("Invalid PIN length. Try again.");
          return false;
        }
      }

      // Add character if within limits and ignore '*'
      if (charIndex < maxPinLength && key != '*') {
        pinBuffer[charIndex] = key;
        Serial.print("*");
        charIndex++;
      }
      giveInputFeedback();
    }
  }
}

// Validate entered PIN against currentPIN
bool validatePIN() {
  char enteredPIN[maxPinLength + 1];
  if (getPINInput(enteredPIN)) {
    if (strcmp(enteredPIN, currentPIN) == 0) {
      giveSuccessFeedback();
      return true;
    }
  }
  giveErrorFeedback();
  return false;
}

void displayColor(byte red_intensity, byte green_intensity, byte blue_intensity) {
  analogWrite(RED_PIN, red_intensity);
  analogWrite(GREEN_PIN, green_intensity);
  analogWrite(BLUE_PIN, blue_intensity);
}

void giveInputFeedback() {
  displayColor(0, 0, 0);
  tone(BUZZER_PIN, 880, 200);
  delay(200);
  displayColor(0, 0, 128);
}

void giveSuccessFeedback() {
  displayColor(0, 0, 0);
  tone(BUZZER_PIN, 300, 200);
  delay(200);
  tone(BUZZER_PIN, 500, 500);
  delay(500);
  displayColor(0, 128, 0);
}

void giveErrorFeedback() {
  displayColor(0, 0, 0);
  tone(BUZZER_PIN, 300, 200);
  delay(200);
  tone(BUZZER_PIN, 200, 500);
  delay(500);
  displayColor(128, 0, 0);
}
