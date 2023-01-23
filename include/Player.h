/**
 * @file Player.h
 * @brief 
 * @version 0.1
 * @date 2023-01-05
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef PLAYER_H
#define PLAYER_H

#include <stdio.h>
#include <stdlib.h>


/**
 * @brief Diese Struktur stellt einen Spieler dar.
 */
typedef struct {

    /**
     * @brief Das Symbol fuer den Spieler auf dem Spielbrett
     */
    char symbol;

    /**
     * @brief Speichert ob der Spieler ein NPC ist oder nicht.
     *        Zusaetzlich wird noch gespeicher, wie sich die KI verhaelt.
     *        0   = Mensch
     *        1-2 = KI verhalten
     */
    int aiLevel;

    /**
     * @brief Anzahl der gewonnenen Spiele
     */
    int wins;

} Player;


/**
 * @brief Die Strucktur ist eine Verkettete Liste von Spielern
 */
typedef struct PlayerListStruct {

    /**
     * @brief Der Spieler
     */
    Player player;

    /**
     * @brief Vorheriger Spieler
     */
    struct PlayerListStruct* previous;

    /**
     * @brief Naechster Spieler
     */
    struct PlayerListStruct* next;

} PlayerList;


/**
 * @brief Erstellt eine Liste von Spielern
 * @param player Der erste Spieler
 * @return PlayerList* 
 */
PlayerList* PlayerListCreate(Player player);

/**
 * @brief Zerstoert die Liste mit den Spielern
 * @param list 
 */
void PlayerListDestroy(PlayerList** list);


/**
 * @brief Fuegt einen Spieler der Liste hinzu
 * @param list 
 * @param player Das Symbol des Spielers
 * @return Player* 
 */
Player* PlayerListAdd(PlayerList* list, char player);

/**
 * @brief Entfaernt einen Spieler aus der Liste
 * @param list 
 * @param player Das Symbol des Spielers
 * @return Player 
 */
Player PlayerListRemove(PlayerList** list, char player);

/**
 * @brief Findet einen Spieler in der Liste oder gibt den Letzen zurueck
 * @param list 
 * @param player Das Symbol des Spielers
 * @return PlayerList* 
 */
PlayerList* PlayerListFindOrLast(PlayerList* list, char player);

/**
 * @brief Tauscht zwei Spieler mit den Entsprechenden Symbolen
 * @param list 
 * @param a Das Symbol des Spielers A
 * @param b Das Symbol des Spielers B
 */
void PlayerListSwap(PlayerList* list, char a, char b);

/**
 * @brief Gibt den Listen eintrag mit dem menschlichen Spieler (keine KI) zurueck
 * @param list 
 * @return PlayerList* 
 */
PlayerList* PlayerGetRealPlayer(PlayerList* list);

#endif