const int photoPin = A0;    // the pin where the photoresistor is connected
const int ledPin = 13;      // the pin where the LED is connected

int lightLevel = 0;         // variable to store the light level
int threshold = 100;        // threshold for light change detection


void setup() {
  pinMode(ledPin, OUTPUT);  // initializes the LED pin as an output

}

void loop() {
  lightLevel = analogRead(photoPin);   // read the light level from the photoresister

  if (lightLevel < threshold) {        // if the light level is below the threshold
  digitalWrite(ledPin,  HIGH);
  
  } else {
    digitalWrite(ledPin, LOW);         //turn off the Led
  }
  delay(100);                          // small delay to stabilize the readings
}
