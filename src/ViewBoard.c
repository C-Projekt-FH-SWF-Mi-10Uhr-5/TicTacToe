
#include "../include/ViewBoard.h"

#include "../include/Game.h"
#include "../include/ViewMenu.h"

#include "../include/GameAI.h"

#include <curses.h>

char ViewBoardAusgabe = ' ';// Welche Cursortaste wurde gedrueckt (TODO: Spaeter etfernen)
int ViewBoardX, ViewBoardY;// Aktuell ausgewaeltes Feld im Spielbrett
GameBoard ViewBoardGB;// Das darzustellende Spielbrett
int CheckPlacedSlot=0; //Wert, der angibt ob ein Feld bereits besetzt ist (=1) oder noch frei ist (=0)
char Winner=0; //Gewinner Variable

void ViewBoardSetGameBoard(GameBoard gameBoard) {
    ViewBoardGB = gameBoard; // Setze das Spielbrett in die Darstellung
    Winner=0; //Zuruecksetzen des Gewinners, falls man bereits eine Runde vorher gespielt hat
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
        if(Winner != 0) {
            return;
        }
        CheckPlacedSlot=0; //Ruecksetzen des Fehlerwertes
        if(*GameBoardIndexOf(ViewBoardGB, ViewBoardY, ViewBoardX) == ' ') { //Ueberpruefe, ob das Feld frei ist
            PlayerPlacement(ViewBoardGB, ViewBoardY, ViewBoardX); //Setze ein X auf das entsprechende Feld
            ComputerPlacement(ViewBoardGB, 2); //Der Computer setzt ein O auf ein leeres Feld
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
    if(Winner == 0) {
        mvprintw(5 + (ViewBoardY * 2), 5 + (ViewBoardX * 2), "%c", '@');// Zeige das ausgewaehlte Element an
        //Ueberpruefung, ob es einen Gewinner gibt
        if(CheckWinner(ViewBoardGB, 'X') == 1) {
            Winner='X';
        }
        else if(CheckWinner(ViewBoardGB, 'O') == 1) {
            Winner='O';
        }
    }
    if(CheckPlacedSlot == 1) { //Gebe eine Fehlermeldung aus, wenn das ausgewaehlte Feld bereits besetzt ist
        mvprintw(1, 0, "Fehlerhafte Eingabe, versuche erneut");
    }
    //Versuch einer Win/Lose Ausgabe:
    if(Winner == 'X') { //bedeutet, dass der Spieler gewonnen hat
        mvprintw(2, 0, "WIN! Herzlichen Glueckwunsch! Verlassen mit 'q'");
    }
    if(Winner == 'O') { //bedeutet, dass der Computer gewonnen hat
        mvprintw(2, 0, "LOSE! Schade, vielleicht klappt es beim naechsten Mal! Verlassen mit 'q'");
    }
}
