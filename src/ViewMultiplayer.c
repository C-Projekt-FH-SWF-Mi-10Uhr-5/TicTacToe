#include "../include/Game.h"
#include "../include/ViewMenu.h"
#include "../include/ViewBoard.h"
#include "../include/ViewMultiplayer.h"

#include <stdio.h>
#include <curses.h>

char ViewMultiplayerAusgabe = ' ';
int ViewMultiplayerIndex = 0;
GameBoard ViewMultiplayerGameBoard;
PlayerList* ViewMultiplayerPlayerList = NULL;

void ViewMultiplayerPressedKeyCall(int pressedKey) {
    switch (pressedKey) {
        case KEY_UP:
            ViewMultiplayerAusgabe = '^';
            ViewMultiplayerIndex--;
            break;
        case KEY_DOWN:
            ViewMultiplayerAusgabe = 'v';
            ViewMultiplayerIndex++;
            break;
        case KEY_LEFT:
            ViewMultiplayerAusgabe = '<';
            break;
        case KEY_RIGHT:
            ViewMultiplayerAusgabe = '>';
            break;
        case 'q':
            GameGet()->quit = 1;// Stoppe die Gameloop und beende das Spiel
            break;
        case 'l':
            ViewMultiplayerIndex = 0; //Zuruecksetzen des Einstellungen Indexes 
            GameGet()->pressedKeyCall = ViewMenuPressedKeyCall;// Setze die Methode ViewMenuPressedKeyCall um das Hauptmenue darzustellen
            GameGet()->paintCall = ViewMenuPaintCall;// Setze die Methode ViewBoardPaintCall um das Hauptmenue darzustellen
            break;
        case KEY_ENTER:
        case ' ':
        case '\n':
            switch(ViewMultiplayerIndex) {
                case 0: // 2 Spieler
                    {
                        GameBoardDestroy(&ViewMultiplayerGameBoard); // Zerstore das vorherige
                        ViewMultiplayerGameBoard = GameBoardCreate(3, 3); // Erstelle ein 3x3 Spielfeld
                        if (ViewMultiplayerPlayerList != NULL) {
                            PlayerListDestroy(&ViewMultiplayerPlayerList);
                        }
                        Player player;
                        player.symbol = 'X';
                        player.aiLevel = 0;
                        ViewMultiplayerPlayerList = PlayerListCreate(player);
                        Player* newPlayer = PlayerListAdd(ViewMultiplayerPlayerList, '0');
                        newPlayer->aiLevel = 0;
                        ViewBoardShow(ViewMultiplayerGameBoard, ViewMultiplayerPlayerList);// Erstelle, Setze 3x3 Spielfeld und zeige es
                    }
                    break;
                case 1: //3 Spieler
                    {
                        GameBoardDestroy(&ViewMultiplayerGameBoard); // Zerstore das vorherige
                        ViewMultiplayerGameBoard = GameBoardCreate(4, 4); // Erstelle ein 3x3 Spielfeld
                        if (ViewMultiplayerPlayerList != NULL) {
                            PlayerListDestroy(&ViewMultiplayerPlayerList);
                        }
                        Player player;
                        player.symbol = '1';
                        player.aiLevel = 0;
                        ViewMultiplayerPlayerList = PlayerListCreate(player);
                        Player* newPlayer = PlayerListAdd(ViewMultiplayerPlayerList, '2');
                        newPlayer->aiLevel = 0;
                        newPlayer = PlayerListAdd(ViewMultiplayerPlayerList, '3');
                        newPlayer->aiLevel = 0;
                        ViewBoardShow(ViewMultiplayerGameBoard, ViewMultiplayerPlayerList);// Erstelle, Setze 3x3 Spielfeld und zeige es
                    }
                    break;
                case 2: //4 Spieler
                    {
                        GameBoardDestroy(&ViewMultiplayerGameBoard); // Zerstore das vorherige
                        ViewMultiplayerGameBoard = GameBoardCreate(5, 5); // Erstelle ein 3x3 Spielfeld
                        if (ViewMultiplayerPlayerList != NULL) {
                            PlayerListDestroy(&ViewMultiplayerPlayerList);
                        }
                        Player player;
                        player.symbol = '1';
                        player.aiLevel = 0;
                        ViewMultiplayerPlayerList = PlayerListCreate(player);
                        Player* newPlayer = PlayerListAdd(ViewMultiplayerPlayerList, '2');
                        newPlayer->aiLevel = 0;
                        newPlayer = PlayerListAdd(ViewMultiplayerPlayerList, '3');
                        newPlayer->aiLevel = 0;
                        newPlayer = PlayerListAdd(ViewMultiplayerPlayerList, '4');
                        newPlayer->aiLevel = 0;
                        ViewBoardShow(ViewMultiplayerGameBoard, ViewMultiplayerPlayerList);// Erstelle, Setze 3x3 Spielfeld und zeige es
                    }
                    break;
                case 3: //Back To Main Menu
                    ViewMultiplayerIndex = 0; //Setze den Index des Multiplayer Menues zurueck
                    GameGet()->pressedKeyCall = ViewMenuPressedKeyCall; // Setze die Methode ViewMenuPressedKeyCall um das Hauptmenue darzustellen
                    GameGet()->paintCall = ViewMenuPaintCall;// Setze die Methode ViewMenuPaintCall um das Hauptmenue darzustellen
                    break;                
            }
            break;
    }
    if (ViewMultiplayerIndex < 0) {
        ViewMultiplayerIndex = 3;// Springe zum letzten Eintrag
    } 
    else if (ViewMultiplayerIndex > 3) {
        ViewMultiplayerIndex = 0;// Springe zum ersten Eintrag
    }
}

void ViewMultiplayerPaintCall() {
    mvprintw(0, 0, "Steuern mit Pfeiltasten, Beenden mit 'q'");
    mvprintw(3, 5, "%c", ViewMultiplayerAusgabe);

    mvprintw(5, 5, "2 Spieler");
    mvprintw(6, 5, "3 Spieler");
    mvprintw(7, 5, "4 Spieler");
    mvprintw(8, 5, "Back to Main Menu");

    mvprintw(ViewMultiplayerIndex + 5, 4, ">");// Zeige das Ausgewaelte Element an
}