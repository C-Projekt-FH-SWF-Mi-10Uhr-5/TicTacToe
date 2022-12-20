#ifndef GAME_H
#define GAME_H

#include <curses.h>

typedef struct {
    void (*pressedKeyCall)(int pressedKey);
    void (*paintCall)();
    int quit;
} Game;

Game *GameGet();

void GameInit(void (*pressedKeyCall)(int pressedKey), void (*paintCall)());

void GameStart();

void GameStop();

#endif