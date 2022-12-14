
#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <stdio.h>
#include <stdlib.h>

typedef struct {
  char *board;
  int columns, rows;
} GameBoard;

GameBoard GameBoardCreate(int columns, int rows);

void GameBoardDestroy(GameBoard *gb);

void GameBoardClear(GameBoard gb);

void GameBoardSet(GameBoard gb, int column, int row, char c);
char GameBoardGet(GameBoard gb, int column, int row);

char *GameBoardIndexOf(GameBoard gb, int column, int row);

void GameBoardPrint(GameBoard gb);

#endif