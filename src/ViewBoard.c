
#include "../include/ViewBoard.h"

#include "../include/Game.h"
#include "../include/ViewMenu.h"

#include <curses.h>

char ViewBoardAusgabe = ' ';
int ViewBoardX, ViewBoardY;
GameBoard ViewBoardGB;

void ViewBoardSetGameBoard(GameBoard gameBoard) { ViewBoardGB = gameBoard; }

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
        GameGet()->quit = 1;
        break;
    case KEY_BACKSPACE:
        GameGet()->pressedKeyCall = ViewMenuPressedKeyCall;
        GameGet()->paintCall = ViewMenuPaintCall;
        break;
    case KEY_ENTER:
    case ' ':
    case '\n':
        GameBoardSet(ViewBoardGB, ViewBoardY, ViewBoardX, 'X');
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

void ViewBoardPaintCall() {
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
    mvprintw(5 + (ViewBoardY * 2), 5 + (ViewBoardX * 2), "%c", '@');
}
