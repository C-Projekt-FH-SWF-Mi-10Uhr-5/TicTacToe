/**
 * @file GameAI.h
 * @brief
 * @version 0.1
 * @date 2023-01-01
 */

#ifndef GAMEAI_H
#define GAMEAI_H

#include "GameBoard.h"

int CheckEmptySpaces(GameBoard gb);

void ComputerPlacement(GameBoard gb, char c, int difficulty);

void PlayerPlacement(GameBoard gb, char c, int ViewBoardY, int ViewBoardX);

int CheckWinner(GameBoard gb, char c);

#endif