/**
 * @file GameAI.h
 * @author Paul Widholt
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

void ViewSettingsPressedKeyCall(int pressedKey);

void ViewSettingsPaintCall();

void ViewSymbolPressedKeyCall(int pressedKey);

void ViewSymbolPaintCall();

void ViewDifficultyPressedKeyCall(int pressedKey);

void ViewDifficultyPaintCall();

#endif