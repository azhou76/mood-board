// /*
//  * THIS FILE WILL BE USED FOR LAB 6
//  */

// /*
//  * A struct to keep all three state inputs in one place
//  */
// typedef struct {
//   int numButtons;
//   orientation lastButton;
//   long mils;
// } state_inputs;

// /*
//  * A struct to keep all 9 state variables in one place
//  */
// typedef struct {
//   byte x;
//   byte y;
//   orientation o;
//   int lxb;
//   int uxb;
//   int level;
//   int timeStep;
//   int savedClock;
//   int countdown;
// } state_vars;

// bool testTransition(state startState,
//                      state endState,
//                      state_inputs testStateInputs, 
//                      state_vars startStateVars,
//                      state_vars endStateVars,
//                      bool verbos);
// /*        
//  * Helper function for printing states
//  */
// char* s2str(state s) {
//   switch(s) {
//     case sDISP_COUNTDOWN:
//     return "(1) DISP_COUNTDOWN";
//     case sWAIT_AFTER_ROT:
//     return "(2) WAIT_AFTER_ROT";
//     case sMOV:
//     return "(3) MOV";
//     case sWAIT_AFTER_MOV:
//     return "(4) WAIT_AFTER_MOV";
//     case sROT:
//     return "(5) ROT";
//     case sWAIT_FOR_BUT:
//     return "(6) WAIT_FOR_BUT";
//     case sGAME_OVER:
//     return "(7) GAME_OVER";
//     default:
//     return "???";
//   }
// }

// /*
//  * Helper function for printing orientations
//  */
// char* o2str(orientation o) {
//   switch(o) {
//     case UP:
//     return "UP";
//     case RIGHT:
//     return "RIGHT";
//     case DOWN:
//     return "DOWN";
//     case LEFT:
//     return "LEFT";
//     default:
//     return "???";
//   }
// }

// /*
//  * Given a start state, inputs, and starting values for state variables, tests that
//  * updateFSM returns the correct end state and updates the state variables correctly
//  * returns true if this is the case (test passed) and false otherwise (test failed)
//  * 
//  * Need to use "verbos" instead of "verbose" because verbose is apparently a keyword
//  */
// bool testTransition(state startState,
//                      state endState,
//                      state_inputs testStateInputs, 
//                      state_vars startStateVars,
//                      state_vars endStateVars,
//                      bool verbos) {
//   x = startStateVars.x;
//   y = startStateVars.y;
//   o = startStateVars.o;
//   lxb = startStateVars.lxb;
//   uxb = startStateVars.uxb;
//   level = startStateVars.level;
//   timeStep = startStateVars.timeStep;
//   savedClock = startStateVars.savedClock;
//   countdown = startStateVars.countdown;
//   state resultState = updateFSM(startState, testStateInputs.mils, testStateInputs.numButtons, testStateInputs.lastButton);
//   bool passedTest = (endState == resultState and
//                       x == endStateVars.x and
//                       y == endStateVars.y and
//                       o == endStateVars.o and
//                       lxb == endStateVars.lxb and
//                       uxb == endStateVars.uxb and
//                       level == endStateVars.level and
//                       timeStep == endStateVars.timeStep and
//                       savedClock == endStateVars.savedClock and
//                       countdown == endStateVars.countdown);
//   if (! verbos) {
//     return passedTest;
//   } else if (passedTest) {
//     char sToPrint[200];
//     sprintf(sToPrint, "Test from %s to %s PASSED", s2str(startState), s2str(endState));
//     Serial.println(sToPrint);
//     return true;
//   } else {
//     char sToPrint[200];
//     Serial.println(s2str(startState));
//     sprintf(sToPrint, "Test from %s to %s FAILED", s2str(startState), s2str(endState));
//     Serial.println(sToPrint);
//     sprintf(sToPrint, "End state expected: %s | actual: %s", s2str(endState), s2str(resultState));
//     Serial.println(sToPrint);
//     sprintf(sToPrint, "Inputs: mils %ld | numButtons %d | lastButton %s", testStateInputs.mils, testStateInputs.numButtons, o2str(testStateInputs.lastButton));
//     Serial.println(sToPrint);
//     sprintf(sToPrint, "          %2s | %2s | %5s | %3s | %3s | %5s | %9s | %11s | %9s", "x", "y", "o", "lxb", "uxb", "level", "timeStep", "savedClock", "countdown");
//     Serial.println(sToPrint);
//     sprintf(sToPrint, "expected: %2d | %2d | %5s | %3d | %3d | %5d | %9d | %11d | %9d", endStateVars.x, endStateVars.y, o2str(endStateVars.o), endStateVars.lxb, endStateVars.uxb, endStateVars.level, endStateVars.timeStep, endStateVars.savedClock, endStateVars.countdown);
//     Serial.println(sToPrint);
//     sprintf(sToPrint, "actual:   %2d | %2d | %5s | %3d | %3d | %5d | %9d | %11d | %9d", x, y, o2str(o), lxb, uxb, level, timeStep, savedClock, countdown);
//     Serial.println(sToPrint);
//     return false;
//   }
// }

// /*
//  * REPLACE THE FOLLOWING 6 LINES WITH YOUR TEST CASES
//  */
// // const state testStatesIn[0] = {};
// // const state testStatesOut[0] = {};
// // const state_inputs testInputs[0] = {};
// // const state_vars testVarsIn[0] = {};
// // const state_vars testVarsOut[0] = {};
// // const int numTests = 0;
// const state testStatesIn[23] = {(state) 1, (state) 1, (state) 1, (state) 1, (state) 2, (state) 2, (state) 2, (state) 3, (state) 3, (state) 4, (state) 4, (state) 4, (state) 5, (state) 5, (state) 5, (state) 6, (state) 6, (state) 6, (state) 7, (state) 1, (state) 1, (state) 2, (state) 2};
// const state testStatesOut[23] = {(state) 1, (state) 1, (state) 2, (state) 6, (state) 2, (state) 3, (state) 3, (state) 4, (state) 7, (state) 4, (state) 5, (state) 5, (state) 2, (state) 6, (state) 7, (state) 6, (state) 1, (state) 7, (state) 7, (state) 2, (state) 6, (state) 3, (state) 3};
// const state_inputs testInputs[23] = {{0, DOWN, 600}, {3, DOWN, 1500}, {0, UP, 1500}, {0, RIGHT, 1500}, {3, LEFT, 1800}, {2, DOWN, 2000}, {0, LEFT, 2000}, {3, LEFT, 2000}, {1, RIGHT, 2}, {3, LEFT, 1800}, {2, RIGHT, 2000}, {0, UP, 2000}, {2, UP, 1500}, {3, UP, 1500}, {3, DOWN, 1}, {1, RIGHT, 1800}, {1, LEFT, 2000}, {2, LEFT, 2000}, {0, UP, 0}, {2, DOWN, 1500}, {1, RIGHT, 1500}, {1, DOWN, 2000}, {0, DOWN, 2000}};
// const state_vars testVarsIn[23] = {{3, 2, LEFT, 1, 0, 2, 2, 500, 3}, {1, 0, UP, 2, 0, 2, 1, 1000, 0}, {5, 0, DOWN, 3, 9, 0, 0, 1000, -1}, {5, 0, UP, 3, 9, 0, 0, 1000, -1}, {0, 2, UP, 0, 2, 2, 1000, 1000, 3}, {0, 3, UP, 0, 13, 2, 1000, 1000, 1}, {0, 3, UP, 0, 13, 2, 1000, 1000, 2}, {4, 2, LEFT, 3, 9, 2, 1, 1000, 1}, {0, 2, RIGHT, 5, 5, 2, 0, 3, 2}, {3, 2, UP, 2, 0, 0, 1000, 1000, 1}, {5, 1, LEFT, 3, 9, 3, 800, 1000, 2}, {5, 1, LEFT, 3, 9, 0, 800, 1000, 1}, {5, 0, DOWN, 3, 9, 3, 1, 1000, 0}, {5, 0, UP, 3, 9, 0, 3, 1000, 0}, {3, 0, UP, 5, 5, 2, 3, 3, 2}, {3, 2, RIGHT, 3, 1, 2, 1000, 1000, 2}, {3, 2, LEFT, 3, 9, 2, 800, 1000, -1}, {3, 2, LEFT, 3, 9, 2, 800, 1000, -1}, {2, 0, UP, 2, 1, 1, 2, 0, 1}, {10, 2, RIGHT, 0, 16, 3, 3, 1000, -1}, {15, 2, RIGHT, 0, 16, 3, 2, 1000, -1}, {2, 3, UP, 0, 16, 2, 1000, 600, 2}, {2, 3, UP, 0, 16, 0, 1000, 1000, 3}};
// const state_vars testVarsOut[23] = {{3, 2, LEFT, 1, 0, 2, 2, 500, 3}, {1, 0, UP, 2, 0, 2, 1, 1500, -1}, {5, 0, DOWN, 3, 9, 0, 0, 1500, -1}, {5, 0, UP, 3, 9, 0, 0, 1500, -1}, {0, 2, UP, 0, 2, 2, 1000, 1000, 3}, {0, 2, UP, 1, 13, 2, 1000, 1000, 1}, {0, 2, UP, 0, 13, 2, 1000, 1000, 2}, {4, 2, LEFT, 3, 9, 2, 1, 2000, 1}, {0, 2, RIGHT, 5, 5, 2, 0, 3, 2}, {3, 2, UP, 2, 0, 0, 1000, 1000, 1}, {5, 1, UP, 4, 9, 3, 800, 1000, 2}, {5, 1, UP, 3, 9, 0, 800, 1000, 1}, {5, 0, DOWN, 3, 9, 3, 1, 1500, 0}, {5, 0, UP, 3, 9, 0, 3, 1500, 0}, {3, 0, UP, 5, 5, 2, 3, 3, 2}, {3, 2, RIGHT, 3, 1, 2, 1000, 1000, 2}, {3, 0, UP, 3, 9, 3, 760, 2000, 2}, {3, 2, LEFT, 3, 9, 2, 800, 1000, -1}, {2, 0, UP, 2, 1, 1, 2, 0, 1}, {10, 2, RIGHT, 0, 16, 3, 3, 1500, -1}, {15, 2, RIGHT, 0, 16, 3, 2, 1500, -1}, {2, 2, UP, 1, 16, 2, 1000, 600, 2}, {2, 2, UP, 0, 16, 0, 1000, 1000, 3}};
// const int numTests = 23;



// /*
//  * Runs through all the test cases defined above
//  */
// bool testAllTests() {
//   Serial.print("HERE");
//   for (int i = 0; i < numTests; i++) {
//     Serial.print("Running test ");
//     Serial.println(i);
//     if (!testTransition(testStatesIn[i], testStatesOut[i], testInputs[i], testVarsIn[i], testVarsOut[i], true)) {
//       return false;
//     }
//     Serial.println();
//   }
//   Serial.println("All tests passed!");
//   return true;
// }



// // // matrix_handler_tests.ino
// // #include "MatrixHandler.h"
// // #include "Globals.h"

// // // Mock Variables and Functions
// // int mockWave[16];

// // void mockMatrixFillScreen(int color) {
// //     // Mock filling the screen (for testing, just print a log)
// //     Serial.print("Screen filled with color: ");
// //     Serial.println(color);
// // }

// // void mockMatrixDrawPixel(int x, int y, int color) {
// //     // Mock drawing a pixel (for testing, log the coordinates and color)
// //     Serial.print("Pixel drawn at (");
// //     Serial.print(x);
// //     Serial.print(", ");
// //     Serial.print(y);
// //     Serial.print(") with color: ");
// //     Serial.println(color);
// // }

// // void mockMatrixShow() {
// //     // Mock showing the matrix (log that the display was updated)
// //     Serial.println("Matrix display updated.");
// // }

// // float mockGetAverage(int arr[], int count) {
// //     if (count == 0) return 0; 
// //     long sum = 0;
// //     for (int i = 0; i < count; i++) {
// //         sum += arr[i];
// //     }
// //     return (float)sum / count; 
// // }

// // // Mocked drawWave Function
// // void mockDrawWave(int soundValue, int soundValues[], int filled) {
// //     int newHeight = map(soundValue, 50, 600, 0, 16);

// //     for (int i = 0; i < 15; i++) {
// //         mockWave[i] = mockWave[i + 1];
// //     }

// //     mockWave[15] = newHeight;

// //     mockMatrixFillScreen(0);
// //     for (int x = 0; x < 16; x++) {
// //         int height = mockWave[x];
// //         for (int y = 0; y < height; y++) {
// //             mockMatrixDrawPixel(x, 16 - y - 1, map(soundValue, 0, 600, 0, 255));
// //         }

// //         for (int y = height; y < 16; y++) {
// //             mockMatrixDrawPixel(x, 16 - y - 1, map(mockGetAverage(soundValues, filled), 0, 600, 255, 0));
// //         }
// //     }

// //     mockMatrixShow();
// // }

// // // Mocked drawWaveParty Function
// // void mockDrawWaveParty(int soundValue, unsigned long currTime, unsigned long &lastChangeColorTime) {
// //     int newHeight = map(soundValue, 0, 1023, 0, 16);

// //     for (int i = 0; i < 15; i++) {
// //         mockWave[i] = mockWave[i + 1];
// //     }

// //     mockWave[15] = newHeight;

// //     static int red = 200, green = 200, blue = 200;

// //     if (currTime - lastChangeColorTime > 2000) {
// //         red = random(0, 200);
// //         green = random(0, 200);
// //         blue = random(0, 200);
// //         lastChangeColorTime = currTime;
// //     }

// //     mockMatrixFillScreen(0);

// //     for (int x = 0; x < 16; x++) {
// //         int height = mockWave[x];

// //         for (int y = 0; y < height; y++) {
// //             mockMatrixDrawPixel(x, 16 - y - 1, mockMatrixColor(0, 0, 200));
// //         }

// //         for (int y = height; y < 16; y++) {
// //             mockMatrixDrawPixel(x, 16 - y - 1, mockMatrixColor(red, green, blue));
// //         }
// //     }

// //     mockMatrixShow();
// // }

// // // Test Cases
// // void testDrawWave() {
// //     Serial.println("Testing mockDrawWave...");

// //     int soundValues[10] = {100, 200, 300, 400, 500, 600, 700, 800, 900, 1000};
// //     mockDrawWave(350, soundValues, 10);
// //     Serial.println("mockDrawWave test completed.");
// // }

// // void testDrawWaveParty() {
// //     Serial.println("Testing mockDrawWaveParty...");

// //     unsigned long lastChangeColorTime = 0;
// //     unsigned long currTime = millis();

// //     mockDrawWaveParty(500, currTime, lastChangeColorTime);
// //     Serial.println("mockDrawWaveParty test completed.");
// // }

// // void setup() {
// //     Serial.begin(9600);
// //     Serial.println("Starting tests...");

// //     // Run tests
// //     testDrawWave();
// //     testDrawWaveParty();

// //     Serial.println("All tests completed.");
// // }

// // void loop() {
// //     // Nothing here for testing purposes
// // }


// Allows us to verify that our mapping conversions of amplitude values to 
void testCheckMapping() {
    Serial.println("Testing checkMapping function...");
    int passed = 0, failed = 0;
    int soundValues[10]; // Mock sound values array
    int filled = 10;     // Mock filled size for testing

    // Generate random test cases
    for (int i = 0; i < 100; i++) {
        int soundValue = random(0, 1024); // Generate random sound values

        // Fill mock soundValues array with random values
        for (int j = 0; j < 10; j++) {
            soundValues[j] = random(0, 1024);
        }

        // Test the function
        bool result = checkMapping(soundValue, soundValues, filled);

        // Expected output conditions
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

        // Validate
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

// Allows us to test that our board's animation-shifting logic is correct when using randomly generated heights for new sound values
void testDrawWave() {
    Serial.println("Testing drawWave function...");
    int mockWave[16]; // Mock wave array
    uint32_t outputMatrix[16][16]; // Resultant matrix

    // Initialize the mockWave array with random values
    for (int i = 0; i < 16; i++) {
        mockWave[i] = random(0, 16); // Random heights for each column
    }

    // Call drawWave with the mock data
    int newHeight = random(0, 16);
    mockDrawWave(mockWave, newHeight, outputMatrix);

    // Validate the outputMatrix
    bool passed = true;

    for (int x = 0; x < 16; x++) {
        int height = mockWave[x];

        // Check for correct pixel placement
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

        // Check for correct background placement
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

    // Display test result
    if (passed) {
        Serial.println("drawWave test passed!");
    } else {
        Serial.println("drawWave test failed.");
    }
}

// Allows us to test if our LED board is drawing correctly using randomly generated sound values
void testIntegratedDrawWave() {
    Serial.println("Integration testing draw wave LED board part");
    int passed = 0, failed = 0;
    int soundValues[10]; // Mock sound values array
    int filled = 10;     // Mock filled size for testing

    // Generate random test cases
    for (int i = 0; i < 20; i++) {
        int soundValue = random(0, 1024); // Generate random sound values

        // Fill mock soundValues array with random values
        for (int j = 0; j < 10; j++) {
            soundValues[j] = random(0, 1024);
        }

        drawWave(soundValue, soundValues, filled);
        Serial.print("Drew wave ");
        Serial.println(i + 1);
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
  int BirdY = 12;
  int obstacleX = 12;
  int obstacleGap = 8;
  mockHandleModeGame(birdX, obstacleX, obstacleGap, score, gravity, birdY, isGameOver);
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
  int BirdY = 12;
  int obstacleX = 12;
  int obstacleGap = 8;
  mockHandleModeGame(birdX, obstacleX, obstacleGap, score, gravity, birdY, isGameOver);
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
  int BirdY = 12;
  int obstacleX = 8;
  int obstacleGap = 12;
  mockHandleModeGame(birdX, obstacleX, obstacleGap, score, gravity, birdY, isGameOver);
  if ((isGameOver){
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
  int BirdY = 12;
  int obstacleX = 8;
  int obstacleGap = 8;
  mockHandleModeGame(birdX, obstacleX, obstacleGap, score, gravity, birdY, isGameOver);
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
  int BirdY = 12;
  int obstacleX = 16;
  int obstacleGap = 8;
  mockHandleModeGame(birdX, obstacleX, obstacleGap, score, gravity, birdY, isGameOver);
  if (!(isGameOver) && (obstacleX == 0)){
    passed ++;
  }
  else{
    Serial.println("testObstacleCollision failed!");
  }}


