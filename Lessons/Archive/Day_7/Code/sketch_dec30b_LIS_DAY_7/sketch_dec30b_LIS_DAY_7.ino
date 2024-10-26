
// Day 7 code...

int sensorPin = A0;  // select the *analog zero* input pin for probing the photoresistor
int onboardLED = 13;  // select the pin for the HERO's built in LED
int sensorValue = 0;  // variable that we'll use to store the value from the sensor
unsigned int batteryCapacity = 50000;
unsigned int batteryLevel = 0;
unsigned int ticks = 0;
unsigned int wait = 100;
double PercentFull;


void setup() {
  // put your setup code here, to run once:
 
 pinMode(onboardLED, OUTPUT);
 Serial.begin(9600);
}

void PrintBatteryPercentage() {
// print the elapsed time
  Serial.print(ticks);
  Serial.print(" ms   charge at ");

  // convert the integers to decimal numbers, divide them and print...
    PercentFull=100*((double)batteryLevel / (double)batteryCapacity);
    Serial.print(PercentFull);

  // print a percent character and Line return...
    Serial.println("%");

    
}

  
void loop() {
  // put your main code here, to run repeatedly:

  sensorValue = analogRead(sensorPin);  // read the value from the sensor
  batteryLevel += sensorValue;
  ticks += wait;

  if(batteryLevel >= batteryCapacity) {
    Serial.print(ticks);
    Serial.print(" ms    ");
    Serial.println("FULLY CHARGED");
    batteryLevel = batteryCapacity;  // to prevent integer from continuing to increase
    ticks = 0;
    delay(20000);    // Long pause
  }
  else  {
    PrintBatteryPercentage();
  }

  delay(wait);
  

}
