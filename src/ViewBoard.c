
#include "../include/ViewBoard.h"

#include "../include/Game.h"
#include "../include/ViewMenu.h"

#include "../include/GameAI.h"
#include "../include/Logger.h"

#include <curses.h>

char ViewBoardAusgabe = ' ';// Welche Cursortaste wurde gedrueckt (TODO: Spaeter etfernen)
int ViewBoardX, ViewBoardY;// Aktuell ausgewaeltes Feld im Spielbrett
GameBoard ViewBoardGB;// Das darzustellende Spielbrett
int CheckPlacedSlot=0; //Wert, der angibt ob ein Feld bereits besetzt ist (=1) oder noch frei ist (=0)

void ViewBoardShow(GameBoard gameBoard, PlayerList* playerList) {
    ViewBoardGB = gameBoard; // Setze das Spielbrett in die Darstellung
    GameMasterInit(playerList, gameBoard);// TODO: Nicht loeschen der PlayerList erzeugt ein speicherloch!!!!!1!!11
    GameGet()->paintCall = ViewBoardPaintCall;// Setze die Methode ViewBoardPaintCall um das Spielbrett darzustellen
    GameMasterNext();
}

void ViewBoardPressedKeyCall(int pressedKey) {
    switch (pressedKey) {
    case KEY_UP:
        ViewBoardAusgabe = '^';
        ViewBoardY--;
        break;
    case KEY_DOWN:
        ViewBoardAusgabe = 'v';
        ViewBoardY++;
        break;
    case KEY_LEFT:
        ViewBoardAusgabe = '<';
        ViewBoardX--;
        break;
    case KEY_RIGHT:
        ViewBoardAusgabe = '>';
        ViewBoardX++;
        break;
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
        CheckPlacedSlot=0; //Ruecksetzen des Fehlerwertes
        if(*GameBoardIndexOf(ViewBoardGB, ViewBoardY, ViewBoardX) == ' ') { //Ueberpruefe, ob das Feld frei ist
            PlayerPlacement(ViewBoardGB, GameMasterGetActivePlayer(), ViewBoardY, ViewBoardX); //Setze ein X auf das entsprechende Feld
            GameMasterNext();
        }
        else {
            CheckPlacedSlot=1; //Ist das Feld nicht frei, wird ein Fehlerwert uebergeben
        }
        break;
    }

    if (ViewBoardX < 0) {
        ViewBoardX = ViewBoardGB.columns - 1;
    } else if (ViewBoardX > ViewBoardGB.columns-1) {
        ViewBoardX = 0;
    }
    if (ViewBoardY < 0) {
        ViewBoardY = ViewBoardGB.rows - 1;
    } else if (ViewBoardY > ViewBoardGB.rows-1) {
        ViewBoardY = 0;
    }
}

void ViewBoardPaintCall() {// Stelle das Spielbrett dar (TODO: Bessere darstellung)
    mvprintw(0, 0, "Steuern mit Pfeiltasten, Beenden mit 'q'");
    mvprintw(3, 5, "%c", ViewBoardAusgabe);

    int row = 5;
    int col = 5;

    for (int i = 0; i < ViewBoardGB.columns; i++) {
        for (int j = 0; j < ViewBoardGB.rows; j++) {
            mvprintw(row, col, "%c", *GameBoardIndexOf(ViewBoardGB, i, j));
            col++;
            if (j + 1 < ViewBoardGB.rows) {
                mvprintw(row, col, "%c", '|'); // 179
                col++;
            }
        }
        if (i + 1 < ViewBoardGB.rows) {
            row++;
            col = 5;
            for (int j = 0; j < ViewBoardGB.rows; j++) {
                mvprintw(row, col, "%c", '-'); // 196
                col++;
                if (j + 1 < ViewBoardGB.rows) {
                    mvprintw(row, col, "%c", '+'); // 197
                    col++;
                }
            }
        }
        row++;
        col = 5;
    }
    if(CheckPlacedSlot == 1) { //Gebe eine Fehlermeldung aus, wenn das ausgewaehlte Feld bereits besetzt ist
        mvprintw(1, 0, "Fehlerhafte Eingabe, versuche erneut");
    } else {
        char activePlayer =  GameMasterGetActivePlayer();
        char buf[22] = "~ ist an der Reihe...\0";
        buf[0] = activePlayer;
        mvprintw(1, 0, buf);
    }
    char Winner = GameMasterGetWinner();
    if(Winner == 0) {
        mvprintw(5 + (ViewBoardY * 2), 5 + (ViewBoardX * 2), "%c", '@');// Zeige das ausgewaehlte Element an
    } else {
        //Versuch einer Win/Lose Ausgabe:
        if(GameMasterGetWinnerKiLevel() == 0) { //bedeutet, dass der Spieler gewonnen hat
            mvprintw(2, 0, "WIN! Herzlichen Glueckwunsch! Verlassen mit 'q'");
        }
        if(GameMasterGetWinnerKiLevel() != 0) { //bedeutet, dass der Computer gewonnen hat
            mvprintw(2, 0, "LOSE! Schade, vielleicht klappt es beim naechsten Mal! Verlassen mit 'q'");
        }
        if(Winner == ' ') { //bedeutet, dass keiner gewonnen hat
            mvprintw(2, 0, "Unentschieden! vielleicht klappt es beim naechsten Mal! Verlassen mit 'q'");
        }
    }
}
