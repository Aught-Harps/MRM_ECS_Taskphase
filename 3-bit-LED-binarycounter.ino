// Define the pins for LEDs and the pushbutton
const int ledPins[] = {5,6,7};
const int buttonPin = 11;

int count = 0; // Variable to hold the count
int buttonState = LOW; // Variable to store the state of the button
int lastButtonState = LOW; // Variable to store the previous state of the button
unsigned long lastDebounceTime = 0; // Variable to store the last time the button was pressed
unsigned long debounceDelay = 50; // Debounce delay time in milliseconds

void setup() {
  // Initialize LED pins as OUTPUT
  for (int i = 0; i < 3; i++) {
    pinMode(ledPins[i], OUTPUT);
  }

  // Initialize button pin as INPUT
  pinMode(buttonPin, INPUT);
}

void loop() {
  int reading = digitalRead(buttonPin); // Read the current state of the button

  // Check for button state change with debounce
  if (reading != lastButtonState) {
    lastDebounceTime = millis(); // Reset debounce time
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;

      if (buttonState == HIGH) {
        count = (count + 1) % 8; // Increment count and reset to 0 after 7 (3-bit binary counter)
        updateLeds(); // Update LED display based on the count
      }
    }
  }

  // Save the current state of the button for the next iteration
  lastButtonState = reading;
}

// Function to update LEDs based on the count
void updateLeds() {
  for (int i = 0; i < 3; i++) {
    digitalWrite(ledPins[i], bitRead(count, i));
  }
}
