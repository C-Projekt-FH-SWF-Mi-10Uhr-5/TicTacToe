/**
 * @file ViewBoard.h
 * @brief
 * @version 0.1
 * @date 2022-12-21
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef VIEWBOARD_H
#define VIEWBOARD_H

#include "GameBoard.h"
#include "GameMaster.h"
#include "Player.h"

#include <curses.h>

/**
 * @brief Setzt das Spielbrett in die Spielbrett-Darstellung.
 * @param gameBoard
 */
void ViewBoardShow(GameBoard gameBoard, PlayerList* playerList);

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