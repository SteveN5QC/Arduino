/*
 * 
 *  Persistent PIN with EEPROM
 *
 */
#include "Arduino.h"
#include <Keypad.h>
#include <EEPROM.h>  // Include EEPROM library

// Constants for the minimum and maximum PIN length
const int minPinLength = 4;
const int maxPinLength = 8;
const int maxAttempts = 5;
const int eepromStartAddress = 0;  // Starting address in EEPROM for PIN storage

char currentPIN[maxPinLength + 1];  // Stores the active PIN
int attemptCount = 0;               // Track number of attempts
bool isLocked = true;               // Track lock state

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

void setup() {
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);

  Serial.begin(9600);

  // Load the PIN from EEPROM
  if (loadPINFromEEPROM()) {
    Serial.println("Stored PIN loaded successfully.");
    isLocked = true;
    displayColor(128, 0, 0);  // Red LED indicates locked state
  } else {
    Serial.println("No PIN found in memory. Set a new PIN (4-8 characters). End with #:");
    setupNewPIN();  // Prompt to set new PIN if no valid PIN is in EEPROM
  }
}

void loop() {
  if (isLocked) {
    Serial.println("System is locked. Enter PIN to unlock:");
    if (validatePIN()) {
      isLocked = false;
      Serial.println("System Unlocked! Options: '#' to lock, '*' to change PIN, any other key to work.");
      displayColor(0, 128, 0);  // Green LED indicates unlocked state
    } else {
      attemptCount++;
      if (attemptCount >= maxAttempts) {
        Serial.println("Too many failed attempts. Access locked permanently.");
        while (true); // Lock indefinitely
      }
    }
  } else {
    char button_character = heroKeypad.getKey();
    if (button_character) {
      if (button_character == '#') {  // Lock the system
        isLocked = true;
        Serial.println("System locked. Enter PIN to unlock.");
        displayColor(128, 0, 0);  // Red LED for locked state
      } else if (button_character == '*') {  // Change PIN
        Serial.println("Enter current PIN to change it:");
        if (validatePIN()) {
          Serial.println("PIN accepted. Setting up new PIN.");
          displayColor(128, 80, 0);  // Yellow LED while changing PIN
          setupNewPIN();
          Serial.println("New PIN set successfully. System unlocked.");
          displayColor(0, 128, 0);  // Green LED for unlocked state
        } else {
          Serial.println("Incorrect PIN. Returning to unlocked mode.");
          displayColor(0, 128, 0);  // Keep green LED for unlocked state
        }
      } else {  // Any other character to "work"
        Serial.print("Working... You pressed: ");
        Serial.println(button_character);
        giveInputFeedback();  // Short beep and blue LED for each work action
        displayColor(0, 128, 0);  // Maintain green LED for unlocked state
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
      savePINToEEPROM();  // Save the new PIN to EEPROM
      Serial.println("New PIN set successfully!");
      giveSuccessFeedback();
    } else {
      Serial.println("PINs did not match. Restarting setup.");
      setupNewPIN();
    }
  }
}

// Save the current PIN to EEPROM
void savePINToEEPROM() {
  int length = strlen(currentPIN);
  EEPROM.write(eepromStartAddress, length);  // Store the length of the PIN
  for (int i = 0; i < length; i++) {
    EEPROM.write(eepromStartAddress + 1 + i, currentPIN[i]);
  }
}

// Load the PIN from EEPROM
bool loadPINFromEEPROM() {
  int length = EEPROM.read(eepromStartAddress);  // Read the PIN length
  if (length < minPinLength || length > maxPinLength) {
    return false;  // No valid PIN stored
  }
  for (int i = 0; i < length; i++) {
    currentPIN[i] = EEPROM.read(eepromStartAddress + 1 + i);
  }
  currentPIN[length] = '\0';  // Null-terminate the PIN
  return true;
}

// Get PIN input with "#" to end entry
bool getPINInput(char* pinBuffer) {
  int charIndex = 0;
  while (true) {
    char key = heroKeypad.getKey();
    if (key) {
      if (key == '#') {
        pinBuffer[charIndex] = '\0';
        if (charIndex >= minPinLength && charIndex <= maxPinLength) {
          return true;
        } else {
          Serial.println("Invalid PIN length. Try again.");
          return false;
        }
      }
      if (charIndex < maxPinLength) {
        pinBuffer[charIndex] = key;
        Serial.print("*");
        charIndex++;
      }
      giveInputFeedback();
    }
  }
}

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
