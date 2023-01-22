/**
 * @file main.c TicTacToe Game 
 * @author Fabian Grubba, Paul Widholt, Adam Wegner (teilweise, im Code (GameAI.c) vermerkt)
 * @version 1.0
 * @date 2022-01-22
 *
 * @copyright Copyright (c) 2023
 *
 */
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
