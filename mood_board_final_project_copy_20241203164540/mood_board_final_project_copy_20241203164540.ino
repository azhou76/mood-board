// #include <Adafruit_GFX.h>
// #include <Adafruit_NeoMatrix.h>
// #include <Adafruit_NeoPixel.h>
// #include "FspTimer.h"
// #include "WDT.h"
// #ifndef PSTR
// #define PSTR 
// #endif

// // #define PIN 6

// int sound_sensor = A0; 

// Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(16, 16, 6,
//                                                NEO_MATRIX_TOP + NEO_MATRIX_LEFT + NEO_MATRIX_ROWS + NEO_MATRIX_ZIGZAG,
//                                                NEO_GRB + NEO_KHZ800);

// const uint16_t colors[] = {
//   matrix.Color(255, 0, 0), matrix.Color(0, 255, 0), matrix.Color(0, 0, 255)
// };

// typedef enum {
//     MODE_NORMAL,
//     MODE_BRIGHT,
//     MODE_PARTY,
//     MODE_GAME,
//     MODE_COUNT
// } GameMode;
// GameMode currentMode = MODE_NORMAL;

// int wave[16]; //wave height array
// const unsigned int D6_PORT = 1;
// const unsigned int D6_PIN = 11;
// const unsigned int D2_PORT = 1;
// const unsigned int D2_PIN = 4;
// const unsigned int D2_IRQ = 1;

// bool brightNormal = true;

// unsigned long lastPetTime = 0;  
// int birdY = 4;        // Bird's vertical position
// int birdX = 16;        // Bird's fixed horizontal position
// int obstacleX = 2;    // Obstacle's horizontal position
// int obstacleGap = 3;  // Gap position in the obstacle
// int score = 0;        // Player's score
// bool isGameOver = false;

// unsigned long lastUpdateTime = 0;
// unsigned long flapTime = 0;
// int updateInterval = 500; // Game speed
// int gravity = 1;          // Bird falls every cycle

// // Clap detection threshold
// #define CLAP_THRESHOLD 400
// // The MCU gives us 32 possible CPU interrupt channels to connect to
// // We'll just use the first available one (see Datasheet Table 13.3.1 for more info)
// unsigned int getNextCPUINT(unsigned int start) {
//   /* Get next unused CPU interrupt > start */
//   unsigned int tryInt = start + 1;
//   while (tryInt < 32) {
//     if (NVIC_GetEnableIRQ((IRQn_Type)tryInt) == 0) {
//       return tryInt;
//     }
//     tryInt++;
//   }
// }
// const unsigned int CPU_INT_1 = getNextCPUINT(1);

// void setInterrupts(){
//   // R_PFS->PORT[D6_PORT].PIN[D6_PIN].PmnPFS_b.PDR = 1;
//   // R_PFS->PORT[D6_PORT].PIN[D6_PIN].PmnPFS_b.PDR = 1; // Set as output
//   R_PFS->PORT[D2_PORT].PIN[D2_PIN].PmnPFS_b.PDR = 0;

//   // Disable the CPU interrupt while we configure it
//   NVIC_DisableIRQ((IRQn_Type)CPU_INT_1);

//   // TODO: Configure D2 as an input AND to be used as an IRQ input pin
//   R_PFS->PORT[D2_PORT].PIN[D2_PIN].PmnPFS = (1 << R_PFS_PORT_PIN_PmnPFS_ISEL_Pos);

//   // TODO: Trigger an interrupt when D2 goes from LOW to HIGH (prelab Q4.6)
//   // Configure the ICU to connect the Port IRQ to the CPU (NVIC) IRQ (prelab Q4.7)
//   R_ICU->IELSR[CPU_INT_1] = 0x002;

//   // Use the Arm CMSIS API to enable *CPU* interrupts
//   NVIC_SetVector((IRQn_Type)CPU_INT_1, (uint32_t)&ourISR);  // set vector entry to our handler
//   NVIC_SetPriority((IRQn_Type)CPU_INT_1, 14);               // Priority lower than Serial (12)
//   NVIC_EnableIRQ((IRQn_Type)CPU_INT_1);
// }

// void petWDT() {
//   WDT.refresh();           
//   lastPetTime = millis(); 
// }

// void drawWave(int soundValue, int soundValues[], int filled) {
//   // Map the sound value to wave height
//  int newHeight = map(soundValue, 50, 600, 0, 16);

//  for (int i = 0; i < 15; i++) { // shiting wave to left
// wave[i] = wave[i + 1];
//  }

//  wave[15] = newHeight; // add new wave height to the end of the array

//  // Draw the wave
//  matrix.fillScreen(0); // Clear the matrix
//  for (int x = 0; x < 16; x++) {
//  int height = wave[x];
//  for (int y = 0; y < height; y++) {
//  // Draw a vertical column of pixels for the wave
//  matrix.drawPixel(x, 16 - y - 1, matrix.Color(map(soundValue, 0, 600, 0, 255), map(soundValue, 0, 600, 0, 127), map(soundValue, 0, 600, 255, 0)));
//  }

//  for (int y = height; y < 16; y++) {
//     matrix.drawPixel(x, 16 - y - 1,
//     matrix.Color(map(getAverage(soundValues, filled), 0, 600, 255, 0), map(getAverage(soundValues, filled), 0, 600, 255, 0), map(getAverage(soundValues, filled), 0, 600, 255, 0)) // Example: Fill with blue
//     );
//     }
//  }
//  matrix.show();
//  delay(100);
// }

// void drawWaveParty(int soundValue, unsigned long currTime, unsigned long &lastChangeColorTime) {
//   // map sound val to wave height
//   int newHeight = map(soundValue, 0, 1023, 0, 16);

//   for (int i = 0; i < 15; i++) { // shifting wave to the left
//     wave[i] = wave[i + 1];
//   }

//   wave[15] = newHeight; // add new wave height to the end of the array

//   // Declare static color variables to persist across function calls
//   static int red = 200, green = 200, blue = 200;

//   // Change color every 2 seconds
//   if (millis() - lastChangeColorTime > 2000) {
//     red = random(0, 200); // 0 to 200
//     green = random(0, 200);
//     blue = random(0, 200);
//     lastChangeColorTime = millis();
//   }

//   matrix.fillScreen(0); // Clear the board

//   for (int x = 0; x < 16; x++) {
//     int height = wave[x];

//     // Draw the wave
//     for (int y = 0; y < height; y++) {
//       matrix.drawPixel(x, 16 - y - 1, matrix.Color(
//         0,0,200
//         //map(soundValue, 0, 600, 0, 255),
//         //map(soundValue, 0, 600, 0, 127),
//         //map(soundValue, 0, 600, 255, 0)
//       ));
//     }

//     // Fill in the background with the same color
//     for (int y = height; y < 16; y++) {
//       matrix.drawPixel(x, 16 - y - 1, matrix.Color(red, green, blue));
//     }
//   }

//   matrix.show();
//   delay(100); // Optional delay for visibility
// }


// void setup() {
//   Serial.begin(9600);  
//   matrix.begin();
//   matrix.setTextWrap(false);
//   matrix.setBrightness(255);
//   matrix.setTextColor(colors[0]);

//   // pinMode(7, INPUT);

//   while (!Serial);
//   setInterrupts();

//   // Initialize wave heights
//   for (int i = 0; i < 16; i++) {
//     wave[i] = 16 / 2; 
//   }

//   // Initialize the watchdog
//   if (WDT.begin(5000)) {
//     //Serial.println("Initializing watchdog");
//     WDT.refresh();
//   } else {
//    // Serial.println("Error initializing watchdog");
//   }

//   lastPetTime = millis(); 
// }

// void ourISR() {
//   static int timesPushed = 0; 
//   Serial.println(timesPushed++);
//   if (R_ICU->IELSR_b[CPU_INT_1].IR == 1) {
//    // brightNormal = !brightNormal; //toggle brightness mode on interrupt
//     currentMode = static_cast<GameMode>((currentMode + 1) % MODE_COUNT);
//     Serial.println(currentMode);




//     // comment out if/else to make it pause and unpause instead of on/off
//     // if (brightNormal) {
//     //    matrix.fillScreen(0);  // Turn on the matrix (clear screen)
//     //    matrix.show();         // Update the matrix display
//     // } else {
//     //    matrix.clear();        // Turn off the matrix
//     //    matrix.show();         // Update the matrix display
//     // }
//     R_ICU->IELSR_b[CPU_INT_1].IR = 0;
//     NVIC_ClearPendingIRQ((IRQn_Type)CPU_INT_1);
//   }
// }

// int x = matrix.width();
// int pass = 0;
// int filled = 0;
// int soundValues[20];


// int pollSound() {
//    int soundValue = 0;                     
//     for (int i = 0; i < 32; i++)  
//     { soundValue += analogRead(sound_sensor); } 

//     soundValue >>= 5;            //bitshift operation

//     if (soundValue > 250) {
//       if (pass < 20) {
//         soundValues[pass] = soundValue;
//         pass += 1;
//       } else {
//         pass = 0;
//       }
//       if (filled < 20) {
//         filled += 1;
//       }
//     }

//     return soundValue;
// }
// void loop() {
//   //if (brightNormal) {
//     int soundValue;
//   switch(currentMode) {
//     case MODE_NORMAL:{
//       Serial.println("normal");
//       matrix.setBrightness(10);
//       soundValue = pollSound();
//       Serial.println(soundValue);
//       if (soundValue > 200) {
//         Serial.println("Petting watchdog");
//         petWDT(); 
//       }

//       // Check if 5 seconds have passed without petting the watchdog
//       if (millis() - lastPetTime > 5000) {
//         Serial.println("HELLO");
//         Serial.println("Watchdog timeout! System will reset.");

//         NVIC_SystemReset();
//       }
//       drawWave(soundValue, soundValues,filled);
//       break;}
  
//   // else {
//     case MODE_BRIGHT:{
//       Serial.println("bright");
//       soundValue = pollSound();
//       matrix.setBrightness(map(soundValue, 0, 600, 20, 80));
//        Serial.println(soundValue);
//       if (soundValue > 200) {
//         Serial.println("Petting watchdog");
//         petWDT(); 
//       }

//       // Check if 5 seconds have passed without petting the watchdog
//       if (millis() - lastPetTime > 5000) {
//         Serial.println("HELLO");
//         Serial.println("Watchdog timeout! System will reset.");

//         NVIC_SystemReset();
//       }
//       drawWave(soundValue, soundValues,filled);
//       break;}
//     //}
//   case MODE_GAME: {
//     Serial.println("testing refactoring");
//     if (isGameOver) {
//       showGameOver();
//       Serial.println("gameover");
//       break;
//     }

//     unsigned long currentTime = millis();

//     // Check for clap to make the bird flap
//     int clapValue = analogRead(sound_sensor);
//     Serial.println('clapval');
//     Serial.println(clapValue);

//     if (clapValue > CLAP_THRESHOLD && (currentTime - flapTime > 50)) {
//       Serial.println("flapped");
//       birdFlap();
//       flapTime = currentTime;
//       petWDT();
//       lastPetTime = millis();
//     }
//     if (clapValue > CLAP_THRESHOLD){
//       petWDT();
//       lastPetTime = millis();
//     }

//     // Update game state at regular intervals
//     if (currentTime - lastUpdateTime > updateInterval) {
//       updateGame();
//       lastUpdateTime = currentTime;
//     }
//     break;  // Ensure a break is present to avoid fall-through
// }
//   case MODE_PARTY:{
//     Serial.println("PARTTY MODE");
//       soundValue = pollSound();
//       //matrix.setBrightness(map(soundValue, 0, 600, 20, 80));
//         Serial.println(soundValue);
//       if (soundValue > 200) {
//         Serial.println("Petting watchdog");
//         petWDT(); 
//       }

//       // Check if 5 seconds have passed without petting the watchdog
//       if (millis() - lastPetTime > 5000) {
//         Serial.println("HELLO");
//         Serial.println("Watchdog timeout! System will reset.");

//         NVIC_SystemReset();
//       }
//       unsigned long currTime= millis();
//       unsigned long lastChangeColorTime= 0;
//       drawWaveParty(soundValue, currTime, lastChangeColorTime);
//       break;
//   }
//   }

// }

// float getAverage(int arr[], int count) {
//   if (count == 0) return 0; 
//   long sum = 0;
//   for (int i = 0; i < count; i++) {
//     sum += arr[i];
//   }

//   return (float)sum / count; 
// }
// // Make the bird "flap" upwards
// void birdFlap() {
//   birdY -= 1;
//   //Serial.println(birdY);
//   if (birdY < 0) {birdY = 0;} // Prevent going off the screen
// }

// // Update game state
// void updateGame() {
//   // let it float to the middle
//   if (birdX > 8){
//     birdX -=1;
//   }
//  // Prevent going off the screen

//   // Move obstacle
//   //obstacleX += 1;
//   if (obstacleX > 15) {
//     obstacleX = 0;                // Reset obstacle position
//     obstacleGap = random(1, 12);   // Randomize gap position
//     score += 1;                   // Increment score
//   }

//    // Move obstacle (but stop if the bird cannot pass through)
//   birdY += gravity;
//   if (birdY > 15) {birdY = 15;}
//   obstacleX += 1;
//   // if (canPassThrough()) {
//   //   obstacleX += 1;  // Move obstacle if the bird can pass
//   // }

//   // Check for collisions
//   if (birdX == obstacleX && (birdY < obstacleGap || birdY > obstacleGap + 1)) {
//     isGameOver = true;
//   }

//   // Update LED matrix
//   renderGame();
// }

// bool canPassThrough(){
//   //its not within one of the bird
//   //0 is. the right, 15 is the left
//   //15 is down, 0 is up
//   //bird y is 7 and obstacle gap is 15
//   if (birdX-obstacleX < 0){
//     return true;
//   }
//   if (obstacleX-birdX< -1){ //greater than one away or the bird is already to the right of the screen
//     return true;
//   }
//   if (abs(obstacleGap-birdY) == 0 || abs(birdY- obstacleGap+1) ==0){
//     return true;
//   }
//   //Serial.println("false");
//   return false;
//   //if its within one and one below or one above the mingap height and max gap height

// }

// // Render the game on the LED matrix
// void renderGame() {
//   matrix.fillScreen(0);
//   // Draw the bird
//   Serial.println(birdY);
//   matrix.drawPixel(birdX,birdY,matrix.Color(200,200,0));

//   // Draw the obstacle
//   for (int i = 0; i < 16; i++) {
//     if (i < obstacleGap || i > obstacleGap + 1) {
//       matrix.drawPixel(obstacleX,i,matrix.Color(0,200,0));
//     }
//   }
//   matrix.show();
// }
// // Reset the game variables
// void resetGame() {
//   int birdY = 4;        // Bird's vertical position
//   int birdX = 16;        // Bird's fixed horizontal position
//   int obstacleX = 2;    // Obstacle's horizontal position
//   int obstacleGap = 3;  // Gap position in the obstacle
//   int score = 0;        // Player's score
//   bool isGameOver = false;
//   Serial.println('reset game');
//   matrix.fillScreen(0);
// }


// // Display game over message
// void showGameOver() {
//   matrix.fillScreen(0);
//   matrix.setTextWrap(false);
//   matrix.setCursor(2, 5);  // Adjust the position of the text (you can modify y-coordinate to center it)
//   matrix.setTextColor(colors[0]);
//   //matrix.setFont(&Tiny3x3a2pt7b);
//   //matrix.print();
//   matrix.setRotation(1);
//   matrix.print(F(":("));// Fill the matrix to indicate "Game Over"
  
//   matrix.show();
//   //delay(1000);
//   matrix.setRotation(4);
//   resetGame();

// }

