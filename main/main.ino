#include "MatrixHandler.h"
#include "SoundProcessor.h"
#include "GameModes.h"
#include "InterruptHandler.h"
#include "WDTHandler.h"
#include "GameTest.h"


GameMode currentMode = MODE_NORMAL;

void setup() {
    Serial.begin(9600);

    // UNCOMMENT IF TESTING
    // testCheckMapping(); // tests that ranges of sound value mappings are valid
    // testDrawWave(); // tests wave shift works as expected

    // COMMENT OUT IF TESTING
    matrixSetup();
    soundProcessorSetup();
    interruptSetup();
    gameModeSetup();
    WDTSetup();

    // FUNCTIONS WE USED WHEN TESTING HARDWARE COMPONENTS (i.e. our integration tests)
    // testBirdGravity();
    // testBirdFlap();
    // testBirdCollision();
    // testBirdNoCollision();
    // testObstacleGeneration();
    // testIntegratedDrawWave();
    // testIntegratedModeChange();
    // testBackgroundColorChange();

}

void loop() {
    // COMMENT OUT EVERYTHING IN loop() IF TESTING
    int soundValue = pollSound();
    switch (currentMode) {
        case MODE_NORMAL:
            handleModeNormal(soundValue); // transition 5-1: GAME_MODE -> NORMAL_MODE 
            break;
        case MODE_BRIGHT:
            handleModeBright(soundValue); // transition 1-2, NORMAL_MODE -> BRIGHT_MODE
            break;
        case MODE_PARTY:
            handleModeParty(soundValue); // transition 2-3, BRIGHT_MODE -> PARTY_MODE
            break;
        case MODE_GAME:
            handleModeGame(); // transition 3-4, PARTY_MODE -> GAME_MODE
            break;
        default:
            break;
    }
}