/*
 * 30 Days - Lost in Space
 * Day 6 - Time to Fix the Battery
 * ADDING a Time Stapm
 *
 * Learn more at https://learn.inventr.io/adventure
 *
 * We will need to find an additional source of power as our battery will not last long
 * without some recharging.  We do have solar panels so let's work on how the HERO can
 * monitor the power coming from those panels using a "photo-resistor" to simulate the
 * variable power available to our Lander.
 *
 * Alex Eschenauer
 * David Schmidt
 * Greg Lyzenga
 */

/*
 * Arduino concepts introduced/documented in this lesson.
 * - unsigned int: A 16 bit value containing numbers from 0 to 65535
 * - Serial Monitor: Allows the HERO to display text in an Arduino IDE window.
 * - Serial.begin(): Used to initialize the Serial Monitor.
 * - Serial.print(): Display some text in the Arduino IDE Serial Monitor window.
 * - Serial.println(): Display test in the Serial Monitor followed by a newline.
 * - analogRead(): Read a value from an analog pin that is based on how much voltage is on the pin (0-5v)
 *
 * Parts and electronics concepts introduced in this lesson.
 * - Analog pins: Pins on the HERO that can read many different values instead of just HIGH/LOW.
 * - Photo Resistor: Changes it's resistance depending on how much light it senses.
 */

/* We start by including this line of code, which helps our HERO work properly with the Arduino program. */
#include "Arduino.h"

// Our photoresistor will give us a reading of the current light level on this analog pin
const byte PHOTORESISTOR_PIN = A0;  // we pick an analog pin (defined in Arduino.h)

// These two constants set the minimum and maximum delay times for oue blinking LED
// The type "unsigned int" represents numbers from 0 to 65535.  Another name you may
// see for this type is "uint16_t".  We need this since these delay values can be
// greater than the biggest number a byte can represent (255).
const unsigned int MIN_DELAY = 50;   // 50 ms shortest blink delay
const unsigned int MAX_DELAY = 500;  // 500 ms longest blink delay

// One time setup
void setup() {
  // We will blink our build in LED based on amount of light received from our photoresistor
  pinMode(LED_BUILTIN, OUTPUT);       // output since we will control the built in LED
  pinMode(PHOTORESISTOR_PIN, INPUT);  // input value from analog pin connected to photoresistor

  /*
   * To show you the exact value being read on the analog pin we will print the exact number
   * using our Arduino IDE's "Serial Monitor".  This is a window displayed under the sketch that
   * can display text sent to it from the HERO.
   *
   * The speed that this data is sent/received must match between the Arduino IDE and HERO.  We
   * configure this speed for the HERO to send data using the Serial.begin() function.  Throughout
   * this course we will use a typical value of 9600 "baud", which is 9,600 bit of information per
   * second.
   */
  Serial.begin(9600);  // This initializes the Serial Monitor and sets the speed to 9600 bits per second
}

// The loop() function is called over and over when sketch is run.
void loop() {
  /*
   * Each time through our loop() we will read the current value of our photoresistor.  When
   * the voltage goes up from more light we flash the built-in LED faster (with shorter blinks).
   *
   * The photoresistor will produce a voltage that is not a simple digitial (on/off, HIGH/LOW)
   * value.  Because of this we cannot use a digital pin on our HERO.  Luckily our HERO board
   * provides six "analog" pins, named A0-A5.
   *
   * These pins will convert a voltage from 0V to 5V to a number from 0 to 1023, giving us
   * a full range of values.  Because we are reading an analog value instead of a digital
   * value, we use the analogRead() function.
   *
   * Here we use the reading from the PHOTORESISTOR_PIN and modify how long we delay based on it.
   */
  unsigned int light_value = analogRead(PHOTORESISTOR_PIN);   // light value from 0 to 1024

  /*
   * Our HERO board doesn't have a text display, so the Arduino IDE has provided us a way to
   * for the HERO to send messages that are displayed in a window in the Arduino IDE.  To open
   * the Serial Monitor on the Arduino IDE you can select Tools/Serial Monitor from the Arduino
   * IDE menu, use the shortcut keys listed in the menu or click the "magnifying glass" icon in
   * the upper right of the IDE window.
   *
   * We initialized the Serial functions in setup and now we will use Serial.print() and
   * Serial.println() to send messages to the Arduino IDE Serial Monitor.  Both functions
   * take a single value which can be either a constant or a variable.  The only difference
   * between the two functions is that Serial.print() leaves the cursor at the end of the
   * current line.  Any additional output will be appended to the current line.  Serial.println()
   * prints the value and THEN adds a "newline", so that any following messages will appear
   * on the following line.
   */




  // now blink our built in LED using our delay_value.
  digitalWrite(LED_BUILTIN, HIGH);  // Turn on LED
  delay(delay_value);               // Leave on delay_value milliseconds
  digitalWrite(LED_BUILTIN, LOW);   // Turn off LED
  delay(delay_value);               // Leave off delay_value milliseconds
}