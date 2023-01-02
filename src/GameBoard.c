#include "../include/GameBoard.h"

GameBoard GameBoardCreate(int columns, int rows) {
    GameBoard gb;// Erstelle ein Spielbrett //asdsabhdbhdbh
    gb.columns = columns;// Setze die Anzahl der Spalten
    gb.rows = rows;// Setze die Anzahl der Zeilen
    gb.board = (char *)malloc(sizeof(char) * columns * rows);// Fordere den Speicher fuer das Spielbrett an
    GameBoardClear(gb);// Setze alle Zeichen auf leer
    return gb;
}

void GameBoardDestroy(GameBoard *gb) {// Uebergebe einen Pointer damit deutlich wird, dass die Struktur geloescht wurde
    free(gb->board);// Gib den speicher frei
    gb->board = NULL;// Setze der Pointer NULL um zu zeigen, dass die Struktur geloescht wurde
    gb->columns = 0;// Setze die Spalten auf 0 um zu zeigen, dass die Struktur geloescht wurde
    gb->rows = 0;// Setze die Zeilen auf 0 um zu zeigen, dass die Struktur geloescht wurde
}

void GameBoardClear(GameBoard gb) {// Setze alle Zeichen auf leer
    for (int i = 0; i < gb.columns; i++) {
        for (int j = 0; j < gb.rows; j++) {
            (*GameBoardIndexOf(gb, i, j)) = ' ';
        }
    }
}

void GameBoardSet(GameBoard gb, int column, int row, char c) {
    (*GameBoardIndexOf(gb, column, row)) = c;// Setzt das entsprechende Zeichen an der Entsprechenden Stelle auf dem Spielbrett
    // printf("set %d = ( %d *  %d + %d ) %c\n", (column * gb.columns + row),
    // column, gb.columns, row, c);
}

char GameBoardGet(GameBoard gb, int column, int row) {
    return *GameBoardIndexOf(gb, column, row);// Gibt das entsprechende Zeichen an der Entsprechenden Stelle auf dem Spielbrett zurueck
}

char *GameBoardIndexOf(GameBoard gb, int column, int row) {
    return gb.board + ((column * gb.rows) + row);// Gibt den Pointer der Entsprechenden Stelle auf dem Spielbrett zurueck
}

void GameBoardPrint(GameBoard gb) {// TODO: Nicht mehr relevant weil wir ViewBoard haben. Vielleicht entfaernen
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
