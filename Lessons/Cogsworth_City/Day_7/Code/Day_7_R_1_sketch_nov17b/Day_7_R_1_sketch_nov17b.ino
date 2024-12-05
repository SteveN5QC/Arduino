/*
 * R1 -- Change Green LED to Pin 6 to allow for Pulse Width Modulation (PWM)
 * 
 * Steve's Cogsworth City -- Day 7
 * General Comments and Logic Narrative
 *
 * Pin Assigmnent Chart
 * 
 * A0 – Photoresistor --> const int photoresPin = A0;   // The Photo Resister is wired to Pin A0
 * 2 – Green Button --> const int greenbuttonPin = 2;   // The Green Button is wired to Pin 2
 * 3 – Blue Button --> const int bluebuttonPin = 3;   // The Blue Button is wired to Pin 3
 * 4 – Orange / Red Button --> const int redbuttonPin = 4;   // The Red Button is wired to Pin 4
 * 
 * 6 – Green LED  --> const int greenLEDPin = 8;   // The Green LED is wired to Pin 6 -- R1 -- WAS: Pin 8
 * 9 – Blue LED  --> const int blueLEDPin = 9;   // The Blue LED is wired to Pin 9
 * 10 – Red LED  --> const int redLEDPin = 10;   // The Red LED is wired to Pin 10
 *
 *
 * 
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

const int photoresPin = A0;     // The Photo Resister is wired to Pin A0
const int greenbuttonPin = 2;   // The Green Button is wired to Pin 2
const int bluebuttonPin = 3;    // The Blue Button is wired to Pin 3
const int redbuttonPin = 4;     // The Red Button is wired to Pin 4

const int greenLEDPin = 6;      // The Green LED is wired to Pin 6 -- R1:  WAS Pin 8
const int blueLEDPin = 9;       // The Blue LED is wired to Pin 9
const int redLEDPin = 10;       // The Red LED is wired to Pin 10

int greenbuttonState = 0;       // variable for reading the green button status
int bluebuttonState = 0;        // variable for reading the blue button status
int redbuttonState = 0;         // variable for reading the red button status
int ledBrightness = 0;          // variable for LED brightness based on photoresistor

// ************************************************
//                     SETUP()
// ************************************************
void setup() {
  // put your setup code here, to run once:
  pinMode(greenbuttonPin, INPUT);  // initialize the Green button pin as an input
  pinMode(bluebuttonPin, INPUT);   // initialize the Blue button pin as an input
  pinMode(redbuttonPin, INPUT);    // initialize the Red button pin as an input
  pinMode(greenLEDPin, OUTPUT);    // initialize the Green LED pin as an output
  pinMode(blueLEDPin, OUTPUT);     // initialize the Blue LED pin as an output
  pinMode(redLEDPin, OUTPUT);      // initialize the Red LED pin as an output
  Serial.begin(9600);              // begin serial communication for debugging

}

// ************************************************
//                     LOOP()
// ************************************************
void loop() {
  // put your main code here, to run repeatedly:
    // read the state of the pushbutton values:
  greenbuttonState = digitalRead(greenbuttonPin);
  bluebuttonState = digitalRead(bluebuttonPin);
  redbuttonState = digitalRead(redbuttonPin);
 
  // read the photoresistor value and map it to LED brightness:
  int sensorValue = analogRead(photoresPin);
  ledBrightness = map(sensorValue, 0, 1023, 0, 255);
 
  // check if the pushbuttons are pressed. If they are, the buttonState is HIGH:
  if (greenbuttonState == HIGH) {
    analogWrite(greenLEDPin, ledBrightness);  // adjust LED brightness based on light level
  } else {
    analogWrite(greenLEDPin, 0);   // turn LED off
  }
 
  if (bluebuttonState == HIGH) {
    analogWrite(blueLEDPin, ledBrightness);  // adjust LED brightness based on light level
  } else {
    analogWrite(blueLEDPin, 0);   // turn LED off
  }
 
  if (redbuttonState == HIGH) {
    analogWrite(redLEDPin, ledBrightness);  // adjust LED brightness based on light level
  } else {
    analogWrite(redLEDPin, 0);   // turn LED off
  }
 
  // print the sensor values to the serial monitor for debugging
  Serial.print("Light level: ");
  Serial.println(sensorValue);
  Serial.print("LED brightness: ");
  Serial.println(ledBrightness);
 
  delay(100);  // wait for a short period before repeating the loop

}


// ************************************************
//                     Lesson Reference Code
// ************************************************

/*
const int buttonPin1 = 2;   // the number of the first button pin
const int buttonPin2 = 3;   // the number of the second button pin
const int buttonPin3 = 4;   // the number of the third button pin
const int ledPin1 = 8;      // the number of the first LED pin
const int ledPin2 = 9;      // the number of the second LED pin
const int ledPin3 = 10;     // the number of the third LED pin
const int photoPin = A0;    // the pin where the photoresistor is connected
 
int buttonState1 = 0;       // variable for reading the first button status
int buttonState2 = 0;       // variable for reading the second button status
int buttonState3 = 0;       // variable for reading the third button status
int ledBrightness = 0;      // variable for LED brightness based on photoresistor
 
void setup() {
  pinMode(buttonPin1, INPUT);  // initialize the first button pin as an input
  pinMode(buttonPin2, INPUT);  // initialize the second button pin as an input
  pinMode(buttonPin3, INPUT);  // initialize the third button pin as an input
  pinMode(ledPin1, OUTPUT);    // initialize the first LED pin as an output
  pinMode(ledPin2, OUTPUT);    // initialize the second LED pin as an output
  pinMode(ledPin3, OUTPUT);    // initialize the third LED pin as an output
  Serial.begin(9600);          // begin serial communication for debugging
}
 
void loop() {
  // read the state of the pushbutton values:
  buttonState1 = digitalRead(buttonPin1);
  buttonState2 = digitalRead(buttonPin2);
  buttonState3 = digitalRead(buttonPin3);
 
  // read the photoresistor value and map it to LED brightness:
  int sensorValue = analogRead(photoPin);
  ledBrightness = map(sensorValue, 0, 1023, 0, 255);
 
  // check if the pushbuttons are pressed. If they are, the buttonState is HIGH:
  if (buttonState1 == HIGH) {
    analogWrite(ledPin1, ledBrightness);  // adjust LED brightness based on light level
  } else {
    analogWrite(ledPin1, 0);   // turn LED off
  }
 
  if (buttonState2 == HIGH) {
    analogWrite(ledPin2, ledBrightness);  // adjust LED brightness based on light level
  } else {
    analogWrite(ledPin2, 0);   // turn LED off
  }
 
  if (buttonState3 == HIGH) {
    analogWrite(ledPin3, ledBrightness);  // adjust LED brightness based on light level
  } else {
    analogWrite(ledPin3, 0);   // turn LED off
  }
 
  // print the sensor values to the serial monitor for debugging
  Serial.print("Light level: ");
  Serial.println(sensorValue);
  Serial.print("LED brightness: ");
  Serial.println(ledBrightness);
 
  delay(100);  // wait for a short period before repeating the loop
}

*/