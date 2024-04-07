// Day 6 code...

int sensorPin = A0;  // select the "analog zero" input pin for probing the photoresistor
int onboardLED = 13; // select the pin for the HERO's built-in LED
int sensorValue = 0; // variable that we'll use to store the value of the reading from the sensor


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(onboardLED, OUTPUT);
  }

void loop() {
  // Pulde the builtin LED for a time determined by the sensor
  sensorValue = analogRead(sensorPin);
  digitalWrite(onboardLED, HIGH);
  delay(sensorValue);
  digitalWrite(onboardLED, LOW);
  delay(sensorValue);

  //read the analog sensor value and dend it to serial
  Serial.println(sensorValue);
  delay(sensorValue);
  
}
