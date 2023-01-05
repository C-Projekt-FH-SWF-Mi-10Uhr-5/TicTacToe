#ifndef GAMEMASTER_H
#define GAMEMASTER_H

#include "Player.h"

void GameMasterNext(PlayerList* list);

void GameMasterPlayerCall(Player player);

Player GameMasterGetNextPlayer(PlayerList* list);

char GameMasterGetActivePlayer();

#endif