#ifndef MATRIX_HANDLER_H
#define MATRIX_HANDLER_H

#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>

extern Adafruit_NeoMatrix matrix;
void matrixSetup();
void drawWave(int soundValue, int soundValues[], int filled);
void drawWaveParty(int soundValue, unsigned long currTime, unsigned long &lastChangeColorTime);

#endif