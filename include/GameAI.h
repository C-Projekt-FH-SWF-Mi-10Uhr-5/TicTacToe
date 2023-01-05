/**
 * @file GameAI.h
 * @author Paul Widholt
 * @brief
 * @version 0.1
 * @date 2023-01-01
 */

#ifndef GAMEAI_H
#define GAMEAI_H

#include "GameBoard.h"

int CheckEmptySpaces(GameBoard gb);

void ComputerPlacement(GameBoard gb, int difficulty);

void PlayerPlacement(GameBoard gb, int ViewBoardY, int ViewBoardX);

int CheckWinner(GameBoard gb, char c);

#endif