#include <Arduino.h>

// put function declarations here:

const int potPin = 32; // Pin where the potentiometer is connected
const int ledPin = 4;  // Pin where the LED is connected
const int buttonPin = 15; // Pin where the button is connected

int potValue = 0; // Variable to store the potentiometer value
int buttonState = 0; // Variable to store the button state
int lastButtonState = HIGH; // Variable to store the last button state
bool ledOn = false; // Variable to store the LED state

void setup() {
  // put your setup code here, to run once:
    pinMode(potPin, INPUT);
    pinMode(ledPin, OUTPUT);
    pinMode(buttonPin, INPUT_PULLUP); // Use internal pull-up resistor
    Serial.begin(115200); // Initialize serial communication
}

void loop() {
  // put your main code here, to run repeatedly:

   potValue = analogRead(potPin); // Read the potentiometer value
   buttonState = digitalRead(buttonPin); // Read the button state

   if (buttonState == LOW && lastButtonState == HIGH) { // If button is pressed
    ledOn = !ledOn; // Toggle the LED state
   }
   lastButtonState = buttonState; // Update the last button state

   if (ledOn) {
    int ledBrightness = map(potValue, 0, 4095, 0, 255); // Map potentiometer value to LED brightness
    analogWrite(ledPin, ledBrightness); // Set LED brightness
   } else {
    analogWrite(ledPin, 0); // Turn off the LED
   }

    Serial.print("Potentiometer Value: ");
    Serial.print(potValue);
    Serial.print(" | Button State: ");
    Serial.print(buttonState);
    Serial.print(" | LED State: ");
    Serial.println(ledOn);

    delay(100); // Small delay for stability
}