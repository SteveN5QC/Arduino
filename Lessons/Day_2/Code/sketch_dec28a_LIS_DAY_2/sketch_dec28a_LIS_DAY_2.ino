int Light = 12 ;  //HERO board pin 12

void setup() {
  // initialize the HERO...
  // initialize a digital pin as an output, then set its value to HIGH (5 volts)
  pinMode(Light, OUTPUT);
  digitalWrite(Light, LOW);
  

}

void loop() {
  // the code placed here will run repeatedly until the HERO is turned off:
  digitalWrite(Light, LOW);
  delay(2000);
  digitalWrite(Light, HIGH);
  delay(200);
}
