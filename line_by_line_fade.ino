#include "LedControl.h"

// Pin connections for the MAX7219
const int dataPin = 12;
const int clkPin = 11;
const int csPin = 10;

// Create an instance of the LedControl library
LedControl lc = LedControl(dataPin, clkPin, csPin, 1); // Only one MAX7219 is used

void setup() {
    lc.shutdown(0, false);  // Wake up the MAX7219
    lc.setIntensity(0, 0);  // Set initial brightness to 0
    lc.clearDisplay(0);     // Clear the display
}

void loop() {
    fadeRows();
    delay(100); // Wait for a second before starting again
    lc.clearDisplay(0); // Clear the display before the next fade
}

void fadeRows() {
    for (int row = 0; row < 8; row++) {
        // Gradually turn on the LEDs in the current row
        for (int intensity = 0; intensity < 16; intensity++) {
            lc.setIntensity(0, intensity);
            lc.setRow(0, row, 0xFF); // Turn on all LEDs in the current row
            delay(350); // Adjust this delay for the desired fade speed
        }
        // Gradually turn off the LEDs in the current row
        for (int intensity = 15; intensity >= 0; intensity--) {
            lc.setIntensity(0, intensity);
            lc.setRow(0, row, 0xFF); // Keep all LEDs on in the current row
            delay(350); // Adjust this delay for the desired fade speed
        }
        lc.setRow(0, row, 0x00); // Turn off all LEDs in the current row
    }
}
