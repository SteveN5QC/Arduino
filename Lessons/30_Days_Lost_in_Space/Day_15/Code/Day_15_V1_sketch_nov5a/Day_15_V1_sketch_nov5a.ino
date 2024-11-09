// Define maximum and minimum PIN length
const int minPinLength = 4;
const int maxPinLength = 8;
const int maxAttempts = 5;

char currentPIN[maxPinLength + 1];  // Stores the active PIN
int attemptCount = 0;               // Track number of attempts

void setup() {
    Serial.begin(9600);             // Start serial communication
    pinMode(LED_BUILTIN, OUTPUT);   // Set up onboard LED for feedback

    // Prompt for initial user-defined PIN setup
    Serial.println("Set a new PIN (4-8 characters). End with #:");
    setupNewPIN();
}

void loop() {
    if (attemptCount >= maxAttempts) {
        Serial.println("Too many failed attempts. Access locked.");
        while (true); // Lock the system
    }

    Serial.println("Enter PIN:");
    if (validatePIN()) {
        Serial.println("Access Granted!");
        digitalWrite(LED_BUILTIN, HIGH); // Turn on LED for valid entry
        delay(1000);                      // Hold success for visibility
    } else {
        attemptCount++;
        Serial.print("Incorrect PIN. Attempts remaining: ");
        Serial.println(maxAttempts - attemptCount);
        digitalWrite(LED_BUILTIN, LOW);   // Turn off LED for invalid entry
        delay(1000);
    }
}

// Set up a new PIN with verification
void setupNewPIN() {
    char tempPIN[maxPinLength + 1];  // Temporary storage for first PIN entry

    // First entry of new PIN
    Serial.println("Enter new PIN:");
    if (getPINInput(tempPIN)) {
        Serial.println("Re-enter new PIN for verification:");
        
        // Second entry to confirm
        char verifyPIN[maxPinLength + 1];
        if (getPINInput(verifyPIN) && strcmp(tempPIN, verifyPIN) == 0) {
            strcpy(currentPIN, tempPIN);  // Set the new PIN
            Serial.println("New PIN set successfully!");
        } else {
            Serial.println("PINs did not match. Restart setup.");
            setupNewPIN(); // Retry setup if verification fails
        }
    }
}

// Get PIN input with "#" to end entry
bool getPINInput(char* pinBuffer) {
    int charIndex = 0;
    while (true) {
        if (Serial.available()) {
            char inputChar = Serial.read();

            // Check for end of entry with "#"
            if (inputChar == '#') {
                pinBuffer[charIndex] = '\0'; // End the PIN string
                if (charIndex >= minPinLength && charIndex <= maxPinLength) {
                    return true;
                } else {
                    Serial.println("Invalid PIN length. Try again.");
                    return false;  // Invalid length
                }
            }

            // Add character if within limits
            if (charIndex < maxPinLength) {
                pinBuffer[charIndex] = inputChar;
                Serial.print("*");  // Mask input with *
                charIndex++;
            }
        }
    }
}

// Validate entered PIN against currentPIN
bool validatePIN() {
    char enteredPIN[maxPinLength + 1];
    if (getPINInput(enteredPIN)) {
        return strcmp(enteredPIN, currentPIN) == 0;
    }
    return false;
}
