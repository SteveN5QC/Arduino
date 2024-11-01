// Pin definitions for RGB LED
const int redPin = 11;
const int greenPin = 10;
const int bluePin = 9;

// Simulation constants
const int totalStepsForward = 10;
const int maxLeftSteps = 3;
const int maxRightSteps = 3;
const int simulations = 100;

// Outcome counters
int fellLeftCount = 0;
int fellRightCount = 0;
int backedOffCount = 0;
int successCount = 0;

// Setup and initialize
void setup() {
    Serial.begin(9600);
    randomSeed(analogRead(A2)); // Seed for randomness

    pinMode(redPin, OUTPUT);
    pinMode(greenPin, OUTPUT);
    pinMode(bluePin, OUTPUT);
}

// Main loop
void loop() {
    for (int i = 0; i < simulations; i++) {
        runSimulation();
    }
    
    // Print results after all simulations
    Serial.print("Fell off left: ");
    Serial.println(fellLeftCount);
    Serial.print("Fell off right: ");
    Serial.println(fellRightCount);
    Serial.print("Backed off: ");
    Serial.println(backedOffCount);
    Serial.print("Successful walks: ");
    Serial.println(successCount);

    // Stop the program after displaying results
    while (true);
}

// Run a single simulation of the pirate's walk
void runSimulation() {
    int position = 0; // Horizontal position: -3 = left edge, 0 = center, 3 = right edge
    int stepsForward = 0;

    while (stepsForward < totalStepsForward) {
        float move = random(0, 100) / 100.0;

        if (move < 0.4) {
            stepsForward++; // Move forward
        } else if (move < 0.65) {
            position--; // Move left
        } else if (move < 0.9) {
            position++; // Move right
        } else {
            stepsForward--; // Move backward
        }

        // Check boundaries
        if (position < -maxLeftSteps) {
            fellLeftCount++;
            signalFellLeft();
            return;
        } else if (position > maxRightSteps) {
            fellRightCount++;
            signalFellRight();
            return;
        } else if (stepsForward < 0) {
            backedOffCount++;
            signalBackedOff();
            return;
        }
    }

    // If 10 steps forward were completed
    successCount++;
    signalSuccess();
}

// LED Signals for each outcome

void signalFellLeft() {
    signalMorse("... --- ...   .-.. .-.. .-.."); // "SOS LLL"
}

void signalFellRight() {
    signalMorse("... --- ...   .-. .-. .-."); // "SOS RRR"
}

void signalBackedOff() {
    setColor(redPin);
    delay(1000); // Red LED for 1 second
    setColor(0); // Turn off LED
}

void signalSuccess() {
    signalMorse("... .... .- ...- .   .- -. -..   .-   .... .- .. .-. -.-. ..- -   ..-. --- .-."); // "shave and a haircut 2 bits"
}

// Morse code helper
void signalMorse(String morse) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < morse.length(); j++) {
            if (morse[j] == '.') {
                setColor(bluePin);
                delay(120); // Short blink
            } else if (morse[j] == '-') {
                setColor(bluePin);
                delay(360); // Long blink
            } else {
                setColor(0); // Turn off LED for spaces
            }
            delay(120); // Delay between signals
        }
        delay(300); // Pause between repeats
    }
    setColor(0); // Turn off LED
}

// Set LED color function
void setColor(int pin) {
    digitalWrite(redPin, LOW);
    digitalWrite(greenPin, LOW);
    digitalWrite(bluePin, LOW);
    if (pin != 0) digitalWrite(pin, HIGH);
}
