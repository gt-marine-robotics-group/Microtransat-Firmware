#ifndef BLINK_HPP
#define BLINK_HPP

//External imports
#include <Arduino.h>

void setup() {
    // Initialize the built-in LED pin as an output
    pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
    // Turn the LED on
    digitalWrite(LED_BUILTIN, HIGH);
    // Wait for 1000 milliseconds (1 second)
    delay(1000);
    // Turn the LED off
    digitalWrite(LED_BUILTIN, LOW); 
    // Wait for 1000 milliseconds (1 second)
    delay(1000);
}

#endif

