#ifndef VIEWBOARD_H
#define VIEWBOARD_H

#include "../include/GameBoard.h"
#include <curses.h>

void ViewBoardSetGameBoard(GameBoard gameBoard);

void ViewBoardPressedKeyCall(int pressedKey);

void ViewBoardPaintCall();

#endif