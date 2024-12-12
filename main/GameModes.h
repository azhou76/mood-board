#ifndef GAME_MODES_H
#define GAME_MODES_H

typedef enum {
    MODE_NORMAL,
    MODE_BRIGHT,
    MODE_PARTY,
    MODE_GAME,
    MODE_COUNT
} GameMode;

extern GameMode currentMode;

void gameModeSetup();
void handleModeNormal(int soundValue);
void handleModeBright(int soundValue);
void handleModeParty(int soundValue);
void handleModeGame();

#endif