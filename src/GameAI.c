#include "../include/GameBoard.h"
#include "../include/Game.h"
#include <stdlib.h>
#include <time.h>
#include <curses.h>

int CheckEmptySpaces(GameBoard gb) { //Funktion zum Ueberpruefen von freien Feldern
    int emptySpaces=0;
    for(int i=0; i < gb.columns; i++) {
        for(int j=0; j < gb.rows; j++) {
            if(*GameBoardIndexOf(gb, i, j) == ' ') {
                emptySpaces++; //Gibt es freie Felder, so wird dieser Wert hochgezaehlt
            }
        }
    }
    return emptySpaces;
}

void ComputerPlacement(GameBoard gb, int difficulty) { //Sehr rustikale AI, die auf ein zufaelliges Feld ihr Symbol setzt
    if(difficulty == 1) {
        srand(time(NULL));
        int column=0;
        int row=0;
        if(CheckEmptySpaces(gb) > 1) { //Gilt nur, wenn es mehr als 1 freies Feld gibt (Spieler hat den letzten Zug)
            do {
                row=rand()%3;
                column=rand()%3;
            } while(*GameBoardIndexOf(gb, column, row) != ' '); //Ist das Feld bereits belegt, wird ein anderes zufaellig ausgewaehlt

            GameBoardSet(gb, column, row, 'O'); //Am Ende wird auf ein freies Feld das Symbol gesetzt
        }
        else {
            GameGet()->quit = 1; // Stoppe die Gameloop und beende das Spiel
        }
    }if(difficulty == 2){
    // Prüfe, ob der Computer in einer Reihe, Spalte oder Diagonale zwei 'O'-Zeichen hat und ein leeres Feld
    // Wenn ja, setze das 'O'-Zeichen auf das leere Feld, um den Sieg zu garantieren
        for(int i=0; i<gb.columns; i++) {
            if((*GameBoardIndexOf(gb, i, 0) == 'O') && (*GameBoardIndexOf(gb, i, 1) == 'O') && (*GameBoardIndexOf(gb, i, 2) == ' ')) {
            GameBoardSet(gb, i, 2, 'O');
            return;
            }
            else if((*GameBoardIndexOf(gb, i, 0) == 'O') && (*GameBoardIndexOf(gb, i, 1) == ' ') && (*GameBoardIndexOf(gb, i, 2) == 'O')) {
            GameBoardSet(gb, i, 1, 'O');
            return;
            }
            else if((*GameBoardIndexOf(gb, i, 0) == ' ') && (*GameBoardIndexOf(gb, i, 1) == 'O') && (*GameBoardIndexOf(gb, i, 2) == 'O')) {
            GameBoardSet(gb, i, 0, 'O');
            return;
            }
        }
        for(int i=0; i<gb.rows; i++) {
            if((*GameBoardIndexOf(gb, 0, i) == 'O') && (*GameBoardIndexOf(gb, 1, i) == 'O') && (*GameBoardIndexOf(gb, 2, i) == ' ')) {
            GameBoardSet(gb, 2, i, 'O');
            return;
            }
            else if((*GameBoardIndexOf(gb, 0, i) == 'O') && (*GameBoardIndexOf(gb, 1, i) == ' ') && (*GameBoardIndexOf(gb, 2, i) == 'O')) {
            GameBoardSet(gb, 1, i, 'O');
            return;
            }
            else if((*GameBoardIndexOf(gb, 0, i) == ' ') && (*GameBoardIndexOf(gb, 1, i) == 'O') && (*GameBoardIndexOf(gb, 2, i) == 'O')) {
            GameBoardSet(gb, 0, i, 'O');
            return;
            }
        }
            if((*GameBoardIndexOf(gb, 0, 0) == 'O') && (*GameBoardIndexOf(gb, 1, 1) == 'O') && (*GameBoardIndexOf(gb, 2, 2) == ' ')) {
            GameBoardSet(gb, 2, 2, 'O');
            return;
            }
            else if((*GameBoardIndexOf(gb, 0, 0) == 'O') && (*GameBoardIndexOf(gb, 1, 1) == ' ') && (*GameBoardIndexOf(gb, 2, 2) == 'O')) {
            GameBoardSet(gb, 1, 1, 'O');
            return;
            }
            else if((*GameBoardIndexOf(gb, 0, 0) == ' ') && (*GameBoardIndexOf(gb, 1, 1) == 'O') && (*GameBoardIndexOf(gb, 2, 2) == 'O')) {
            GameBoardSet(gb, 0, 0, 'O');
            return;
            }
            else if((*GameBoardIndexOf(gb, 0, 2) == 'O') && (*GameBoardIndexOf(gb, 1, 1) == 'O') && (*GameBoardIndexOf(gb, 2, 0) == ' ')) {
            GameBoardSet(gb, 2, 0, 'O');
            return;
            }
            else if((*GameBoardIndexOf(gb, 0, 2) == 'O') && (*GameBoardIndexOf(gb, 1, 1) == ' ') && (*GameBoardIndexOf(gb, 2, 0) == 'O')) {
            GameBoardSet(gb, 1, 1, 'O');
            return;
            }
            else if((*GameBoardIndexOf(gb, 0, 2) == ' ') && (*GameBoardIndexOf(gb, 1, 1) == 'O') && (*GameBoardIndexOf(gb, 2, 0) == 'O')) {
            GameBoardSet(gb, 0, 2, 'O');
            return;
            }
    // Prüfe, ob der Spieler in einer Reihe, Spalte oder Diagonale zwei 'X'-Zeichen hat und ein leeres Feld
    // Wenn ja, setze das 'O'-Zeichen auf das leere Feld, um den Gewinn des Spielers zu verhindern
        for(int i=0; i<gb.columns; i++) {
            if((*GameBoardIndexOf(gb, i, 0) == 'X') && (*GameBoardIndexOf(gb, i, 1) == 'X') && (*GameBoardIndexOf(gb, i, 2) == ' ')) {
            GameBoardSet(gb, i, 2, 'O');
            return;
            }
            else if((*GameBoardIndexOf(gb, i, 0) == 'X') && (*GameBoardIndexOf(gb, i, 1) == ' ') && (*GameBoardIndexOf(gb, i, 2) == 'X')) {
            GameBoardSet(gb, i, 1, 'O');
            return;
            }
            else if((*GameBoardIndexOf(gb, i, 0) == ' ') && (*GameBoardIndexOf(gb, i, 1) == 'X') && (*GameBoardIndexOf(gb, i, 2) == 'X')) {
            GameBoardSet(gb, i, 0, 'O');
            return;
            }
        }
        for(int i=0; i<gb.rows; i++) {
            if((*GameBoardIndexOf(gb, 0, i) == 'X') && (*GameBoardIndexOf(gb, 1, i) == 'X') && (*GameBoardIndexOf(gb, 2, i) == ' ')) {
            GameBoardSet(gb, 2, i, 'O');
            return;
            }
            else if((*GameBoardIndexOf(gb, 0, i) == 'X') && (*GameBoardIndexOf(gb,1, i) == ' ') && (*GameBoardIndexOf(gb, 2, i) == 'X')) {
            GameBoardSet(gb, 1, i, 'O');
            return;
            }
            else if((*GameBoardIndexOf(gb, 0, i) == ' ') && (*GameBoardIndexOf(gb, 1, i) == 'X') && (*GameBoardIndexOf(gb, 2, i) == 'X')) {
            GameBoardSet(gb, 0, i, 'O');
            return;
            }
        }
            if((*GameBoardIndexOf(gb, 0, 0) == 'X') && (*GameBoardIndexOf(gb, 1, 1) == 'X') && (*GameBoardIndexOf(gb, 2, 2) == ' ')) {
            GameBoardSet(gb, 2, 2, 'O');
            return;
            }
            else if((*GameBoardIndexOf(gb, 0, 0) == 'X') && (*GameBoardIndexOf(gb, 1, 1) == ' ') && (*GameBoardIndexOf(gb, 2, 2) == 'X')) {
            GameBoardSet(gb, 1, 1, 'O');
            return;
            }
            else if((*GameBoardIndexOf(gb, 0, 0) == ' ') && (*GameBoardIndexOf(gb, 1, 1) == 'X') && (*GameBoardIndexOf(gb, 2, 2) == 'X')) {
            GameBoardSet(gb, 0, 0, 'O');
            return;
            }
            else if((*GameBoardIndexOf(gb, 0, 2) == 'X') && (*GameBoardIndexOf(gb, 1, 1) == 'X') && (*GameBoardIndexOf(gb, 2, 0) == ' ')) {
            GameBoardSet(gb, 2, 0, 'O');
            return;
            }
            else if((*GameBoardIndexOf(gb, 0, 2) == 'X') && (*GameBoardIndexOf(gb, 1, 1) == ' ') && (*GameBoardIndexOf(gb, 2, 0) == 'X')) {
            GameBoardSet(gb, 1, 1, 'O');
            return;
            }
            else if((*GameBoardIndexOf(gb, 0, 2) == ' ') && (*GameBoardIndexOf(gb, 1, 1) == 'X') && (*GameBoardIndexOf(gb, 2, 0) == 'X')) {
            GameBoardSet(gb, 0, 2, 'O');
            return;
            }
    // Wenn kein Zug gefunden wurde, der den Sieg garantiert, mache einen Zufallszug
        srand(time(NULL));
        int column=0;
        int row=0;
        if(CheckEmptySpaces(gb) > 1) { //Gilt nur, wenn es mehr als 1 freies Feld gibt (Spieler hat den letzten Zug)
            do {
                row=rand()%3;
                column=rand()%3;
            } while(*GameBoardIndexOf(gb, column, row) != ' '); //Ist das Feld bereits belegt, wird ein anderes zufällig ausgewählt

            GameBoardSet(gb, column, row, 'O'); //Am Ende wird auf ein freies Feld das Symbol gesetzt
        }
        else {
            GameGet()->quit = 1; // Stoppe die Gameloop und beende das Spiel
        }
    }
}

void PlayerPlacement(GameBoard gb, int ViewBoardY, int ViewBoardX) { //Zur besseren Veranschaulichung des Spielerzuges
    GameBoardSet(gb , ViewBoardY, ViewBoardX, 'X'); //Setze ein X auf das entsprechende Feld
}


int CheckWinner(GameBoard gb, char c) { //Funktion die ueberprueft, ob es einen Sieger gibt, GESCHEITERT
    int winner=0;
    //Columns:
    for(int i=0; i<gb.columns; i++) {
        if((*GameBoardIndexOf(gb, i, 0) == c) && (*GameBoardIndexOf(gb, i, 1) == c) && (*GameBoardIndexOf(gb, i, 2) == c)) {
            return 1;
        }
    }
    //Rows:
    for(int i=0; i<gb.rows; i++) {
        if((*GameBoardIndexOf(gb, 0, i) == c) && (*GameBoardIndexOf(gb, 1, i) == c) && (*GameBoardIndexOf(gb, 2, i) == c)) {
            return 1;
        }
    }
    //Diagonale:
    if((*GameBoardIndexOf(gb, 0, 0) == c) && (*GameBoardIndexOf(gb, 1, 1) == c) && (*GameBoardIndexOf(gb, 2, 2) == c)) {
        return 1;
    }
    if((*GameBoardIndexOf(gb, 0, 2) == c) && (*GameBoardIndexOf(gb, 1, 1) == c) && (*GameBoardIndexOf(gb, 2, 0) == c)) {
        return 1;
    }
}