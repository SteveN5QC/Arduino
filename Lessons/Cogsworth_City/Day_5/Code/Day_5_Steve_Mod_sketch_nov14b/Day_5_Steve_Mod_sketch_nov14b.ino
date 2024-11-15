const int switchPin1 = 2;    // switc1 1 is connected to pin 2
const int switchPin3 = 3;    // Switch 3 is connected to pin 3
const int ledPin1 = 8;       // Led 1 is connected to pin 8
const int ledPin2 = 9;       // Led 2 is connected to pin 9

int switchState1 = 0;        // Variable to hold the state of switch 1
int lastSwitchState1 = 0;    // Previous state of switch 1

int switchState3 = 0;        // Variable to hold the state of switch 3
int lastSwitchState3 = 0;    // Previous state of switch 3

int ledState1 = LOW;         // Current state of LED 1 (initially off)
int ledState2 = LOW;         // Current state of LED 2 (initially off)

void setup() {
  pinMode(switchPin1, INPUT);
  pinMode(switchPin3, INPUT);
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
 
}

void loop() {
  // Read the state of switch 1
  switchState1 = digitalRead(switchPin1);


  // Toggle LED 1 on/off when switch goes to on
  if (switchState1 != lastSwitchState1)  {
    if (switchState1 == HIGH)  {
      ledState1 == !ledState1;  // Toggle LED state
      digitalWrite(ledPin1, ledState1);  //Set LED state
    }
    delay(50);  // Debounce delay
  }
  lastSwitchState1 = switchState1;  // Save the current state for the next iteration


    // Read the state of switch 3
  switchState3 = digitalRead(switchPin3);


  // Toggle LED 2 on/off when switch goes to on
  if (switchState3 != lastSwitchState3)  {
    if (switchState3 == HIGH)  {
      ledState2 == !ledState2;  // Toggle LED state
      digitalWrite(ledPin2, ledState2);  //Set LED state
    }
    delay(50);  // Debounce delay
  }
  lastSwitchState3 = switchState3;  // Save the current state for the next iteration

}

