const int Dip_Switch_Pin = 2;  // the number of the pin connected to Dip Switch 1
const int ledPin = 13;  // the number of the LED pin

int switchState = 0;  // the variable for reading the Dip Switch status




void setup() {
  pinMode(Dip_Switch_Pin, INPUT);   // initialize the Dip Switch Pin as an input
  pinMode(ledPin, OUTPUT);  // Initialize the LED Pin as an output

}

void loop() {
switchState = digitalRead(Dip_Switch_Pin);  // Read the state AKA position of the Dip Switch

if (switchState == HIGH)  {    // check if the switch is on
  digitalWrite(ledPin, HIGH);   // turn the LED on
} else {
  digitalWrite(ledPin, LOW);  // turn LED off
}


}


