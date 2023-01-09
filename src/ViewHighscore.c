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

    mvprintw(5, 5, "Gespielte Spiele insgesamt: %d", GameGetPlayedGames());
    mvprintw(6, 5, "Gewonnene Spiele: %c", '-');
    double playtime = GameGetPlaytime();
    TimePeriod period = GameConvertToPeriod(playtime);
    mvprintw(7, 5, "Spielzeit:");
    int versatz = 11;
    if (period.days!=0) {
        mvprintw(7, 5+versatz, "%d Tage, ", period.days);
        versatz+=12;
    }
    if (period.hours!=0) {
        mvprintw(7, 5+versatz, "%d Stunden, ", period.hours);
        versatz+=12;
    }
    if (period.minutes!=0) {
        mvprintw(7, 5+versatz, "%d Minuten, ",period.minutes);
        versatz+=12;
    }
    mvprintw(7, 5+versatz, "%d Sekunden", period.seconds);
    mvprintw(8, 5, "Spielzeit in Sekunden: %f", playtime);
    mvprintw(9, 5, "Back to Main Menu");

    mvprintw(ViewHighscoreIndex + 9, 4, ">");// Zeige das Ausgewaehlte Element an
}