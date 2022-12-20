#include "../include/GameBoard.h"

GameBoard GameBoardCreate(int columns, int rows) {
    GameBoard gb;
    gb.columns = columns;
    gb.rows = rows;
    gb.board = (char *)malloc(sizeof(char) * columns * rows);
    GameBoardClear(gb);
    return gb;
}

void GameBoardDestroy(GameBoard *gb) {
    free(gb->board);
    gb->board = NULL;
    gb->columns = 0;
    gb->rows = 0;
}

void GameBoardClear(GameBoard gb) {
    for (int i = 0; i < gb.columns; i++) {
        for (int j = 0; j < gb.rows; j++) {
            (*GameBoardIndexOf(gb, i, j)) = ' ';
        }
    }
}

void GameBoardSet(GameBoard gb, int column, int row, char c) {
    (*GameBoardIndexOf(gb, column, row)) = c;
    // printf("set %d = ( %d *  %d + %d ) %c\n", (column * gb.columns + row),
    // column, gb.columns, row, c);
}

char GameBoardGet(GameBoard gb, int column, int row) {
    return *GameBoardIndexOf(gb, column, row);
}

char *GameBoardIndexOf(GameBoard gb, int column, int row) {
    return gb.board + ((column * gb.rows) + row);
}

void GameBoardPrint(GameBoard gb) {
    for (int i = 0; i < gb.columns; i++) {
        for (int j = 0; j < gb.rows; j++) {
            printf("%c", *GameBoardIndexOf(gb, i, j));
            if (j + 1 < gb.rows) {
                printf("%c", 179);
            }
        }
        if (i + 1 < gb.rows - 1) {
            printf("\n");
            for (int j = 0; j < gb.rows; j++) {
                printf("%c", 196);
                if (j + 1 < gb.rows) {
                    printf("%c", 197);
                }
            }
        }
        printf("\n");
    }
}
