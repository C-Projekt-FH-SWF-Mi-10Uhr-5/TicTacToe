/**
 * @file ViewBoard.h
 * @author Fabian Grubba (grubba.fabiandavidjonah@fh-swf.de)
 * @brief
 * @version 0.1
 * @date 2022-12-21
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef VIEWBOARD_H
#define VIEWBOARD_H

#include "../include/GameBoard.h"
#include <curses.h>

/**
 * @brief Setzt das Spielbrett in die Spielbrett-Darstellung.
 * @param gameBoard
 */
void ViewBoardSetGameBoard(GameBoard gameBoard);

/**
 * @brief Nimmt die Tastatur eingaben fuer die Spielbrett-Darstellung entgegen.
 * @param pressedKey
 */
void ViewBoardPressedKeyCall(int pressedKey);

/**
 * @brief Stellt das Spielbrett dar.
 */
void ViewBoardPaintCall();

#endif