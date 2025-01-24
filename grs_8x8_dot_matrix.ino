// Include the library
#include "LedControl.h"

// Initialize the LedControl object
// Pin 12: DataIn, Pin 10: CLK, Pin 11: LOAD(CS), 1: Number of MAX72XX devices
LedControl lc = LedControl(12, 10, 11, 1);

// Delay time for switching between characters
unsigned long delaytime = 1500;

void setup() {
  // Wake up the MAX72XX from power-saving mode
  lc.shutdown(0, false);
  // Set brightness to medium
  lc.setIntensity(0, 8);
  // Clear the display
  lc.clearDisplay(0);
}

// Function to display GRS on the 8x8 dot matrix
void displayGRS() {
  // Define the 8x8 patterns for G, R, and S
  byte G[8] = {B00111100, B01100110, B01000000, B01001110, B01000110, B01100110, B00111100, B00000000};
  byte R[8] = {B01111100, B00100110, B00100110, B01111100, B00110000, B00101000, B01100100, B00000000};
  byte S[8] = {B00111110, B01100000, B01100000, B00111100, B00000110, B00000110, B01111100, B00000000};

  // Display G
  for (int row = 0; row < 8; row++) {
    lc.setRow(0, row, G[row]);
  }
  delay(delaytime);
  lc.clearDisplay(0);

  // Display R
  for (int row = 0; row < 8; row++) {
    lc.setRow(0, row, R[row]);
  }
  delay(delaytime);
  lc.clearDisplay(0);

  // Display S
  for (int row = 0; row < 8; row++) {
    lc.setRow(0, row, S[row]);
  }
  delay(delaytime);
  lc.clearDisplay(0);
}

void loop() {
  // Continuously display GRS
  displayGRS();
}
