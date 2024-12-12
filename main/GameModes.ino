#include "GameModes.h"
#include "MatrixHandler.h"
#include "SoundProcessor.h"
#include "WDTHandler.h"
#include "Globals.h"
#define CLAP_THRESHOLD 400

int birdY = 4;       
int birdX = 16;        
int obstacleX = 2;  
int obstacleGap = 3;  
int score = 0; 
bool isGameOver = false;
unsigned long lastUpdateTime = 0;
unsigned long flapTime = 0;
int updateInterval = 500; 
int gravity = 1; 

void gameModeSetup() {
  currentMode = MODE_NORMAL;
}

// FLAPPY BIRD HELPER FUNCTIONS
void birdFlap() { // Make the bird flap
  birdY -= 1;
  if (birdY < 0) {birdY = 0;} 
}

void renderGame() {
  matrix.fillScreen(0);
  matrix.drawPixel(birdX,birdY,matrix.Color(200,200,0));

  // Draw the obstacle
  for (int i = 0; i < 16; i++) {
    if (i < obstacleGap || i > obstacleGap + 1) {
      matrix.drawPixel(obstacleX,i,matrix.Color(0,200,0));
    }
  }
  matrix.show();
}


void updateGame() {
  if (birdX > 8){
    birdX -=1;
  }

  // move obstacle
  if (obstacleX > 15) {
    obstacleX = 0;                
    obstacleGap = random(1, 12);  
    score += 1;                 
  }

  birdY += gravity;
  if (birdY > 15) {birdY = 15;}
  obstacleX += 1;

  // if collides, then game over
  if (birdX == obstacleX && (birdY < obstacleGap || birdY > obstacleGap + 1)) {
    isGameOver = true;
  }

  renderGame();
}

bool canPassThrough(){
  //0 is. the right, 15 is the left
  //15 is down, 0 is up
  if (birdX-obstacleX < 0){
    return true;
  }
  if (obstacleX-birdX< -1){ //greater than one away or the bird is already to the right of the screen
    return true;
  }
  if (abs(obstacleGap-birdY) == 0 || abs(birdY- obstacleGap+1) ==0){
    return true;
  }
  return false;
  //if its within one and one below or one above the mingap height and max gap height

}

void resetGame() {
  int birdY = 4;        
  int birdX = 16;     
  int obstacleX = 2;  
  int obstacleGap = 3;
  int score = 0;  
  bool isGameOver = false;
  matrix.fillScreen(0);
}

void showGameOver() { // displays image to indicate game over
  matrix.fillScreen(0);
  matrix.setTextWrap(false);
  matrix.setCursor(2, 5);  
  matrix.setTextColor(colors[0]);
  matrix.setRotation(1);
  matrix.print(F(":("));
  matrix.show();
  matrix.setRotation(4);
  resetGame();
}



void handleModeNormal(int soundValue) {
    matrix.setBrightness(10);
    soundValue = pollSound();
    if (soundValue > 200) {
      Serial.println("Petting watchdog");
      petWDT(); 
    }

    // check if 5 seconds have passed without petting the watchdog
    if (millis() - lastPetTime > 5000) {
      Serial.println("Watchdog timeout! System will reset.");

      NVIC_SystemReset();
    }
    drawWave(soundValue, soundValues,filled);
}

void handleModeBright(int soundValue) {
    soundValue = pollSound();
    matrix.setBrightness(map(soundValue, 0, 600, 20, 80));
    if (soundValue > 200) {
      Serial.println("Petting watchdog");
      petWDT(); 
    }

    // Check if 5 seconds have passed without petting the watchdog
    if (millis() - lastPetTime > 5000) {
      Serial.println("Watchdog timed out. System will reset.");
      NVIC_SystemReset();
    }
    drawWave(soundValue, soundValues,filled);
}

void handleModeParty(int soundValue) {
    soundValue = pollSound();
    if (soundValue > 200) {
      Serial.println("Petting watchdog");
      petWDT(); 
    }

    // Check if 5 seconds have passed without petting the watchdog
    if (millis() - lastPetTime > 5000) {
      Serial.println("Watchdog timeout! System will reset.");

      NVIC_SystemReset();
    }
    unsigned long currTime= millis();
    unsigned long lastChangeColorTime= 0;
    drawWaveParty(soundValue, currTime, lastChangeColorTime);
}

void handleModeGame() {
    if (isGameOver) {
      showGameOver();
      Serial.println("Game over.");
    }

    unsigned long currentTime = millis();

    int clapValue = analogRead(A0); // check for clap

    if (clapValue > CLAP_THRESHOLD && (currentTime - flapTime > 50)) {
      birdFlap();
      flapTime = currentTime;
      petWDT();
      lastPetTime = millis();
    }
    if (clapValue > CLAP_THRESHOLD){
      petWDT();
      lastPetTime = millis();
    }
    if (currentTime - lastUpdateTime > updateInterval) {
      updateGame();
      lastUpdateTime = currentTime;
    }
}
