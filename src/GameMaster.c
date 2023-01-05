#include "../include/GameMaster.h"

#include "../include/Logger.h"

GameBoard   GameMasterGameBoard;
PlayerList* GameMasterPlayerList;
char        GameMasterActivePlayer = '\0';
char        GameMasterWinner = 0; //Gewinner Variable

void GameMasterInit(PlayerList* playerList, GameBoard gameBoard) {
    GameMasterPlayerList = playerList;
    GameMasterGameBoard = gameBoard;
    GameMasterActivePlayer = '\0';
    GameMasterWinner = 0; //Zuruecksetzen des Gewinners, falls man bereits eine Runde vorher gespielt hat
}

void GameMasterNext() {
    LOGGER_LOG ("GameMaster", "NEXT")
    if (GameMasterWinner != 0) {
        GameMasterActivePlayer = '\0';
        return;
    }
    if(GameMasterActivePlayer != 0 && CheckWinner(GameMasterGameBoard, GameMasterActivePlayer) == 1) {
        GameMasterWinner = GameMasterActivePlayer;
        LOGGER_START("GameMaster", "log") LOGGER_STR("WINNER ") LOGGER_CHAR(GameMasterWinner) LOGGER_END()
        GameGet()->pressedKeyCall = ViewBoardPressedKeyCall;
        return;
    }
    Player nextPlayer = GameMasterGetNextPlayer(GameMasterPlayerList);
    GameMasterActivePlayer = nextPlayer.symbol;
    GameMasterPlayerCall(nextPlayer);
}

void GameMasterPlayerCall(Player player) {
        LOGGER_START("GameMaster", "log") LOGGER_STR("player ") LOGGER_CHAR(player.symbol) LOGGER_INT(player.kiLevel) LOGGER_END()
    if (player.kiLevel) {
        GameGet()->pressedKeyCall = NULL;
        ComputerPlacement(GameMasterGameBoard, player.kiLevel); //Der Computer setzt ein O auf ein leeres Feld
        GameMasterNext();
    } else {
        GameGet()->pressedKeyCall = ViewBoardPressedKeyCall;
    }
}

Player GameMasterGetNextPlayer(PlayerList* list) {
    LOGGER_START("GameMaster", "log") LOGGER_STR("ActP ") LOGGER_CHAR(GameMasterActivePlayer) LOGGER_STR(" ActP") LOGGER_END()
    if (GameMasterActivePlayer == '\0') {
        LOGGER_LOG ("GameMaster", "null")
        return list->player;
    }
    PlayerList* element = PlayerListFindOrLast(list, GameMasterActivePlayer);
    if (element->next != NULL) {
        LOGGER_LOG ("GameMaster", "next")
        return list->next->player;
    } else {
        LOGGER_LOG ("GameMaster", "player")
        return list->player;
    }
}

char GameMasterGetActivePlayer() {
    return GameMasterActivePlayer;
}

char GameMasterGetWinner() {
    return GameMasterWinner;
}
