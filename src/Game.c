
#include <curses.h>

#include "Game.h"

Game *GameGet() {
    static Game game;
    return &game;
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
    game->paintCall = paintCall;
}

void GameStart() {
    // ===== Event loop =====

    int pressedKey;

    Game *game = GameGet();

    while (!game->quit) {
        // ===== Benutzereingaben =====

        pressedKey = getch(); // Eingabe einlesen

        if (pressedKey == ERR) {
            napms(10); // Pause in Millisekunden
        } else {
            (*game->pressedKeyCall)(pressedKey);
        }

        // ===== Ausgabe =====

        erase(); // Fensterinhalt leeren

        (*game->paintCall)();

        refresh(); // Fensterinhalt aktualisieren
    }
}

void GameStop() {
    // ===== Programmende =====
    endwin(); // Fenster schliessen
}