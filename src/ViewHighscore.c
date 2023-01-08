#include "../include/Game.h"
#include "../include/ViewMenu.h"

#include <stdio.h>
#include <curses.h>

int ViewHighscoreIndex = 0;



void ViewHighscorePressedKeyCall(int pressedKey) {
    switch(pressedKey) {
        case 'q':
            GameGet()->quit = 1;// Stoppe die Gameloop und beende das Spiel (TODO: Spaeter etfernen)
            break;
        case 'l': 
            GameGet()->pressedKeyCall = ViewMenuPressedKeyCall;// Setze die Methode ViewMenuPressedKeyCall um das Hauptmenue darzustellen
            GameGet()->paintCall = ViewMenuPaintCall;// Setze die Methode ViewBoardPaintCall um das Hauptmenue darzustellen
            break;
        case KEY_ENTER:
        case ' ':
        case '\n':
            switch(ViewHighscoreIndex) {
                case 0: //Back To Main Menu
                    GameGet()->pressedKeyCall = ViewMenuPressedKeyCall; // Setze die Methode ViewMenuPressedKeyCall um das Hauptmenue darzustellen
                    GameGet()->paintCall = ViewMenuPaintCall;// Setze die Methode ViewMenuPaintCall um das Hauptmenue darzustellen
                    break;                
            }
            break;
    }
}

void ViewHighscorePaintCall() {
    mvprintw(0, 0, "Steuern mit Pfeiltasten, Beenden mit 'q'");

    mvprintw(5, 5, "Gespielte Spiele insgesamt: %c", '-');
    mvprintw(6, 5, "Gewonnene Spiele: %c", '-');
    mvprintw(7, 5, "Spielzeit: %c", '-');
    mvprintw(8, 5, "Back to Main Menu");

    mvprintw(ViewHighscoreIndex + 8, 4, ">");// Zeige das Ausgewaehlte Element an
}