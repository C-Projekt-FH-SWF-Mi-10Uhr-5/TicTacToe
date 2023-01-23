#include "../include/Player.h"

PlayerList* PlayerListCreate(Player player) {
    PlayerList* list = (PlayerList *)malloc(sizeof(PlayerList)); // Fordert Speicher vom Heap fuer die Liste an
    list->player = player; // Fuege den Spieler ein
    list->previous = NULL; // Kein vorheriges Element da
    list->next = NULL; // und noch kein naechste Element da
    return list;
}

void PlayerListDestroy(PlayerList** list) {
    if ((*list)->next != NULL) { // Hat die List ein naechstes Element?
        PlayerListDestroy(&(*list)->next); // Zerstoere die Liste rekursiv
    }
    free(*list); // gib das Listenelement frei
    (*list) = NULL; // setze den Pointer auf NULL um zu zeigen, dass der Speicher freigegeben wurde
}

Player* PlayerListAdd(PlayerList* list, char player) {
    PlayerList* find = PlayerListFindOrLast(list, player); // Ist bereits ein Spieler in der List mit dem Symbol?
    if (find->player.symbol == player) {
        return &find->player; // Gib den gefunden Spieler zuruck (als Pointer zum Modifiziren)
    }
    else {
        PlayerList* newElement = (PlayerList *)malloc(sizeof(PlayerList)); // Erstelle einen neuen Listeneintrag
        find->next = newElement; // Verkette den neuen Eintrag
        newElement->previous = find; // Setze den Rueckweg
        newElement->next = NULL;
        newElement->player.symbol = player; // Setze das Spielersymbol
        newElement->player.aiLevel = 0; // Initialisire den KI eintrag
        newElement->player.wins = 0; // Initialisire die gewonnen Spiele
        return &newElement->player; // Gib den erstelten Spieler zuruck (als Pointer zum Modifiziren)
    }
}

Player PlayerListRemove(PlayerList** list, char player) {
    PlayerList* find = PlayerListFindOrLast(*list, player); // Versuche den Spieler zu finden
    Player result;
    result.symbol = '\0';
    if (find->player.symbol == player) { // Wurde der Spieler gefunden?
        result = find->player;
        if (find == *list) { // Soll das erste Element geloescht werden
            if (find->next != NULL) {// Haben wir ein naechste Element
                (*list) = find->next; // Setze das Nachste als erstes Element
                find->next->previous = NULL; // Das Erste element hat kein vorheriges
                free(find); // Loesche das erste Element
            }
        }
        else {
            if (find->previous != NULL) { // Haben wir ein vorheriges Element?
                find->previous->next = find->next; // Ersetzte das zuloechende Element
            }
            if (find->next != NULL) { // Haben wir ein nachfolgendes Element?
                find->next->previous = find->previous; // Ersetzte das zuloechende Element
            }
            free(find); // Loesche das Element
        }
    }
    return result; // Gib den Spieler des geloeschten Eintrags zuruck
}

PlayerList* PlayerListFindOrLast(PlayerList* list, char player) {
    if (list->player.symbol != player && list->next != NULL) { // Ist das Symbol ungleich und haben wir einen naechsten Eintrag
        return PlayerListFindOrLast(list->next, player); // Weiter zum naechsten
    }
    return list;
}

void PlayerListSwap(PlayerList* list, char a, char b) {
    PlayerList* entryA = PlayerListFindOrLast(list, a); // Finde den Ersten
    PlayerList* entryB = PlayerListFindOrLast(list, b); // Finde den Zweiten
    if (entryA->player.symbol == a && entryB->player.symbol == b) { // Beide gefunden?
        Player temp = entryB->player; // Speicher den Zweiten zwischen
        entryB->player = entryA->player; // Ersetze den Zweiten mit dem Ersten
        entryA->player = temp; // Ersetze den Ersten mit dem Zweiten (Zwischengespeichert)
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
