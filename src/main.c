
#include "../include/Game.h"
#include "../include/ViewMenu.h"

int main(int argc, char *argv[]) {

    GameInit(ViewMenuPressedKeyCall, ViewMenuPaintCall);// Spiel einrichten mit Funktionspointer um das Hauptmenue darzustellen
    GameStart();// Spiel starten
    GameStop();// Spiel abraeumen

    return 0;
}
