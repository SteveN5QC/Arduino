#define LED_1 13
#define LED_2 12
#define LED_3 11
#define LED_4 10
#define BUZZER 3 // The speaker enable
#define POTENTIOMETER A0 // The analog input for the potentiometer
#define BUTTON_1 A1 // The input pushbuttons
#define BUTTON_2 A2
#define BUTTON_3 A3
#define DISP_LATCH 4 // The 3 pins that control the display
#define DISP_CLK 7
#define DISP_DATA 8
 
void setup() {
pinMode(BUTTON_1, INPUT); //set the button pin as INPUT
pinMode(BUTTON_2, INPUT); //set the button pin as INPUT
pinMode(BUTTON_3, INPUT); //set the button pin as INPUT
pinMode(POTENTIOMETER, INPUT); //set the button pin as INPUT
pinMode(LED_4, OUTPUT); //set the LED pin as OUTPUT
pinMode(LED_3, OUTPUT); //set the LED pin as OUTPUT
pinMode(LED_2, OUTPUT); //set the LED pin as OUTPUT
pinMode(LED_1, OUTPUT); //set the LED pin as OUTPUT
pinMode(BUZZER, OUTPUT); //set the LED pin as OUTPUT
digitalWrite(LED_1, HIGH); //write 1 or HIGH to led pin
digitalWrite(LED_2, HIGH); //write 1 or HIGH to led pin
digitalWrite(LED_3, HIGH); //write 1 or HIGH to led pin
digitalWrite(LED_4, HIGH); //write 1 or HIGH to led pin
digitalWrite(BUZZER, HIGH); //write 1 or HIGH to led pin
 
Serial.begin(9600);
}
 
 
void loop() {
 
//Button 1
if(digitalRead(BUTTON_1) == 0){
Serial.println("Button 1 pressed");
digitalWrite(LED_1, LOW);
}
else{
digitalWrite(LED_1, HIGH);
}
 
//Button 2
if(digitalRead(BUTTON_2) == 0){
Serial.println("Button 2 pressed");
digitalWrite(LED_2, LOW);
}
else{
digitalWrite(LED_2, HIGH);
}
 
//Button 3
if(digitalRead(BUTTON_3) == 0){
Serial.println("Button 3 pressed");
digitalWrite(LED_3, LOW);
}
else {
digitalWrite(LED_3, HIGH);
}
 
//Slight Delay for Serial Spam
delay(100);
} 