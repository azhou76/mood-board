#include "GameModes.h"
#include "MatrixHandler.h"
#include "SoundProcessor.h"
#include "WDTHandler.h"
#include "Globals.h"
#define CLAP_THRESHOLD 400

int birdY = 4;        // Bird's vertical position
int birdX = 16;        // Bird's fixed horizontal position
int obstacleX = 2;    // Obstacle's horizontal position
int obstacleGap = 3;  // Gap position in the obstacle
int score = 0;        // Player's score
bool isGameOver = false;
unsigned long lastUpdateTime = 0;
unsigned long flapTime = 0;
int updateInterval = 500; // Game speed
int gravity = 1;          // Bird falls every cycle


void gameModeSetup() {
  currentMode = MODE_NORMAL;
}

// FLAPPY BIRD HELPER FUNCTIONS
void birdFlap() { // Make the bird "flap" upwards
  birdY -= 1;
  //Serial.println(birdY);
  if (birdY < 0) {birdY = 0;} // Prevent going off the screen
}

// Render the game on the LED matrix
void renderGame() {
  matrix.fillScreen(0);
  // Draw the bird
  Serial.println(birdY);
  matrix.drawPixel(birdX,birdY,matrix.Color(200,200,0));

  // Draw the obstacle
  for (int i = 0; i < 16; i++) {
    if (i < obstacleGap || i > obstacleGap + 1) {
      matrix.drawPixel(obstacleX,i,matrix.Color(0,200,0));
    }
  }
  matrix.show();
}


// Update game state
void updateGame() {
  // let it float to the middle
  if (birdX > 8){
    birdX -=1;
  }
 // Prevent going off the screen

  // Move obstacle
  //obstacleX += 1;
  if (obstacleX > 15) {
    obstacleX = 0;                // Reset obstacle position
    obstacleGap = random(1, 12);   // Randomize gap position
    score += 1;                   // Increment score
  }

   // Move obstacle (but stop if the bird cannot pass through)
  birdY += gravity;
  if (birdY > 15) {birdY = 15;}
  obstacleX += 1;
  // if (canPassThrough()) {
  //   obstacleX += 1;  // Move obstacle if the bird can pass
  // }

  // Check for collisions
  if (birdX == obstacleX && (birdY < obstacleGap || birdY > obstacleGap + 1)) {
    isGameOver = true;
  }

  // Update LED matrix
  renderGame();
}

bool canPassThrough(){
  //its not within one of the bird
  //0 is. the right, 15 is the left
  //15 is down, 0 is up
  //bird y is 7 and obstacle gap is 15
  if (birdX-obstacleX < 0){
    return true;
  }
  if (obstacleX-birdX< -1){ //greater than one away or the bird is already to the right of the screen
    return true;
  }
  if (abs(obstacleGap-birdY) == 0 || abs(birdY- obstacleGap+1) ==0){
    return true;
  }
  //Serial.println("false");
  return false;
  //if its within one and one below or one above the mingap height and max gap height

}

// Reset the game variables
void resetGame() {
  int birdY = 4;        // Bird's vertical position
  int birdX = 16;        // Bird's fixed horizontal position
  int obstacleX = 2;    // Obstacle's horizontal position
  int obstacleGap = 3;  // Gap position in the obstacle
  int score = 0;        // Player's score
  bool isGameOver = false;
  Serial.println('reset game');
  matrix.fillScreen(0);
}

// Display game over message
void showGameOver() {
  matrix.fillScreen(0);
  matrix.setTextWrap(false);
  matrix.setCursor(2, 5);  // Adjust the position of the text (you can modify y-coordinate to center it)
  matrix.setTextColor(colors[0]);
  //matrix.setFont(&Tiny3x3a2pt7b);
  //matrix.print();
  matrix.setRotation(1);
  matrix.print(F(":("));// Fill the matrix to indicate "Game Over"
  
  matrix.show();
  //delay(1000);
  matrix.setRotation(4);
  resetGame();

}



void handleModeNormal(int soundValue) {
    Serial.println("normal");
    matrix.setBrightness(10);
    soundValue = pollSound();
    Serial.println(soundValue);
    if (soundValue > 200) {
      Serial.println("Petting watchdog");
      petWDT(); 
    }

    // Check if 5 seconds have passed without petting the watchdog
    if (millis() - lastPetTime > 5000) {
      Serial.println("HELLO");
      Serial.println("Watchdog timeout! System will reset.");

      NVIC_SystemReset();
    }
    drawWave(soundValue, soundValues,filled);
}

void handleModeBright(int soundValue) {
    Serial.println("bright");
    soundValue = pollSound();
    matrix.setBrightness(map(soundValue, 0, 600, 20, 80));
      Serial.println(soundValue);
    if (soundValue > 200) {
      Serial.println("Petting watchdog");
      petWDT(); 
    }

    // Check if 5 seconds have passed without petting the watchdog
    if (millis() - lastPetTime > 5000) {
      Serial.println("HELLO");
      Serial.println("Watchdog timeout! System will reset.");

      NVIC_SystemReset();
    }
    drawWave(soundValue, soundValues,filled);
}

void handleModeParty(int soundValue) {
    Serial.println("PARTTY MODE");
    soundValue = pollSound();
      Serial.println(soundValue);
    if (soundValue > 200) {
      Serial.println("Petting watchdog");
      petWDT(); 
    }

    // Check if 5 seconds have passed without petting the watchdog
    if (millis() - lastPetTime > 5000) {
      Serial.println("HELLO");
      Serial.println("Watchdog timeout! System will reset.");

      NVIC_SystemReset();
    }
    unsigned long currTime= millis();
    unsigned long lastChangeColorTime= 0;
    drawWaveParty(soundValue, currTime, lastChangeColorTime);
}

void handleModeGame() {
    Serial.println("testing refactoring");
    if (isGameOver) {
      showGameOver();
      Serial.println("gameover");
      //break;
    }

    unsigned long currentTime = millis();

    // Check for clap to make the bird flap
    // int clapValue = analogRead(sound_sensor);
    int clapValue = analogRead(A0);
    Serial.println('clapval');
    Serial.println(clapValue);

    if (clapValue > CLAP_THRESHOLD && (currentTime - flapTime > 50)) {
      Serial.println("flapped");
      birdFlap();
      flapTime = currentTime;
      petWDT();
      lastPetTime = millis();
    }
    if (clapValue > CLAP_THRESHOLD){
      petWDT();
      lastPetTime = millis();
    }

    // Update game state at regular intervals
    if (currentTime - lastUpdateTime > updateInterval) {
      updateGame();
      lastUpdateTime = currentTime;
    }
}
