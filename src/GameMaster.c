#include "../include/GameMaster.h"

#include "../include/Logger.h"

GameBoard   GameMasterGameBoard;
PlayerList* GameMasterPlayerList;
char        GameMasterActivePlayer = '\0';
char        GameMasterWinner=0; //Gewinner Variable

void GameMasterInit(PlayerList* playerList, GameBoard gameBoard) {
    GameMasterPlayerList = playerList;
    GameMasterGameBoard = gameBoard;
    GameMasterActivePlayer = '\0';
    GameMasterWinner=0; //Zuruecksetzen des Gewinners, falls man bereits eine Runde vorher gespielt hat
}

void GameMasterNext() {
    LOGGER_LOG ("GameMaster", "NEXT")
    if (GameMasterWinner != 0) {
        return;
    }
    Player nextPlayer = GameMasterGetNextPlayer(GameMasterPlayerList);
    GameMasterActivePlayer = nextPlayer.symbol;
    GameMasterPlayerCall(nextPlayer);
    if(CheckWinner(GameMasterGameBoard, nextPlayer.symbol) == 1) {
        GameMasterWinner = nextPlayer.symbol;
    }
}

void GameMasterPlayerCall(Player player) {
    if (player.isNPC) {
        GameGet()->pressedKeyCall = NULL;
        ComputerPlacement(GameMasterGameBoard); //Der Computer setzt ein O auf ein leeres Feld
    } else {
        GameGet()->pressedKeyCall = ViewBoardPressedKeyCall;
    }
}

Player GameMasterGetNextPlayer(PlayerList* list) {
    if (GameMasterActivePlayer == '\0') {
        return list->player;
    }
    PlayerList* element = PlayerListFindOrLast(list, GameMasterActivePlayer);
    if (element->next != NULL) {
        return list->next->player;
    } else {
        return list->player;
    }
}

char GameMasterGetActivePlayer() {
    return GameMasterActivePlayer;
}

char GameMasterGetWinner() {
    GameMasterWinner;
}
