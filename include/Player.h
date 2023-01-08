/**
 * @file Player.h
 * @author Fabian Grubba (grubba.fabiandavidjonah@fh-swf.de)
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

typedef struct {
    char symbol;
    int kiLevel;
} Player;

typedef struct PlayerListStruct {

    Player player;
    struct PlayerListStruct* previous;
    struct PlayerListStruct* next;

} PlayerList;

PlayerList* PlayerListCreate(Player player);
void PlayerListDestroy(PlayerList** list);

Player* PlayerListAdd(PlayerList* list, char player);
Player PlayerListRemove(PlayerList** list, char player);
PlayerList* PlayerListFindOrLast(PlayerList* list, char player);
void PlayerListSwap(PlayerList* list, char a, char b);

#endif