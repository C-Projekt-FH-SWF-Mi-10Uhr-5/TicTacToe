/**
 * @file GameMaster.h
 * @brief 
 * @version 0.1
 * @date 2023-01-05
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef GAMEMASTER_H
#define GAMEMASTER_H

#include "Game.h"
#include "GameBoard.h"
#include "GameAI.h"
#include "Player.h"
#include "ViewBoard.h"

/**
 * @brief Initalisire das Spiel
 * @param playerList 
 * @param gameBoard 
 */
void GameMasterInit(PlayerList* playerList, GameBoard gameBoard);

/**
 * @brief Starte die Partie neu
 */
void GameMasterReset();

/**
 * @brief Der nachste Spieler ist dran
 */
void GameMasterNext();

/**
 * @brief Ruf die passende Spiellogik fuer den entsprechenden Spieler auf
 * @param player 
 */
void GameMasterPlayerCall(Player player);

/**
 * @brief Gib den Spieler zurueck, welecher als naechstes an der Reihe ist
 * @param list 
 * @return Player 
 */
Player GameMasterGetNextPlayer(PlayerList* list);

/**
 * @brief Gib das Symbol des Spielers zurueck, welcher gerade an der Reihe ist
 * @return char 
 */
char GameMasterGetActivePlayer();

/**
 * @brief Gib das Symbol des Gewinners zurueck
 * @return char 
 */
char GameMasterGetWinner();

/**
 * @brief Gib die Anzahl der zur Zeit gespielten Spiele zurueck
 * @return int 
 */
int GameMasterGetCurrentPlayedGames();

/**
 * @brief Gib die KI einstellung des Gewinners zurueck
 * @return int 
 */
int GameMasterGetWinnerAiLevel();

/**
 * @brief Speicher die vom menschlichen Spieler gewonnen Spiele in Savegame
 */
void GameMasterSaveWins();

#endif