/**
 * @file Game.h
 * @author Fabian Grubba (grubba.fabiandavidjonah@fh-swf.de)
 * @brief
 * @version 0.1
 * @date 2022-12-21
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef GAME_H
#define GAME_H

#include <curses.h>

/**
 * @brief Die Strucktur Game beinhaltet alle wichtigen Einstellungen um das
 * Speil zu steuern. Sie kann einfach erweitert werden um neue
 * Funktionalitaeten.
 * Die Funktionspointer pressedKeyCall und paintCall muessen unbedingt gesetzt
 * sein, sonst crasht das Spiel.
 */
typedef struct {

    /**
     * @brief Funktionspointer zustaendig fuer den Tasteninput
     */
    void (*pressedKeyCall)(int pressedKey);

    /**
     * @brief Funktionspointer zustaendig fuer den Aufruf der Spiellogik
     */
    void (*gameLogicCall)();

    /**
     * @brief Funktionspointer zustaendig fuer die Darstellung des spiels
     */
    void (*paintCall)();

    /**
     * @brief quit = 1 Beendet das Spiel
     */
    int quit;

} Game;

/**
 * @brief Gibt einen Pinter zurueck der auf die Strucktur vom Typ Game zeigt
 * @return Game*
 */
Game *GameGet();

/**
 * @brief Initialisiert die Strucktur vom Typ Game. Die Funktionspointer
 * pressedKeyCall und paintCall muessen unbedingt gesetzt sein, sonst crasht das
 * Spiel.
 * @param pressedKeyCall
 * @param paintCall
 */
void GameInit(void (*pressedKeyCall)(int pressedKey), void (*paintCall)());

/**
 * @brief Startet das spiel.
 */
void GameStart();

/**
 * @brief Sollte nach dem Spielstart aufgerufen werden. Diese Methode raeumt
 * auf.
 */
void GameStop();

#endif