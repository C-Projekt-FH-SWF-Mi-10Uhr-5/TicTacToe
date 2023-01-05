
#include "../include/Game.h"
#include <curses.h>

Game *GameGet() {
    static Game game;// Erstelle eine Statische Strucktur vom Typ Spiel (Siehe Singelton)
    return &game;// Gib den Pointer auf die Statische Spiel Struktur zurueck
}

void GameInit(void (*pressedKeyCall)(int pressedKey), void (*paintCall)()) {
    // ===== Konfiguration des Fensters =====

    // addch(A_ALTCHARSET);

    initscr(); // leeres Fenster erzeugen
    cbreak();  // Puffern von Eingaben deaktivieren (kein ENTER noetig)
    noecho();  // Benutzereingaben unsichtbar (sichtbar machen mit echo())
    // nonl();
    // intrflush(stdscr, FALSE);
    keypad(stdscr, TRUE);  // Funktions- und Pfeiltasten erlauben
    nodelay(stdscr, TRUE); /* Verhindert Anhalten des Programms bei getch(),
                            * stattdessen wird kontinuierlich ERR zurueckgegeben
                            * solange keine Taste gedrueckt wird.
                            */
    curs_set(0);           // Cursor unsichtbar (0), sichtbar (1)

    Game *game = GameGet();
    game->quit = 0;
    game->pressedKeyCall = pressedKeyCall;
    game->gameLogicCall = NULL;
    game->paintCall = paintCall;
}

void GameStart() {
    // ===== Event loop =====

    int pressedKey;

    Game *game = GameGet();

    while (!game->quit) {// Game Loop

        // ===== Benutzereingaben =====

        if (game->pressedKeyCall != NULL) {
            pressedKey = getch(); // Eingabe einlesen

            if (pressedKey == ERR) {
                napms(10); // Pause in Millisekunden
            } else {
                (*game->pressedKeyCall)(pressedKey);// Funktionspointer aufruf fuer den Tasten input
            }
        } else {
            napms(10); // Pause in Millisekunden
        }

        if (game->gameLogicCall != NULL) {
            (*game->gameLogicCall)();// Funktionspointer aufruf fuer den Aufruf der Spiellogik
        }

        // ===== Ausgabe =====

        erase(); // Fensterinhalt leeren

        (*game->paintCall)();// Funktionspointer aufruf fuer die Grafig ausgabe

        refresh(); // Fensterinhalt aktualisieren

    }
}

void GameStop() {
    // ===== Programmende =====
    endwin(); // Fenster schliessen
}