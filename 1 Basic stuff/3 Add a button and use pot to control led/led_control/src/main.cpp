#include <Arduino.h>

// Pin definitions
enum Pins {
    POT_PIN = 32,
    LED_PIN = 4,
    BUTTON_PIN = 15
};

// Constants
constexpr int POT_MAX_VALUE = 4095;
constexpr int PWM_MAX_VALUE = 255;
constexpr unsigned long DEBOUNCE_DELAY = 50; // milliseconds

class Button {
private:
    const uint8_t pin;
    bool lastState;
    bool state;
    unsigned long lastDebounceTime;

public:
    Button(uint8_t buttonPin) : 
        pin(buttonPin), 
        lastState(HIGH), 
        state(HIGH), 
        lastDebounceTime(0) {}

    void begin() {
        pinMode(pin, INPUT_PULLUP);
    }

    bool wasPressed() {
        bool currentReading = digitalRead(pin);
        
        if (currentReading != lastState) {
            lastDebounceTime = millis();  // Reset timer when state changes
        }

        if ((millis() - lastDebounceTime) > DEBOUNCE_DELAY) {  // Wait 50ms
            if (currentReading != state) {  // If state is still different
                state = currentReading;      // Accept the new state
                if (state == LOW) {          // If button is pressed (LOW due to INPUT_PULLUP)
                    return true;
                }
            }
        }

        lastState = currentReading;
        return false;
    }
};

// Global variables
Button button(BUTTON_PIN);
bool ledOn = false;

void setup() {
    pinMode(POT_PIN, INPUT);
    pinMode(LED_PIN, OUTPUT);
    button.begin();
    Serial.begin(115200);
}

void loop() {
    // Read and constrain potentiometer value
    int potValue = constrain(analogRead(POT_PIN), 0, POT_MAX_VALUE);
    
    // Handle button press with debouncing
    if (button.wasPressed()) {
        ledOn = !ledOn;
    }

    // Update LED
    if (ledOn) {
        int ledBrightness = map(potValue, 0, POT_MAX_VALUE, 0, PWM_MAX_VALUE);
        analogWrite(LED_PIN, ledBrightness);
    } else {
        analogWrite(LED_PIN, 0);
    }

    // Debug output
    Serial.print("Potentiometer Value: ");
    Serial.print(potValue);
    Serial.print(" | LED State: ");
    Serial.println(ledOn);

    delay(10); // Reduced delay since we have proper debouncing
}