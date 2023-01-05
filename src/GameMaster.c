#include "../include/GameMaster.h"

char activePlayer = '\0';

void GameMasterNext(PlayerList* list) {
    Player nextPlayer = GameMasterGetNextPlayer(list);
    activePlayer = nextPlayer.symbol;
    GameMasterPlayerCall(nextPlayer);
}

void GameMasterPlayerCall(Player player) {

}

Player GameMasterGetNextPlayer(PlayerList* list) {
    if (activePlayer == '\0') {
        return list->player;
    }
    PlayerList* element = PlayerListFindOrLast(list, activePlayer);
    if (element->next != NULL) {
        return list->next->player;
    } else {
        return list->player;
    }
}

char GameMasterGetActivePlayer() {
    return activePlayer;
}
