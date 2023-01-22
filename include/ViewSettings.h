/**
 * @file GameAI.h
 * @brief
 * @version 0.1
 * @date 2023-01-03
 */

#ifndef VIEWSETTINGS_H
#define VIEWSETTINGS_H

#include "../include/Game.h"
#include "../include/ViewMenu.h"

#include <stdio.h>
#include <curses.h>

char Player1Symbol; //Spieler 1 Symbol im Spiel
char Player2Symbol; //Spieler 2 Symbol im Spiel
int Difficulty; //Schwierigkeit des 2. Spielers, falls Computer-Gegner (Singleplayer)

void ViewSettingsPressedKeyCall(int pressedKey);

void ViewSettingsPaintCall();

void ViewSymbolPressedKeyCall(int pressedKey);

void ViewSymbolPaintCall();

void ViewDifficultyPressedKeyCall(int pressedKey);

void ViewDifficultyPaintCall();

void ViewPlayerPressedKeyCall(int pressedKey);

void ViewPlayerPaintCall();

#endif