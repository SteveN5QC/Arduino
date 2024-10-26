//Day 8 code...

int red = 11;  // these are the output pins for the three LED colors
int green = 10;
int blue = 9;


void setup() {
  // set our pins to drive the LEDS (runs once)

  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);
}

void RGB_color(int red_value, int green_value, int blue_value)
{
  // custom function to set three PWM color chanels to any given mixture

    analogWrite(red, red_value);
    analogWrite(green, green_value);
    analogWrite(blue, blue_value);
}


void loop() {
  // Cycle through several different color settings

  RGB_color(125, 0, 0); // Red
  delay(800);
  RGB_color(0, 125, 0); // Green
  delay(800);
  RGB_color(0, 0, 190); // Blue
  delay(800);
  RGB_color(128, 64, 0); // yellow
  delay(800);
  RGB_color(125, 0, 125); // Purple
  delay(800);
  RGB_color(255, 255, 255); // White
  delay(2000);  
  RGB_color(125, 0, 0); // Red
  delay(1000);
  RGB_color(0, 125, 0); // Green
  delay(1000);
  

}
