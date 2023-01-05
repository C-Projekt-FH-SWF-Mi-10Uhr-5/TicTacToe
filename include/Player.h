#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char symbol;
    int isNPC;
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

#endif