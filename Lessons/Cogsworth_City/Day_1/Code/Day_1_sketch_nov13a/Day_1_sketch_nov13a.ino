void setup() {
  pinMode(LED_BUILTIN, OUTPUT);  // sets the pin for the built in LED as output
}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH);  // turns the LED on
  delay(1000);                      // waits for a second
  digitalWrite(LED_BUILTIN, LOW);   // turns the LED off
  delay(1000);                      // waits for a second
}