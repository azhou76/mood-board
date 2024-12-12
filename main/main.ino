#include "MatrixHandler.h"
#include "SoundProcessor.h"
#include "GameModes.h"
#include "InterruptHandler.h"
#include "WDTHandler.h"

GameMode currentMode = MODE_NORMAL;

void setup() {
    Serial.begin(9600);
    matrixSetup();
    soundProcessorSetup();
    interruptSetup();
    gameModeSetup();
    WDTSetup();
}

void loop() {
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