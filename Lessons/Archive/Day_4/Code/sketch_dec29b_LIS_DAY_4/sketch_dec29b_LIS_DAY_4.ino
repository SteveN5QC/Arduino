int LED1 = 10;  //pins 10-12 are to be LED outputs
int LED2 = 11;
int LED3 = 12;

int Switch1 = 2;  //pin 2-4 are to be switch inputs
int Switch2 = 3;
int Switch3 = 4;


void setup() {
  //now setup our input and output pins accordingly
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(Switch1, INPUT);
  pinMode(Switch2, INPUT);
  pinMode(Switch3, INPUT);

}

void loop() {
  //now within loop() we'll take actions based on the status of the switches

  //testing...

  if (digitalRead(Switch1) == HIGH){  // check the status of switch #1
    digitalWrite(LED1, HIGH);  // turn LED1 ON
  }
  else{
    digitalWrite(LED1, LOW);  //turn LED1 OFF
  }

  if (digitalRead(Switch2) == HIGH){  // check the status of switch #2
    digitalWrite(LED2, HIGH);  // turn LED1 ON
  }
  else{
    digitalWrite(LED2, LOW);  //turn LED2 OFF
  }

    if (digitalRead(Switch3) == HIGH){  // check the status of switch #3
    digitalWrite(LED3, HIGH);  // turn LED3 ON
  }
  else{
    digitalWrite(LED3, LOW);  //turn LED3 OFF
  }
}
