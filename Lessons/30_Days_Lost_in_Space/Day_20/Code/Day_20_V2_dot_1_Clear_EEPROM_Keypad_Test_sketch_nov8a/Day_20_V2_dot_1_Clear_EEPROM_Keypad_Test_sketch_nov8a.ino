#include <Keypad.h>
#include <EEPROM.h>

// Constants for minimum and maximum PIN length
const int minPinLength = 4;
const int maxPinLength = 8;
const int maxAttempts = 5;
const int eepromStartAddress = 0; // EEPROM start address for PIN
const int magicNumberAddress = 100; // EEPROM address for magic number
const int magicNumber = 1234; // Unique number to flag valid EEPROM data

// Keypad setup
const char BUTTONS[4][4] = {
  { '1', '2', '3', 'A' },
  { '4', '5', '6', 'B' },
  { '7', '8', '9', 'C' },
  { '*', '0', '#', 'D' }
};
const byte ROW_PINS[4] = { 7, 8, 9, 11 };
const byte COL_PINS[4] = { 12, 13, A0, A1 };
Keypad heroKeypad = Keypad(makeKeymap(BUTTONS), ROW_PINS, COL_PINS, 4, 4);

char currentPIN[maxPinLength + 1];  // Stores the active PIN
int attemptCount = 0;
bool isLocked = true;  // System starts in locked state

void setup() {
  Serial.begin(9600);

  // Check if magic number is in EEPROM; if not, clear EEPROM and require new PIN
  if (EEPROM.read(magicNumberAddress) != magicNumber) {
    Serial.println("New program detected. Clearing EEPROM...");
    clearEEPROM();
    EEPROM.write(magicNumberAddress, magicNumber); // Store the magic number after clearing
    Serial.println("No PIN found. Set a new PIN (4-8 chars, end with #):");
    setupNewPIN();
  } else {
    Serial.println("Stored PIN loaded. Enter PIN to unlock.");
    loadPINFromEEPROM();
  }
}

void loop() {
  if (isLocked) {
    Serial.println("System is locked. Enter PIN to unlock:");
    if (validatePIN()) {
      isLocked = false;
      Serial.println("System Unlocked! Options: '#' to lock, '*' to change PIN, other keys to work.");
    } else {
      attemptCount++;
      if (attemptCount >= maxAttempts) {
        Serial.println("Too many failed attempts. System locked.");
        while (true); // Lock system permanently
      }
    }
  } else {
    char button_character = heroKeypad.getKey();
    if (button_character) {
      if (button_character == '#') {  // Lock system
        isLocked = true;
        Serial.println("System locked. Enter PIN to unlock.");
      } else if (button_character == '*') {  // Change PIN
        Serial.println("Enter current PIN to change:");
        if (validatePIN()) {
          Serial.println("PIN accepted. Set a new PIN:");
          setupNewPIN();
          Serial.println("New PIN set. System unlocked.");
        } else {
          Serial.println("Incorrect PIN. Returning to unlocked state.");
        }
      } else {  // Any other character to "work"
        Serial.print("Working... You pressed: ");
        Serial.println(button_character);
      }
    }
  }
}

// Set up a new PIN with verification
void setupNewPIN() {
  char tempPIN[maxPinLength + 1];
  Serial.println("Enter new PIN:");
  if (getPINInput(tempPIN)) {
    Serial.println("Re-enter new PIN to confirm:");
    char verifyPIN[maxPinLength + 1];
    if (getPINInput(verifyPIN) && strcmp(tempPIN, verifyPIN) == 0) {
      strcpy(currentPIN, tempPIN);
      savePINToEEPROM();
      Serial.println("New PIN set successfully!");
    } else {
      Serial.println("PINs did not match. Restart setup.");
      setupNewPIN();
    }
  }
}

// Save the current PIN to EEPROM
void savePINToEEPROM() {
  int length = strlen(currentPIN);
  EEPROM.write(eepromStartAddress, length);  // Store the length
  for (int i = 0; i < length; i++) {
    EEPROM.write(eepromStartAddress + 1 + i, currentPIN[i]);
  }
}

// Load the PIN from EEPROM
bool loadPINFromEEPROM() {
  int length = EEPROM.read(eepromStartAddress);
  if (length < minPinLength || length > maxPinLength) {
    return false;
  }
  for (int i = 0; i < length; i++) {
    currentPIN[i] = EEPROM.read(eepromStartAddress + 1 + i);
  }
  currentPIN[length] = '\0';
  return true;
}

// Clear the EEPROM (reset all bytes to 0)
void clearEEPROM() {
  for (int i = eepromStartAddress; i < EEPROM.length(); i++) {
    EEPROM.write(i, 0);  // Reset each byte in EEPROM to 0
  }
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
    }
  }
}

// Validate entered PIN against currentPIN
bool validatePIN() {
  char enteredPIN[maxPinLength + 1];
  if (getPINInput(enteredPIN)) {
    if (strcmp(enteredPIN, currentPIN) == 0) {
      Serial.println("Access Granted!");
      return true;
    }
  }
  Serial.println("Incorrect PIN.");
  return false;
}
