
#include "../include/Game.h"

#include <curses.h>
#include <stdio.h>
#include <time.h>

clock_t GameStartTimepoint;

SaveGame GameSaveGame;

Game *GameGet() {
    static Game game;// Erstelle eine Statische Strucktur vom Typ Spiel (Siehe Singelton)
    return &game;// Gib den Pointer auf die Statische Spiel Struktur zurueck
}

void GameInit(void (*pressedKeyCall)(int pressedKey), void (*paintCall)()) {
    GameStartTimepoint = clock(); // Zeitpunkt vom Spielstart merken

    // ===== Lade den Spielstand =====
    FILE *fp;
    fp = fopen(".tictactoe.save", "rb");
    if(fp != NULL) { // Konnte die Datei gelesen werden?
        fread(&GameSaveGame, sizeof(SaveGame), 1, fp);
    } else { // Ansonsten Defaults setzen
        GameSaveGame.playtime = 0.0;
        GameSaveGame.playedGames = 0;
        GameSaveGame.wins = 0;
    }
    fclose(fp);

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

    // ===== Game struktur einrichten =====
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

        /*if (is_term_resized()) {
            endwin();
            refresh();
            clear();
        }*/

        // ===== Benutzereingaben =====

        if (game->pressedKeyCall != NULL) {
            pressedKey = getch(); // Eingabe einlesen

            if (pressedKey == ERR) {
                napms(10); // Pause in Millisekunden
            }
            else {
                (*game->pressedKeyCall)(pressedKey);// Funktionspointer aufruf fuer den Tasten input
            }
        }
        else {
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
    GameSave();
    // ===== Programmende =====
    endwin(); // Fenster schliessen
}

int GameGetPlayedGames() {
    return GameSaveGame.playedGames;
}

double GameGetPlaytime() {
    return ( (double) (clock() - GameStartTimepoint) / CLOCKS_PER_SEC ) + GameSaveGame.playtime;
}

void GamePlayed() {
    GameSaveGame.playedGames++;
    GameSave();
}

void GameSave() {
    GameSaveGame.playtime = GameGetPlaytime(); // Berechne und setze die Spielzeit
    GameStartTimepoint = clock(); // Aktualisire die Spielzeit

    // ===== Spielstand speichern =====
    FILE *fp;
    fp = fopen(".tictactoe.save", "wb");
    if(fp != NULL) {
        fwrite(&GameSaveGame, sizeof(SaveGame), 1, fp);
    }
    fclose(fp);
}

TimePeriod GameConvertToPeriod(double d) {
    TimePeriod period;

    if (d > 86400) { // Sind mehrere Tage vergangen?
        period.days = d / 86400; // Tage berechnen
        d = ((int)d) % 86400; // restliche Zeit berechnen
    }
    else {
        period.days = 0;
    }

    if (d > 3600) { // Sind mehrere Stunden vergangen?
        period.hours =  d / 3600; // Stunden berechnen
        d = ((int)d) % 3600; // restliche Zeit berechnen
    }
    else {
        period.hours = 0;
    }

    if (d > 60) { // Sind mehrere Minuten vergangen?
        period.minutes = d / 60; // Minuten berechnen
        d = ((int)d) % 60; // restliche Zeit berechnen
    }
    else {
        period.minutes = 0;
    }

    period.seconds = d;

    return period;
}

void GameAddWins(int wins) {
    GameSaveGame.wins+=wins; // fuege die gewonnenen Spiele hinzu
    GameSave();
}

int GameGetWins() {
    return GameSaveGame.wins; // gib die gewonnenen Spiele zurueck
}