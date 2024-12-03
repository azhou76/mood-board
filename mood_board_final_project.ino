#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>
#ifndef PSTR
 #define PSTR // Make Arduino Due happy
#endif

#define PIN 6

int sound_sensor = A0; //assign to pin A2

// MATRIX DECLARATION:
// Parameter 1 = width of the matrix
// Parameter 2 = height of the matrix
// Parameter 3 = pin number (most are valid)
// Parameter 4 = matrix layout flags, add together as needed:
//   NEO_MATRIX_TOP, NEO_MATRIX_BOTTOM, NEO_MATRIX_LEFT, NEO_MATRIX_RIGHT:
//     Position of the FIRST LED in the matrix; pick two, e.g.
//     NEO_MATRIX_TOP + NEO_MATRIX_LEFT for the top-left corner.
//   NEO_MATRIX_ROWS, NEO_MATRIX_COLUMNS: LEDs are arranged in horizontal
//     rows or in vertical columns, respectively; pick one or the other.
//   NEO_MATRIX_PROGRESSIVE, NEO_MATRIX_ZIGZAG: all rows/columns proceed
//     in the same order, or alternate lines reverse direction; pick one.
//   See example below for these values in action.
// Parameter 5 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_GRBW    Pixels are wired for GRBW bitstream (RGB+W NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)

Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(16, 16, PIN,
  NEO_MATRIX_TOP     + NEO_MATRIX_LEFT +
  NEO_MATRIX_ROWS + NEO_MATRIX_ZIGZAG,
  NEO_GRB            + NEO_KHZ800);

const uint16_t colors[] = {
  matrix.Color(255, 0, 0), matrix.Color(0, 255, 0), matrix.Color(0, 0, 255) };

void setup() {
  Serial.begin(9600); //begin Serial Communication
  matrix.begin();
  matrix.setTextWrap(false);
  matrix.setBrightness(255);
  matrix.setTextColor(colors[0]);
}

int x    = matrix.width();
int pass = 0;

void loop() {
  int soundValue = 0; //create variable to store many different readings
  for (int i = 0; i < 32; i++) //create a for loop to read 
  { soundValue += analogRead(sound_sensor);  } //read the sound sensor
 
  soundValue >>= 5; //bitshift operation 
  Serial.println(soundValue); //print the value of sound sensor
 
  //if a value higher than 500 is registered, we will print the following
  //this is done so that we can clearly see if the threshold is met
  if (soundValue > 500) { 
    Serial.println("         ||        ");
    Serial.println("       ||||||      ");
    Serial.println("     |||||||||     ");
    Serial.println("   |||||||||||||   ");
    Serial.println(" ||||||||||||||||| ");
    Serial.println("   |||||||||||||   ");
    Serial.println("     |||||||||     ");
    Serial.println("       ||||||      ");\
    Serial.println("         ||        ");
  }


  // matrix.fillScreen(0);
  // matrix.setCursor(x, 0);
  matrix.setBrightness(20);

  // Fill the left half (16 columns out of 32) with red
  matrix.fillRect(0, 0, 8, 16, matrix.Color(map(soundValue, 50, 500, 0, 255), map(soundValue, 50, 500, 0, 127), map(soundValue, 50, 500, 255, 0)));  // x, y, width, height, color

  // Fill the right half (remaining 16 columns) with blue
  matrix.fillRect(8, 0, 8, 16, matrix.Color(0, 0, 255));

  // int freq = 80;
  // matrix.fillScreen(matrix.Color(freq, freq, freq));
  matrix.show();
  delay(100);
}