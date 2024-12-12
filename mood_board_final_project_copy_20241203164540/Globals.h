#ifndef GLOBAL_H
#define GLOBAL_H

#include <Adafruit_NeoMatrix.h> // Include the necessary library for `matrix.Color`
#include <Adafruit_NeoPixel.h> // Include this to support NeoMatrix

// Global sound values
extern int soundValues[20];

// Global colors array (RGB)
extern const uint16_t colors[];

// Global timestamp for last interaction
extern unsigned long lastPetTime;

// Global filled state
extern int filled;

// Global Adafruit_NeoMatrix instance
extern Adafruit_NeoMatrix matrix;

#endif // GLOBAL_H
