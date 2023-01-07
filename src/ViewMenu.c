
#include "../include/ViewMenu.h"

#include "../include/Game.h"
#include "../include/Player.h"
#include "../include/ViewBoard.h"
#include "../include/ViewSettings.h"
#include "../include/ViewMultiplayer.h"

#include <curses.h>

char ViewMenuAusgabe = ' ';// Welche Cursortaste wurde gedrueckt (TODO: Spaeter etfernen)
int ViewMenuMenueIndex = 0;// Das aktuell ausgewaehlte Element im Hauptmenue

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
                {
                    Player player;
                    player.symbol = 'X';
                    player.kiLevel = 0;
                    PlayerList* playerList = PlayerListCreate(player);
                    Player* newPlayer = PlayerListAdd(playerList, '0');
                    newPlayer->kiLevel = 2;
                    ViewBoardShow(GameBoardCreate(3, 3), playerList);// Erstelle, Setze 3x3 Spielfeld und zeige es TODO: Nicht loeschen vom Spielfeld erzeugt ein Speicherloch!!
                }
                break;
            case 1: // Multiplayer
                GameGet()->pressedKeyCall = ViewMultiplayerPressedKeyCall; //Setze die Methode ViewMultiplayerPressedKeyCall um die Tasteneingabe in den Multiplayer Menue entgegenzunehmen
                GameGet()->paintCall = ViewMultiplayerPaintCall; //Setze die Methode ViewMultiplayerPaintCall um das Multiplayer Menue darzustellen
                break;
            case 2: // Highscore
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
