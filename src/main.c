
#include "../include/Logger.h"
#include "../include/Game.h"
#include "../include/ViewMenu.h"


int main(int argc, char *argv[]) {
    LOGGER_INIT
    GameInit(ViewMenuPressedKeyCall, ViewMenuPaintCall);// Spiel einrichten mit Funktionspointer um das Hauptmenue darzustellen
    GameStart();// Spiel starten
    GameStop();// Spiel abraeumen
    LOGGER_CLOSE
    return 0;
}
