#include "Globals.h"

Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(16, 16, 6,
                                               NEO_MATRIX_TOP + NEO_MATRIX_LEFT + NEO_MATRIX_ROWS + NEO_MATRIX_ZIGZAG,
                                               NEO_GRB + NEO_KHZ800);

// Initialize soundValues array
int soundValues[20] = {0};

// Initialize colors array with RGB values
const uint16_t colors[] = {
    matrix.Color(255, 0, 0), // Red
    matrix.Color(0, 255, 0), // Green
    matrix.Color(0, 0, 255)  // Blue
};

// Initialize lastPetTime
unsigned long lastPetTime = 0;

// Initialize filled state
int filled = 0;
