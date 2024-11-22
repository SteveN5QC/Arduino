/*
 * Steve's Template
 * General Commentst and Logic Narrative
 *
 * Pin Assigmnent Chart
 *
 * 9 – Red Led
 * 8 – Blue Led
 * 2 -- Button
 *
 * const int ledPinDot = 8;       // The Blue (Dot) Led is wired to Pin 8
 * const int ledPinDash = 9;       // The Red (Dash) Led is wired to  Pin 9
 * const int buttonPin = 2;    // The button is wired to Pin 2

 * 
 * Variable List
 * 
 * 


int buttonState = 0;        // Variable to store the current button state
int lastButtonState = 0;    // Variable to store the last button state
unsigned long pressStartTime = 0; // Time when the button is pressed
unsigned long pressEndTime = 0;   // Time when the button is released
const int shortPressTime = 200;  // Threshold for a short press (dot)
const int longPressTime = 550;   // Threshold for a long press (dash)
 */


// Explicitly include Arduino.h to insure compatability if using other than the Arduino IDE
#include "Arduino.h"

// ************************************************
//    Include other libraries and header files as needed.

// ************************************************
/*  Setup for DIP switch pins for devices
 *  const int devicePin1 = 2;   // Device 1 is connected to pin 2
 *   
 *  Define Variables Needed
 *
 *  int variableState1 = 0;    // Variable to ....
 * 
 */

const int ledPinDot = 8;        // The Blue (Dot) Led is wired to Pin 8
const int ledPinDash = 9;       // The Red (Dash) Led is wired to  Pin 9
const int buttonPin = 2;        // The button is wired to Pin 2


int buttonState = 0;        // Variable to store the current button state
int lastButtonState = 0;    // Variable to store the last button state
unsigned long pressStartTime = 0; // Time when the button is pressed
unsigned long pressEndTime = 0;   // Time when the button is released
const int shortPressTime = 200;  // Threshold for a short press (dot)
const int longPressTime = 550;   // Threshold for a long press (dash)

// ************************************************
//                     SETUP()
// ************************************************
void setup() {
  // put your setup code here, to run once:

  pinMode(ledPinDot, OUTPUT);    // Initialize the Dot Pin / LED as output
  pinMode(ledPinDash, OUTPUT);   // Initialize the Dash Pin as output
  pinMode(buttonPin, INPUT);     // Initialize the button as input
  Serial.begin(9600);            // Start serial communication for debugging

}

// ************************************************
//                     LOOP()
// ************************************************
void loop() {
  // put your main code here, to run repeatedly:

 // Read the button state
  buttonState = digitalRead(buttonPin);

  // If button is pressed
  if (buttonState == HIGH && lastButtonState == LOW) {
    pressStartTime = millis();  // Record the time when the button was pressed
  }

  // If button is released
  if (buttonState == LOW && lastButtonState == HIGH) {
    pressEndTime = millis();  // Record the time when the button was released
    long pressDuration = pressEndTime - pressStartTime;
    Serial.print(pressDuration);

    // If it's a short press (dot)
    if (pressDuration < shortPressTime) {
      sendDot();
    }
    // If it's a long press (dash)
    else if (pressDuration >= shortPressTime && pressDuration < longPressTime) {
      sendDash();
    }
  }
  lastButtonState = buttonState;  // Update the last button state
  delay(50); 

}

// Function to send a dot (short flash)
void sendDot() {
  digitalWrite(ledPinDot, HIGH);  // Turn on LED
  delay(200);                  // LED on for 200ms
  digitalWrite(ledPinDot, LOW);   // Turn off LED
  delay(200);                  // Small delay between signals
  Serial.println(" - Dot");       // Print "Dot" to the serial monitor
}

// Function to send a dash (long flash)
void sendDash() {
  digitalWrite(ledPinDash, HIGH);  // Turn on LED
  delay(200);                  // LED on for 500ms
  digitalWrite(ledPinDash, LOW);   // Turn off LED
  delay(200);                  // Small delay between signals
  Serial.println(" - Dash");      // Print "Dash" to the serial monitor
}




// ************************************************
//                     Lesson Reference Code
// ************************************************

/*

Paste Reference Code Here

const int ledPin = 8;       // Pin for the LED
const int ledPinDash = 9;       // Pin for the LED
const int buttonPin = 2;    // Pin for the button
int buttonState = 0;        // Variable to store the current button state
int lastButtonState = 0;    // Variable to store the last button state
unsigned long pressStartTime = 0; // Time when the button is pressed
unsigned long pressEndTime = 0;   // Time when the button is released
const int shortPressTime = 200;  // Threshold for a short press (dot)
const int longPressTime = 550;   // Threshold for a long press (dash)

void setup() {
  pinMode(ledPin, OUTPUT);   // Initialize the LED as output
  pinMode(ledPinDash, OUTPUT);   // Initialize the LED as output
  pinMode(buttonPin, INPUT); // Initialize the button as input
  Serial.begin(9600);        // Start serial communication for debugging
}

void loop() {
  // Read the button state
  buttonState = digitalRead(buttonPin);

  // If button is pressed
  if (buttonState == HIGH && lastButtonState == LOW) {
    pressStartTime = millis();  // Record the time when the button was pressed
  }

  // If button is released
  if (buttonState == LOW && lastButtonState == HIGH) {
    pressEndTime = millis();  // Record the time when the button was released
    long pressDuration = pressEndTime - pressStartTime;
    Serial.print(pressDuration);

    // If it's a short press (dot)
    if (pressDuration < shortPressTime) {
      sendDot();
    }
    // If it's a long press (dash)
    else if (pressDuration >= shortPressTime && pressDuration < longPressTime) {
      sendDash();
    }
  }
  lastButtonState = buttonState;  // Update the last button state
  delay(50); 

}

// Function to send a dot (short flash)
void sendDot() {
  digitalWrite(ledPin, HIGH);  // Turn on LED
  delay(200);                  // LED on for 200ms
  digitalWrite(ledPin, LOW);   // Turn off LED
  delay(200);                  // Small delay between signals
  Serial.println(" - Dot");       // Print "Dot" to the serial monitor
}

// Function to send a dash (long flash)
void sendDash() {
  digitalWrite(ledPinDash, HIGH);  // Turn on LED
  delay(200);                  // LED on for 500ms
  digitalWrite(ledPinDash, LOW);   // Turn off LED
  delay(200);                  // Small delay between signals
  Serial.println(" - Dash");      // Print "Dash" to the serial monitor
}


*/