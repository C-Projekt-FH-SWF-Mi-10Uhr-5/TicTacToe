
#include "../include/ViewMenu.h"

#include "../include/Game.h"
#include "../include/ViewBoard.h"

#include <curses.h>

char ViewMenuAusgabe = ' ';// Welche Cursortaste wurde gedrueckt (TODO: Spaeter etfernen)
int ViewMenuMenueIndex = 0;// Das aktuell ausgewaelte Element im Hauptmenue

void ViewMenuPressedKeyCall(int pressedKey) {
    switch (pressedKey) {
    case KEY_UP:
        ViewMenuAusgabe = '^';
        ViewMenuMenueIndex--;
        break;
    case KEY_DOWN:
        ViewMenuAusgabe = 'v';
        ViewMenuMenueIndex++;
        break;
    case KEY_LEFT:
        ViewMenuAusgabe = '<';
        break;
    case KEY_RIGHT:
        ViewMenuAusgabe = '>';
        break;
    case 'q':
        GameGet()->quit = 1;// Stoppe die Gameloop und beende das Spiel (TODO: Spaeter etfernen)
        break;
    case KEY_ENTER:
    case ' ':
    case '\n':
        switch (ViewMenuMenueIndex) {
        case 0: // Singleplayer
            ViewBoardSetGameBoard(GameBoardCreate(3, 3));// Erstelle und Setze 3x3 Spielfeld
            GameGet()->pressedKeyCall = ViewBoardPressedKeyCall;// Setze die Methode ViewBoardPressedKeyCall um die Tasteneingabe im Spielbrett entgegenzu nehmen
            GameGet()->paintCall = ViewBoardPaintCall;// Setze die Methode ViewBoardPaintCall um das Spielbrett darzustellen
            break;
        case 1: // Multiplayer
            break;
        case 2: // Highscore
            break;
        case 3: // Settings
            break;
        case 4: // Exit
            GameGet()->quit = 1; // Stoppe die Gameloop und beende das Spiel
            break;
        }
        break;
    }
    if (ViewMenuMenueIndex < 0) {
        ViewMenuMenueIndex = 4;// Springe zum letzten Eintrag
    } else if (ViewMenuMenueIndex > 4) {
        ViewMenuMenueIndex = 0;// Springe zum ersten Eintrag
    }
}

void ViewMenuPaintCall() {// Stelle das Hauptmenue dar
    mvprintw(0, 0, "Steuern mit Pfeiltasten, Beenden mit 'q'");
    mvprintw(3, 5, "%c", ViewMenuAusgabe);

    mvprintw(5, 5, "Singleplayer");
    mvprintw(6, 5, "Multiplayer");
    mvprintw(7, 5, "Highscore");
    mvprintw(8, 5, "Settings");
    mvprintw(9, 5, "Exit");

    mvprintw(ViewMenuMenueIndex + 5, 4, ">");// Zeige das Ausgewaelte Element an
}
