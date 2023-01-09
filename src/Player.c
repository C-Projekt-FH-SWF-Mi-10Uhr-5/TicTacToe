#include "../include/Player.h"

PlayerList* PlayerListCreate(Player player) {
    PlayerList* list = (PlayerList *)malloc(sizeof(PlayerList));
    list->player = player;
    list->previous = NULL;
    list->next = NULL;
    return list;
}

void PlayerListDestroy(PlayerList** list) {
    if ((*list)->next != NULL) {
        PlayerListDestroy(&(*list)->next);
    }
    free(*list);
    (*list) = NULL;
}

Player* PlayerListAdd(PlayerList* list, char player) {
    PlayerList* find = PlayerListFindOrLast(list, player);
    if (find->player.symbol == player) {
        return &find->player;
    } else {
        PlayerList* newElement = (PlayerList *)malloc(sizeof(PlayerList));
        find->next = newElement;
        newElement->previous = find;
        newElement->next = NULL;
        newElement->player.symbol = player;
        newElement->player.aiLevel = 0;
        newElement->player.wins = 0;
        return &newElement->player;
    }
}

Player PlayerListRemove(PlayerList** list, char player) {
    PlayerList* find = PlayerListFindOrLast(*list, player);
    Player result;
    result.symbol = '\0';
    if (find->player.symbol == player) {
        result = find->player;
        if (find == *list) {
            if (find->next != NULL) {
                (*list) = find->next;
                find->next->previous = NULL;
                free(find);
            }
        } else {
            if (find->previous != NULL) {
                find->previous->next = find->next;
            }
            if (find->next != NULL) {
                find->next->previous = find->previous;
            }
            free(find);
        }
    }
    return result;
}

PlayerList* PlayerListFindOrLast(PlayerList* list, char player) {
    if (list->player.symbol != player && list->next != NULL) {
        return PlayerListFindOrLast(list->next, player);
    }
    return list;
}

void PlayerListSwap(PlayerList* list, char a, char b) {
    PlayerList* entryA = PlayerListFindOrLast(list, a);
    PlayerList* entryB = PlayerListFindOrLast(list, b);
    if (entryA->player.symbol == a && entryB->player.symbol == b) {
        Player temp = entryB->player;
        entryB->player = entryA->player;
        entryA->player = temp;
    }
}

PlayerList* PlayerGetRealPlayer(PlayerList* list) {
    if(list == NULL) { //Existiert die Liste nicht,
        return NULL; //wird "nichts" zurueckgegeben (Absicherung)
    }
    else if(list->player.aiLevel == 0) { //Ist der Spieler ein "echter" Spieler (Schwierigkeit = 0) wird dieser zurueckgegeben
        return list;
    }
    else {
        return PlayerGetRealPlayer(list->next); //Ansonsten wird der naechste Spieler aus der Liste rekursiv aufgerufen 
    }
}
