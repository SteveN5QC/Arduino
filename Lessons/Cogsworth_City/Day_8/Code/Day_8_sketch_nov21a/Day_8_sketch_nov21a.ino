/*
 * Steve's Template
 * General Commentst and Logic Narrative
 *
 * Pin Assigmnent Chart
 * 
 * A0 – Photo Resister   -- const int photoPin = A0;   // the photoresistor is connected is connected to Pin A0
 * 10 – Red LED  -- const int redLedPin = 10;  // the Red LED is connected to Pin 10
 * 9 – Blue LED  -- const int blueLedPin = 9;  // the Red LED is connected to Pin 9
 * 7 – Fork -- const int forkPin = 7;  // the firk is connected to Pin 7
 * 3 – Red Button -- const int redbuttonPin = 3;  // the Red button is connected to Pin 3
 * 2 – Blue Button -- const int blueredbuttonPin = 2;  // the Red button is connected to Pin 2


 * Variable List
 * 
 * 
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

const int photoPin = A0;          // the photoresistor is connected is connected to Pin A0
const int redLedPin = 10;         // the Red LED is connected to Pin 10
const int blueLedPin = 9;         // the Red LED is connected to Pin 9
const int forkPin = 7;            // the firk is connected to Pin 7
const int redbuttonPin = 3;       // the Red button is connected to Pin 3
const int bluebuttonPin = 2;   // the Red button is connected to Pin 2

int redbuttonState = 0;           // variable for reading the Red button status
int bluebuttonState = 0;          // variable for reading the Blue button status
int forkState = 0;                // variable for reading the fork status
int photoValue = 0;               // variable for reading the photoresistor value

// ************************************************
//                     SETUP()
// ************************************************
void setup() {
  // put your setup code here, to run once:
  pinMode(redbuttonPin, INPUT);   // initialize the Red button pin as an input
  pinMode(bluebuttonPin, INPUT);  // initialize the Blue button pin as an input
  pinMode(redLedPin, OUTPUT);     // initialize the Red LED pin as an output
  pinMode(blueLedPin, OUTPUT);   // initialize the Blue LED pin as an output
  pinMode(forkPin, INPUT);        // initialize the fork pin as an input
  pinMode(photoPin, INPUT);       // initialize the photoresistor pin as an input
  Serial.begin(9600);             // begin serial communication for debugging

}

// ************************************************
//                     LOOP()
// ************************************************
void loop() {
  // put your main code here, to run repeatedly:

  redbuttonState = digitalRead(redbuttonPin);    // read the state of the Red button
  bluebuttonState = digitalRead(bluebuttonPin);  // read the state of the Blue button
  forkState = digitalRead(forkPin);              // read the state of the fork
  photoValue = analogRead(photoPin);             // read the value from the photoresistor
 
  if (redbuttonState == HIGH && forkState == HIGH) {
    int brightness = map(photoValue, 0, 1023, 0, 255);  // map the photoresistor value to a brightness level
    analogWrite(redLedPin, brightness);                 // adjust Red LED brightness based on light level
    Serial.println("Red button pressed and fork touched! Red LED  on with brightness adjusted.");
  } else {
    digitalWrite(redLedPin, LOW);                      // turn Red LED off
  }
 
  if (bluebuttonState == HIGH && forkState == HIGH) {
    int brightness = map(photoValue, 0, 1023, 0, 255);  // map the photoresistor value to a brightness level
    analogWrite(blueLedPin, brightness);                // adjust Blue LED brightness based on light level
    Serial.println("Blue button pressed and fork touched! Blue LED  on with brightness adjusted.");
  } else {
    digitalWrite(blueLedPin, LOW);                      // turn Blue LED off
  }
 
  delay(100);  // wait for a short period before repeating the loop

}


// ************************************************
//                     Lesson Reference Code
// ************************************************

/*

const int buttonPin1 = 2;  // the pin where the first button is connected
const int buttonPin2 = 3;  // the pin where the second button is connected
const int ledPin1 = 9;     // the pin where the first LED is connected
const int ledPin2 = 10;     // the pin where the second LED is connected
const int forkPin = 7;     // the pin where the fork is connected
const int photoPin = A0;   // the pin where the photoresistor is connected
 
int buttonState1 = 0;      // variable for reading the first button status
int buttonState2 = 0;      // variable for reading the second button status
int forkState = 0;         // variable for reading the fork status
int photoValue = 0;        // variable for reading the photoresistor value
 
void setup() {
  pinMode(buttonPin1, INPUT);  // initialize the first button pin as an input
  pinMode(buttonPin2, INPUT);  // initialize the second button pin as an input
  pinMode(ledPin1, OUTPUT);    // initialize the first LED pin as an output
  pinMode(ledPin2, OUTPUT);    // initialize the second LED pin as an output
  pinMode(forkPin, INPUT);     // initialize the fork pin as an input
  pinMode(photoPin, INPUT);    // initialize the photoresistor pin as an input
  Serial.begin(9600);          // begin serial communication for debugging
}
 
void loop() {
  buttonState1 = digitalRead(buttonPin1);  // read the state of the first button
  buttonState2 = digitalRead(buttonPin2);  // read the state of the second button
  forkState = digitalRead(forkPin);        // read the state of the fork
  photoValue = analogRead(photoPin);       // read the value from the photoresistor
 
  if (buttonState1 == HIGH && forkState == HIGH) {
    int brightness = map(photoValue, 0, 1023, 0, 255);  // map the photoresistor value to a brightness level
    analogWrite(ledPin1, brightness);  // adjust first LED brightness based on light level
    Serial.println("First button pressed and fork touched! LED 1 on with brightness adjusted.");
  } else {
    digitalWrite(ledPin1, LOW);    // turn first LED off
  }
 
  if (buttonState2 == HIGH && forkState == HIGH) {
    int brightness = map(photoValue, 0, 1023, 0, 255);  // map the photoresistor value to a brightness level
    analogWrite(ledPin2, brightness);  // adjust second LED brightness based on light level
    Serial.println("Second button pressed and fork touched! LED 2 on with brightness adjusted.");
  } else {
    digitalWrite(ledPin2, LOW);    // turn second LED off
  }
 
  delay(100);  // wait for a short period before repeating the loop
}

*/