/**
 * @file Game.h
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
 * @brief Daten zum Speichern
 * Wird automatisch am Spielanfang geladen und am Spielende gespeihert.
 * Um einen Datenverlust beim Absturz zu verhindern wird auch nach einem gespeichert.
 */
typedef struct {

    /**
     * @brief Speichert die Spieldauer
     * @see GameGetPlaytime()
     */
    double playtime;

    /**
     * @brief Speichert die Anzahl der gespielten Spiele
     */
    int playedGames;

    /**
     * @brief Speichert die Anzahl der Gewinne
     */
    int wins;

} SaveGame;


/**
 * @brief 
 */
typedef struct {

    /**
     * @brief Die Anzahl der vergangenen Tage
     */
    unsigned int days;

    /**
     * @brief Die Anzahl der vergangenen Stunden
     */
    unsigned short hours;

    /**
     * @brief Die Anzahl der vergangenen Minuten
     */
    unsigned short minutes;

    /**
     * @brief Die Anzahl der vergangenen Sekunden
     */
    unsigned short seconds;

} TimePeriod;


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

/**
 * @brief Gib die gespielten Spiele zurueck
 * @return int 
 */
int GameGetPlayedGames();

/**
 * @brief Gib die Spielzeit zurueck
 * @return double 
 */
double GameGetPlaytime();

/**
 * @brief Informirt Game darueber, dass ein Spiel gespielt wurde
 */
void GamePlayed();

/**
 * @brief Speichert die vom Spiel erhobenendaten
 * @see SaveGame
 */
void GameSave();

/**
 * @brief Wandel die Zeit in fuer uns gut lesbare Einheiten um
 * @param d 
 * @return TimePeriod 
 */
TimePeriod GameConvertToPeriod(double d);

/**
 * @brief fuege die gewonnenen Spiele hinzu
 * @param wins 
 */
void GameAddWins(int wins);

/**
 * @brief gib die gewonnenen Spiele zurueck
 * @return int 
 */
int GameGetWins();

#endif