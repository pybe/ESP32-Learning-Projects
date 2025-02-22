#include <Arduino.h>

// put function declarations here:

const int potPin = 32; // Pin where the potentiometer is connected
const int ledPin = 4;  // Pin where the LED is connected
const int buttonPin = 15; // Pin where the button is connected

int potValue = 0; // Variable to store the potentiometer value
int buttonState = 0; // Variable to store the button state


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

   if (buttonState == LOW) { // If button is pressed
    int ledBrightness = map(potValue, 0, 4095, 0, 255); // Map potentiometer value to LED brightness
    analogWrite(ledPin, ledBrightness); // Set LED brightness
    } else {
      analogWrite(ledPin, 0); // Turn off the LED
    }

    Serial.print("Potentiometer Value: ");
    Serial.print(potValue);
    Serial.print(" | Button State: ");
    Serial.println(buttonState);

    delay(100); // Small delay for stability
}




