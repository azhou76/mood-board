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
void mockUpdateGame(int &birdX, int &obstacleX, int &obstacleGap, &int score, int &gravity, &int birdY, &int isGameOver);
void mockHandleModeGame(long &currentTime, int &clapValue, int &flapTime,
                        int &lastUpdateTime, int updateInterval, bool &isGameOver,
                        int &birdX, int &birdY, int &obstacleX, int &obstacleGap, int &gravity, int &score);

#endif
