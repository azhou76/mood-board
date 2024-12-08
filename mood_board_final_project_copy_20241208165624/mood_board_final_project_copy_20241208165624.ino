#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>

#include "FspTimer.h"
#include "WDT.h"

#ifndef PSTR
#define PSTR // Make Arduino Due happy
#endif

// #define PIN 6

int sound_sensor = A0; //assign to pin A2

Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(16, 16, 6,
 NEO_MATRIX_TOP + NEO_MATRIX_LEFT + NEO_MATRIX_ROWS + NEO_MATRIX_ZIGZAG,
 NEO_GRB + NEO_KHZ800);

const uint16_t colors[] = {
 matrix.Color(255, 0, 0), matrix.Color(0, 255, 0), matrix.Color(0, 0, 255)
};

int wave[16]; // Array to hold wave heights for each column

const unsigned int D6_PORT = 1;
const unsigned int D6_PIN = 11;

// TODO:
const unsigned int D2_PORT = 1;
const unsigned int D2_PIN = 4;

// TODO: (Prelab step 4.5)
const unsigned int D2_IRQ = 1;

bool brightNormal = true;

unsigned long lastPetTime = 0; // Tracks last time watchdog was reset

// The MCU gives us 32 possible CPU interrupt channels to connect to
// We'll just use the first available one (see Datasheet Table 13.3.1 for more info)
unsigned int getNextCPUINT(unsigned int start) {
 /* Get next unused CPU interrupt > start */
 unsigned int tryInt = start + 1;
 while (tryInt < 32) {
 if (NVIC_GetEnableIRQ((IRQn_Type)tryInt) == 0) {
 return tryInt;
 }
 tryInt++;
 }
}
const unsigned int CPU_INT_1 = getNextCPUINT(1);

void petWDT() {
 WDT.refresh(); // Reset the watchdog timer
 lastPetTime = millis(); // Update the last pet time
}

void setup() {
 Serial.begin(9600); //begin Serial Communication
 matrix.begin();
 matrix.setTextWrap(false);
 matrix.setBrightness(255);
 matrix.setTextColor(colors[0]);

 // pinMode(7, INPUT);

 while (!Serial);

 // R_PFS->PORT[D6_PORT].PIN[D6_PIN].PmnPFS_b.PDR = 1;
 // R_PFS->PORT[D6_PORT].PIN[D6_PIN].PmnPFS_b.PDR = 1; // Set as output
 R_PFS->PORT[D2_PORT].PIN[D2_PIN].PmnPFS_b.PDR = 0;

 // Disable the CPU interrupt while we configure it
 NVIC_DisableIRQ((IRQn_Type)CPU_INT_1);

 // TODO: Configure D2 as an input AND to be used as an IRQ input pin
 // Note: read the PmnPFS register description to find the name of the field that
 // configures a pin for IRQ
 // Both fields should be set in one write, using the bitfield macro style you saw
 // in lecture/prelab Q3. All other bitfields should be 0, so you don't have to worry
 // about leaving them unchanged -- just overwrite the whole register
 // The macro(s) you want to use will start with R_PFS_PORT_PIN_PmnPFS
 R_PFS->PORT[D2_PORT].PIN[D2_PIN].PmnPFS = (1 << R_PFS_PORT_PIN_PmnPFS_ISEL_Pos);

 // TODO: Trigger an interrupt when D2 goes from LOW to HIGH (prelab Q4.6)
 // Again, do not use the _b notation. We can just overwrite the register and make the
 // values of the other fields 0.
 R_ICU->IRQCR[D2_IRQ] = 01;
 // Configure the ICU to connect the Port IRQ to the CPU (NVIC) IRQ (prelab Q4.7)
 R_ICU->IELSR[CPU_INT_1] = 0x002;

 // Use the Arm CMSIS API to enable *CPU* interrupts
 NVIC_SetVector((IRQn_Type)CPU_INT_1, (uint32_t)&ourISR); // set vector entry to our handler
 NVIC_SetPriority((IRQn_Type)CPU_INT_1, 14); // Priority lower than Serial (12)
 NVIC_EnableIRQ((IRQn_Type)CPU_INT_1);

 // Initialize wave heights
 for (int i = 0; i < 16; i++) {
 wave[i] = 16 / 2; // Start with the wave centered
 }

 // Initialize the watchdog with a 5-second timeout
 if (WDT.begin(5000)) {
 Serial.println("Initializing watchdog");
 WDT.refresh();
 } else {
 Serial.println("Error initializing watchdog");
 }

 lastPetTime = millis(); // Initialize the pet time
}

void ourISR() {
 static int timesPushed = 0; // static means value persists between function calls
//  Serial.println(timesPushed++);
 if (R_ICU->IELSR_b[CPU_INT_1].IR == 1) {
 brightNormal = !brightNormal; // Toggle the matrix state
 // comment out if/else to make it pause and unpause instead of on/off
 // if (brightNormal) {
 // matrix.fillScreen(0); // Turn on the matrix (clear screen)
 // matrix.show(); // Update the matrix display
 // } else {
 // matrix.clear(); // Turn off the matrix
 // matrix.show(); // Update the matrix display
 // }
 R_ICU->IELSR_b[CPU_INT_1].IR = 0;
 NVIC_ClearPendingIRQ((IRQn_Type)CPU_INT_1);
 }
}

int x = matrix.width();
int pass = 0;
int filled = 0;
int soundValues[10];


void loop() {
 if (brightNormal) {
  Serial.println("test");
  Serial.println(analogRead(sound_sensor));
 int soundValue = 0; //create variable to store many different readings
 for (int i = 0; i < 32; i++) //create a for loop to read
 { soundValue += analogRead(sound_sensor); } //read the sound sensor

 soundValue >>= 5; //bitshift operation

 if (soundValue > 200) {
 if (pass < 10) {
 soundValues[pass] = soundValue;
 pass += 1;
 } else {
 pass = 0;
 }
 if (filled < 10) {
 filled += 1;
 }
 }


 //if a value higher than 500 is registered, we will print the following
 //this is done so that we can clearly see if the threshold is met

 // matrix.fillScreen(0);
 // matrix.setCursor(x, 0);
 matrix.setBrightness(10);

 // Fill the left half (16 columns out of 32) with red
 // if ((getAverage(soundValues, filled) - soundValue > 300) or (getAverage(soundValues, filled) - soundValue < -300)) {
 // matrix.fillRect(0, 0, 16, 16, matrix.Color(255, 255, 255)); // x, y, width, height, color
 // } else {

 // soundValue = constrain(soundValue, 0, 1023); // Ensure value is within 0-1023
 Serial.println(soundValue);
 if (soundValue > 200) {
 Serial.println("Petting watchdog");
 petWDT(); // Reset the watchdog timer
 } 

 // Check if 5 seconds have passed without petting the watchdog
 if (millis() - lastPetTime > 5000) {
 Serial.println("HELLO");
 Serial.println("Watchdog timeout! System will reset.");
 
 NVIC_SystemReset(); // Trigger system reset
 }

 drawWave(soundValue); // Draw wave on LED matrix
 }
 else {
  Serial.println("test");
  Serial.println(analogRead(sound_sensor));
 int soundValue = 0; //create variable to store many different readings
 for (int i = 0; i < 32; i++) //create a for loop to read 
 { soundValue += analogRead(sound_sensor); } //read the sound sensor
 
 soundValue >>= 5; //bitshift operation 
 Serial.println(soundValue); //print the value of sound sensor

 if (soundValue > 200) {
 if (pass < 10) {
 soundValues[pass] = soundValue;
 pass += 1;
 } else {
 pass = 0;
 }
 if (filled < 10) {
 filled += 1;
 }
 }
 
 // matrix.fillScreen(0);
 // matrix.setCursor(x, 0);
 matrix.setBrightness(map(soundValue, 0, 600, 20, 80));

 Serial.println(soundValue);
 if (soundValue > 200) {
 Serial.println("Petting watchdog");
 petWDT(); // Reset the watchdog timer
 } 

 // Check if 5 seconds have passed without petting the watchdog
 if (millis() - lastPetTime > 5000) {
 Serial.println("HELLO");
 Serial.println("Watchdog timeout! System will reset.");
 
 NVIC_SystemReset(); // Trigger system reset
 }

 drawWave(soundValue); // Draw wave on LED matrix
 }

}

void drawWave(int soundValue) {
 // Map the sound value to wave height
 int newHeight = map(soundValue, 50, 600, 0, 16);

 // Shift the wave to the left
 for (int i = 0; i < 15; i++) {
 wave[i] = wave[i + 1];
 }

 // Add the new wave height to the end
 wave[15] = newHeight;

 // Draw the wave
 matrix.fillScreen(0); // Clear the matrix
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

float getAverage(int arr[], int count) {
 if (count == 0) return 0; // Avoid division by zero

 long sum = 0; // Use long to prevent overflow with large numbers
 for (int i = 0; i < count; i++) {
 sum += arr[i];
 }

 return (float)sum / count; // Return average as a float
}
