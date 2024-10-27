const int ledPin = 9;       // LED connected to digital pin 9
const int switchPin = 2;    // DIP switch connected to digital pin 2
int switchState = 0;        // Variable for reading the switch status

void setup() {
    pinMode(ledPin, OUTPUT);    // Set the LED pin as output
    pinMode(switchPin, INPUT);  // Set the switch pin as input
}

void loop() {
    switchState = digitalRead(switchPin);  // Read the state of the switch
    
    if (switchState == HIGH) {
        digitalWrite(ledPin, HIGH);  // Turn LED on if switch is on
    } else {
        digitalWrite(ledPin, LOW);   // Turn LED off if switch is off
    }
}
