/**
 * @file GameBoard.h
 * @author Fabian Grubba (grubba.fabiandavidjonah@fh-swf.de)
 * @brief
 * @version 0.1
 * @date 2022-12-21
 *
 * @copyright Copyright (c) 2022
 *
 * Beispiel:
 *  GameBoard gb = GameBoardCreate(3, 3);
 *  GameBoardSet(gb, 0, 0, '1');
 *  GameBoardSet(gb, 1, 0, '2');
 *  GameBoardSet(gb, 2, 0, '3');
 *  GameBoardSet(gb, 0, 1, '4');
 *  GameBoardSet(gb, 1, 1, '5');
 *  GameBoardSet(gb, 2, 1, '6');
 *  GameBoardSet(gb, 0, 2, '7');
 *  GameBoardSet(gb, 1, 2, '8');
 *  GameBoardSet(gb, 2, 2, '9');
 *  GameBoardDestroy(&gb);
 *
 */
#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Die Struktur GameBoard stellet ein Spielbrett dar.
 */
typedef struct {
    char *board;
    int columns, rows;
} GameBoard;

/**
 * @brief Erzeugt das Spielbrett in der endsprechenden Groesse mit Zeilen und
 * Spalten.
 * @param columns
 * @param rows
 * @return GameBoard
 */
GameBoard GameBoardCreate(int columns, int rows);

/**
 * @brief Gibt den Speicher des Spielbretts wieder frei und loescht den Pointer.
 * @param gb
 */
void GameBoardDestroy(GameBoard *gb);

/**
 * @brief Leert alle Felder des Spielebretts. Setzt sie auf ' '.
 * @param gb
 */
void GameBoardClear(GameBoard gb);

/**
 * @brief Setzt das entsprechende Zeichen an der Entsprechenden Stelle auf dem
 * Spielbrett.
 * @param gb
 * @param column
 * @param row
 * @param c
 */
void GameBoardSet(GameBoard gb, int column, int row, char c);

/**
 * @brief Gibt das entsprechende Zeichen an der Entsprechenden Stelle auf dem
 * Spielbrett zurueck.
 * @param gb
 * @param column
 * @param row
 * @return char
 */
char GameBoardGet(GameBoard gb, int column, int row);

/**
 * @brief Gibt den Pointer der Entsprechenden Stelle auf dem Spielbrett zurueck.
 * @param gb
 * @param column
 * @param row
 * @return char*
 */
char *GameBoardIndexOf(GameBoard gb, int column, int row);

/**
 * @brief Gibt das Spielbrett auf der console aus.
 * @param gb
 * @deprecated Nicht mehr relevant weil wir ViewBoard haben. Vielleicht
 * entfaernen.
 */
void GameBoardPrint(GameBoard gb);

#endif