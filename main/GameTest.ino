#include "GameModes.h"

// checking if mapping conversions of amplitude values correctly
void testCheckMapping() {
    Serial.println("Testing checkMapping function...");
    int passed = 0, failed = 0;
    int soundValues[10]; // Mock sound values array
    int filled = 10;     // Mock filled size for testing

    for (int i = 0; i < 10; i++) {
        int soundValue = random(0, 1024); // Generate random sound values

       // fills in random values for the wave
        for (int j = 0; j < 10; j++) {
            soundValues[j] = random(0, 1024);
        }

        bool result = checkMapping(soundValue, soundValues, filled);

        int newHeight = map(soundValue, 50, 600, 0, 16);
        int newRed = map(soundValue, 0, 600, 0, 255);
        int newGreen = map(soundValue, 0, 600, 0, 127);
        int newBlue = map(soundValue, 0, 600, 255, 0);
        int newBg = map(getAverage(soundValues, filled), 0, 600, 255, 0);

        bool expected = (newHeight >= 0 && newHeight < 16 &&
                         newRed >= 0 && newRed < 255 &&
                         newGreen >= 0 && newGreen < 255 &&
                         newBlue >= 0 && newBlue < 255 &&
                         newBg >= 0 && newBg < 255);

        if (result == expected) {
            passed++;
        } else {
            failed++;
            Serial.print("Failed for soundValue: ");
            Serial.println(soundValue);
        }
    }

    Serial.print("Passed: ");
    Serial.println(passed);
    Serial.print("Failed: ");
    Serial.println(failed);
}

// testing if board is shifting wave to the right given randomly generated heights 
void testDrawWave() {
    Serial.println("Testing drawWave function...");
    int mockWave[16]; // Mock wave array
    uint32_t outputMatrix[16][16]; // Resultant matrix

    // initialized with random values
    for (int i = 0; i < 16; i++) {
        mockWave[i] = random(0, 16); 
    }

    int newHeight = random(0, 16);
    mockDrawWave(mockWave, newHeight, outputMatrix);

    bool passed = true;

    for (int x = 0; x < 16; x++) {
        int height = mockWave[x];

        //check correct pixel placement
        for (int y = 0; y < height; y++) {
            if (outputMatrix[16 - y - 1][x] != 1) {
                Serial.print("Error: Pixel at (");
                Serial.print(x);
                Serial.print(", ");
                Serial.print(16 - y - 1);
                Serial.println(") should be 1.");
                passed = false;
            }
        }

        // checking correct background placement
        for (int y = height; y < 16; y++) {
            if (outputMatrix[16 - y - 1][x] != 0) {
                Serial.print("Error: Pixel at (");
                Serial.print(x);
                Serial.print(", ");
                Serial.print(16 - y - 1);
                Serial.println(") should be 0.");
                passed = false;
            }
        }
    }

    if (passed) {
        Serial.println("drawWave test passed!");
    } else {
        Serial.println("drawWave test failed.");
    }
}

// testing if LED board is drawn correctly using random sound values
void testIntegratedDrawWave() {
    Serial.println("Integration testing draw wave LED board part");
    int passed = 0, failed = 0;
    int soundValues[10]; // Mock sound values array
    int filled = 10;     // Mock filled size for testing

    // fills in random values for the wave
    for (int i = 0; i < 20; i++) {
        int soundValue = random(0, 1024); // Generate random sound values
        
        for (int j = 0; j < 10; j++) {
            soundValues[j] = random(0, 1024);
        }

        drawWave(soundValue, soundValues, filled);
        Serial.print("Drew wave ");
        Serial.println(i + 1);
    }

}

// testing to see if mode changes correctly based on ISR
void testIntegratedModeChange() {
    Serial.println("Starting mode change test!");

    // first ISR call
    ourISR();
    bool firstTest = (currentMode == 1);
    Serial.println(currentMode);

    // second ISR call
    ourISR();
    bool secondTest = (currentMode == 2);
    Serial.println(currentMode);

    // third ISR call
    ourISR();
    bool thirdTest = (currentMode == 3);
    Serial.println(currentMode);

    bool passed = firstTest && secondTest && thirdTest;

    if (passed) {
        Serial.println("Mode change test passed!");
    } else {
        Serial.println("Mode change test failed.");
        
        if (!firstTest) {
            Serial.println("Failed at first test: Expected MODE_BRIGHT");
        }
        if (!secondTest) {
            Serial.println("Failed at second test: Expected MODE_PARTY");
        }
        if (!thirdTest) {
            Serial.println("Failed at third test: Expected MODE_GAME");
        }
    }
}

// testing to see if background color changes correctly
void testBackgroundColorChange() {
  unsigned long lastChangeColorTime = 0;
  unsigned long simulatedMillis = 0; // Simulated "current" time

  int redBefore, greenBefore, blueBefore;
  int redAfter, greenAfter, blueAfter;

  int soundValue = 512; 

  // call to change initial background color
  drawWaveParty(soundValue, simulatedMillis, lastChangeColorTime);

  // initial color values
  redBefore = random(0, 200); 
  greenBefore = random(0, 200);
  blueBefore = random(0, 200);

  // time progression (less than 2 seconds)
  simulatedMillis += 1500; // 1.5 seconds
  drawWaveParty(soundValue, simulatedMillis, lastChangeColorTime);

  // color has not changed
  redAfter = random(0, 200); 
  greenAfter = random(0, 200);
  blueAfter = random(0, 200);
  bool colorDidNotChange = (redBefore == redAfter && greenBefore == greenAfter && blueBefore == blueAfter);

  // time progression (more than 2 seconds)
  simulatedMillis += 1000; // additional 1 second (now 2.5 seconds)
  drawWaveParty(soundValue, simulatedMillis, lastChangeColorTime);

  // check is color has changed
  redAfter = random(0, 200); // Replace with the updated RGB capture
  greenAfter = random(0, 200);
  blueAfter = random(0, 200);
  bool colorDidChange = !(redBefore == redAfter && greenBefore == greenAfter && blueBefore == blueAfter);

  Serial.println("Running Background Color Change Test...");
  if (colorDidNotChange && colorDidChange) {
    Serial.println("Test passed: Background color changes every 2 seconds.");
  } else {
    Serial.println("Test failed: Background color change is incorrect.");
  }
}


//when the the clap threshold hasn't been reached, after one loop with an elapsed time interval, the bird's
// y position should decrement
void testBirdGravity(){
  //int mockSoundValue = 300; //above CLAP_THRESHOLD 400
  long currentTime = 500;
  int clapValue = 500;
  int flapTime= 400;
  int lastUpdateTime = 299;
  int updateInterval = 200;
  bool isGameOver = false;
  int birdX = 8;
  int birdY = 12;
  int obstacleX = 12;
  int obstacleGap = 8;
  int score=0;
  int gravity = 1;
  mockHandleModeGame(clapValue, flapTime, lastUpdateTime, updateTimeInterval, isGameOver, birdX, birdY, obstacleX, obstacleGap, gravity,score);
  if ((birdY == 11)&& !(isGameOver)){
    passed ++;
  }
  else{
    Serial.println("testBirdGravity failed!");
  }
}

//when the the clap threshold has been reached, after one loop with an elapsed time interval, the bird's
// y position should increment
//also testing movement of pipe to the left
void testBirdFlap(){
  //int mockSoundValue = 500; //above CLAP_THRESHOLD 400
  long currentTime = 500;
  int clapValue = 500;
  int flapTime= 400;
  int lastUpdateTime = 400;
  int updateInterval = 200;
  bool isGameOver = false;
  int birdX = 8;
  int birdY = 12;
  int obstacleX = 12;
  int obstacleGap = 8;
  int score=0;
  int gravity = 1;
  mockHandleModeGame(clapValue, flapTime, lastUpdateTime, updateTimeInterval, isGameOver, birdX, birdY, obstacleX, obstacleGap, gravity, score);
  if ((birdY == 13)&& !(isGameOver) && (obstacleX == 13)){
    passed ++;
  }
  else{
    Serial.println("testBirdFlap failed!");
  }

}

//if there is a collision, gameOver should be set to true


void testBirdCollision(){
  long currentTime = 500;
  int clapValue = 0;
  int flapTime= 400;
  int lastUpdateTime = 299;
  int updateInterval = 200;
  bool isGameOver = false;
  int birdX = 8;
  int birdY = 12;
  int obstacleX = 8;
  int obstacleGap = 12;
  int score=0;
  int gravity = 1;
  mockHandleModeGame(clapValue, flapTime, lastUpdateTime, updateTimeInterval, isGameOver, birdX, birdY, obstacleX, obstacleGap, gravity,score);
  if (isGameOver){
    passed ++;
  }
  else{
    Serial.println("testBirdCollision failed!");
  }}

  //if there is no collision when the obstacle X and bird X are the same, gameOver should be false
void testBirdNoCollision(){
  long currentTime = 500;
  int clapValue = 0;
  int flapTime= 400;
  int lastUpdateTime = 299;
  int updateInterval = 200;
  bool isGameOver = false;
  int birdX = 9;
  int birdY = 12;
  int obstacleX = 8;
  int obstacleGap = 8;
  int score=0;
  int gravity = 1;
  mockHandleModeGame(clapValue, flapTime, lastUpdateTime, updateTimeInterval, isGameOver, birdX, birdY, obstacleX, obstacleGap, gravity,score);
  if (!(isGameOver) && (obstacleX == 9)){
    passed ++;
  }
  else{
    Serial.println("testBirdCollision failed!");
  }}

  //test that new obstacle is generated after previous moves off the screen
void testObstacleGeneration(){
  long currentTime = 500;
  int clapValue = 0;
  int flapTime= 400;
  int lastUpdateTime = 299;
  int updateInterval = 200;
  bool isGameOver = false;
  int birdX = 9;
  int birdY = 12;
  int obstacleX = 16;
  int obstacleGap = 8;
  int score=0;
  int gravity = 1;
  mockHandleModeGame(clapValue, flapTime, lastUpdateTime, updateTimeInterval, isGameOver, birdX, birdY, obstacleX, obstacleGap, gravity,score);
  if (!(isGameOver) && (obstacleX == 0)){
    passed ++;
  }
  else{
    Serial.println("testObstacleCollision failed!");
  }}

