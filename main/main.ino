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
    // testCheckMapping();
    // testDrawWave();
    

    // COMMENT OUT IF TESTING
    matrixSetup();
    soundProcessorSetup();
    interruptSetup();
    gameModeSetup();
    WDTSetup();

    // UNCOMMENT IF TESTING LED BOARD (without sound sensor)
    // testIntegratedDrawWave();

}

void loop() {
    // COMMENT OUT EVERYTHING IN loop() IF TESTING
    int soundValue = pollSound();
    switch (currentMode) {
        case MODE_NORMAL:
            handleModeNormal(soundValue);
            break;
        case MODE_BRIGHT:
            handleModeBright(soundValue);
            break;
        case MODE_PARTY:
            handleModeParty(soundValue);
            break;
        case MODE_GAME:
            handleModeGame();
            break;
        default:
            break;
    }
}