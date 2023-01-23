
#include "../include/ViewMenu.h"

#include "../include/Game.h"
#include "../include/Player.h"
#include "../include/ViewBoard.h"
#include "../include/ViewSettings.h"
#include "../include/ViewHighscore.h"

#include <curses.h>

char ViewMenuAusgabe = ' ';// Welche Cursortaste wurde gedrueckt
int ViewMenuMenueIndex = 0;// Das aktuell ausgewaehlte Element im Hauptmenue
GameBoard ViewMenuGameBoard;
PlayerList* ViewMenuPlayerList = NULL;

void ViewMenuShow() {
    GameGet()->pressedKeyCall = ViewMenuPressedKeyCall;// Setze die Methode ViewMenuPressedKeyCall um das Hauptmenue darzustellen
    GameGet()->paintCall = ViewMenuPaintCall;// Setze die Methode ViewBoardPaintCall um das Hauptmenue darzustellen
}

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
            GameGet()->quit = 1;// Stoppe die Gameloop und beende das Spiel
            break;
        case KEY_ENTER:
        case ' ':
        case '\n':
            switch (ViewMenuMenueIndex) {
            case 0: // Singleplayer
                {
                    GameBoardDestroy(&ViewMenuGameBoard); // Zerstore das vorherige
                    ViewMenuGameBoard = GameBoardCreate(3, 3); // Erstelle ein 3x3 Spielfeld
                    if (ViewMenuPlayerList != NULL) {
                        PlayerListDestroy(&ViewMenuPlayerList);
                    }
                    Player player;
                    player.symbol = Player1Symbol;
                    player.aiLevel = 0;
                    player.wins = 0;
                    ViewMenuPlayerList = PlayerListCreate(player);
                    Player* newPlayer = PlayerListAdd(ViewMenuPlayerList, Player2Symbol);
                    newPlayer->aiLevel = Difficulty;
                    ViewBoardShow(ViewMenuGameBoard, ViewMenuPlayerList);// Setze 3x3 Spielfeld und zeige es
                }
                break;
            case 1: // Multiplayer
                {
                    GameBoardDestroy(&ViewMenuGameBoard); // Zerstore das vorherige
                    ViewMenuGameBoard = GameBoardCreate(3, 3); // Erstelle ein 3x3 Spielfeld
                    if (ViewMenuPlayerList != NULL) {
                        PlayerListDestroy(&ViewMenuPlayerList);
                    }
                    Player player;
                    player.symbol = Player1Symbol;
                    player.aiLevel = 0;
                    player.wins = 0;
                    ViewMenuPlayerList = PlayerListCreate(player);
                    Player* newPlayer = PlayerListAdd(ViewMenuPlayerList, Player2Symbol);
                    newPlayer->aiLevel = 0;
                    ViewBoardShow(ViewMenuGameBoard, ViewMenuPlayerList);// Setze 3x3 Spielfeld und zeige es
                }
                break;
            case 2: // Highscore
                GameGet()->pressedKeyCall = ViewHighscorePressedKeyCall; //Uebergebe die Tasteneingabe an das Highscore Menue
                GameGet()->paintCall = ViewHighscorePaintCall; //Lasse das Highscore Menue darstellen
                break;
            case 3: // Settings
                GameGet()->pressedKeyCall = ViewSettingsPressedKeyCall; //Setze die Methode ViewSettingsPressedKeyCall um die Tasteneingabe in den Einstellungen entgegenzunehmen
                GameGet()->paintCall = ViewSettingsPaintCall; //Setze die Methode ViewSettingsPaintCall um die Einstellungen darzustellen
                break;
            case 4: // Exit
                GameGet()->quit = 1; // Stoppe die Gameloop und beende das Spiel
                break;
            }
            break;
    }
    if (ViewMenuMenueIndex < 0) {
        ViewMenuMenueIndex = 4;// Springe zum letzten Eintrag
    } 
    else if (ViewMenuMenueIndex > 4) {
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
