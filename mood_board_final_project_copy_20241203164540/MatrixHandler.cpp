#include "MatrixHandler.h"
#include "Globals.h"


int wave[16]; //wave height array


void matrixSetup() {
    matrix.begin();
    matrix.setTextWrap(false);
    matrix.setBrightness(255);
}

float getAverage(int arr[], int count) {
  if (count == 0) return 0; 
  long sum = 0;
  for (int i = 0; i < count; i++) {
    sum += arr[i];
  }

  return (float)sum / count; 
}

void drawWave(int soundValue, int soundValues[], int filled) {
    // mappign the sound value to wave height
    int newHeight = map(soundValue, 50, 600, 0, 16);

    for (int i = 0; i < 15; i++) { // shiting wave to left
    wave[i] = wave[i + 1];
    }

    wave[15] = newHeight; // add new wave height to the end of the array

    // Draw the wave
    matrix.fillScreen(0); 
    for (int x = 0; x < 16; x++) {
      int height = wave[x];
      for (int y = 0; y < height; y++) {
        // Draw a vertical column of pixels for the wave
        matrix.drawPixel(x, 16 - y - 1, matrix.Color(map(soundValue, 0, 600, 0, 255), map(soundValue, 0, 600, 0, 127), map(soundValue, 0, 600, 255, 0)));
      }

      for (int y = height; y < 16; y++) {
          matrix.drawPixel(x, 16 - y - 1,
            matrix.Color(map(getAverage(soundValues, filled), 0, 600, 255, 0), map(getAverage(soundValues, filled), 0, 600, 255, 0), map(getAverage(soundValues, filled), 0, 600, 255, 0)) // Example: Fill with blue
          );
        }
    }

    matrix.show();
    delay(100);
}

void drawWaveParty(int soundValue, unsigned long currTime, unsigned long &lastChangeColorTime) {
  // mapping sound val to wave height
  int newHeight = map(soundValue, 0, 1023, 0, 16);

  for (int i = 0; i < 15; i++) { // shifting wave to the left
    wave[i] = wave[i + 1];
  }

  wave[15] = newHeight; // add new wave height to the end of the array

  // Declare static color variables to persist across function calls
  static int red = 200, green = 200, blue = 200;

  // Change color every 2 seconds
  if (millis() - lastChangeColorTime > 2000) {
    red = random(0, 200); // 0 to 200
    green = random(0, 200);
    blue = random(0, 200);
    lastChangeColorTime = millis();
  }

  matrix.fillScreen(0); // Clear the board

  for (int x = 0; x < 16; x++) {
    int height = wave[x];

    // Draw the wave
    for (int y = 0; y < height; y++) {
      matrix.drawPixel(x, 16 - y - 1, matrix.Color(0,0,200));
    }

    // Fill in the background with the same color
    for (int y = height; y < 16; y++) {
      matrix.drawPixel(x, 16 - y - 1, matrix.Color(red, green, blue));
    }
  }

  matrix.show();
  delay(100); 
}