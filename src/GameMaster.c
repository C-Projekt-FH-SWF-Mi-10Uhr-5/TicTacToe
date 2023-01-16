#include "../include/GameMaster.h"

#include "../include/Logger.h"

#include <stdlib.h>
#include <time.h>

GameBoard   GameMasterGameBoard;
PlayerList* GameMasterPlayerList = NULL;
char        GameMasterActivePlayer = '\0';
char        GameMasterWinner = 0; //Gewinner Variable
int         GameMasterCurrentPlayedGames = 0; //Zurzeit gespielte Spiele (Anzeige in ViewBoard) (temporaer)

void GameMasterInit(PlayerList* playerList, GameBoard gameBoard) {
    GameMasterCurrentPlayedGames = 0; //Zuruecksetzen der zurzeit gespielten Spiele, da sie nur innerhalb einer Session gecounted werden sollen
    GameMasterPlayerList = playerList;
    GameMasterGameBoard = gameBoard;
    GameMasterReset();
}

void GameMasterReset() {
    GameMasterActivePlayer = '\0';
    GameMasterWinner = 0; //Zuruecksetzen des Gewinners, falls man bereits eine Runde vorher gespielt hat

    srand(time(NULL));
    if (rand()%2)
        PlayerListSwap(GameMasterPlayerList, GameMasterPlayerList->player.symbol, GameMasterPlayerList->next->player.symbol);
}

void GameMasterNext() {
    LOGGER_LOG ("GameMaster", "NEXT")
    if (GameMasterWinner != 0) {//Das spiel ist vorbei (Es gibt einen gewinner)
        GameMasterActivePlayer = '\0';
        return;
    }
    if(GameMasterActivePlayer != 0 && CheckWinner(GameMasterGameBoard, GameMasterActivePlayer) == 1) {//Haben wir einen Gewinner?
        GameMasterWinner = GameMasterActivePlayer;
        LOGGER_START("GameMaster", "log") LOGGER_STR("WINNER ") LOGGER_CHAR(GameMasterWinner) LOGGER_END()
        PlayerListFindOrLast(GameMasterPlayerList, GameMasterWinner)->player.wins++;
        GameMasterCurrentPlayedGames++; //Zurzeit gespielte Spiele wird um eins erhoeht
        GamePlayed();
        GameGet()->pressedKeyCall = ViewBoardPressedKeyCall;//Gib dem User die moeglichkeit zum handeln.
        return;
    }
    if (CheckEmptySpaces(GameMasterGameBoard)==0) {//Unentschieden!!
        GameMasterWinner = ' ';
        GameMasterActivePlayer = 0;
        LOGGER_START("GameMaster", "log") LOGGER_STR("TIE") LOGGER_END()
        GameMasterCurrentPlayedGames++; //Zurzeit gespielte Spiele wird um eins erhoeht
        GamePlayed();
        GameGet()->pressedKeyCall = ViewBoardPressedKeyCall;//Gib dem User die moeglichkeit zum handeln.
        return;
    }
    Player nextPlayer = GameMasterGetNextPlayer(GameMasterPlayerList);
    GameMasterActivePlayer = nextPlayer.symbol;
    GameMasterPlayerCall(nextPlayer);
}

void GameMasterPlayerCall(Player player) {
        LOGGER_START("GameMaster", "log") LOGGER_STR("player ") LOGGER_CHAR(player.symbol) LOGGER_INT(player.aiLevel) LOGGER_END()
    if (player.aiLevel) {
        GameGet()->pressedKeyCall = NULL;
        ComputerPlacement(GameMasterGameBoard, player.symbol, player.aiLevel); //Der Computer setzt ein O auf ein leeres Feld
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
        return element->next->player;
    } else {// Wir sind am Ende
        LOGGER_LOG ("GameMaster", "player")
        return list->player;// Wieder von vorne
    }
}

char GameMasterGetActivePlayer() {
    return GameMasterActivePlayer;
}

char GameMasterGetWinner() {
    return GameMasterWinner;
}

int GameMasterGetCurrentPlayedGames() {
    return GameMasterCurrentPlayedGames;
}

int GameMasterGetWinnerAiLevel() {
    if (GameMasterWinner != 0 && GameMasterWinner != ' ') {
        PlayerList* element = PlayerListFindOrLast(GameMasterPlayerList, GameMasterActivePlayer);
        return element->player.aiLevel;
    }
    return -1;
}

void GameMasterSaveWins() {
    PlayerList *RealPlayerList = PlayerGetRealPlayer(GameMasterPlayerList);
        if(RealPlayerList != NULL) {
            GameAddWins(RealPlayerList->player.wins);
        }
        else {
            LOGGER_START("ViewBoard", "err") LOGGER_STR("RealPlayerList is empty") LOGGER_END()
        }
}