/**
 * @file GameMaster.h
 * @author Fabian Grubba (grubba.fabiandavidjonah@fh-swf.de)
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

void GameMasterInit(PlayerList* playerList, GameBoard gameBoard);

void GameMasterReset();

void GameMasterNext();

void GameMasterPlayerCall(Player player);

Player GameMasterGetNextPlayer(PlayerList* list);

char GameMasterGetActivePlayer();

char GameMasterGetWinner();

int GameMasterGetCurrentPlayedGames();

int GameMasterGetWinnerAiLevel();

void GameMasterSaveWins();

#endif