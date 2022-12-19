
#include "../include/Game.h"
#include "../include/GameBoard.h"
#include "../include/ViewMenu.h"

int main(int argc, char *argv[]) {

    GameBoard gb = GameBoardCreate(3, 3);

    // GameBoardClear(gb);

    GameBoardSet(gb, 0, 0, '1');
    GameBoardSet(gb, 1, 0, '2');
    GameBoardSet(gb, 2, 0, '3');

    GameBoardSet(gb, 0, 1, '4');
    GameBoardSet(gb, 1, 1, '5');
    GameBoardSet(gb, 2, 1, '6');

    GameBoardSet(gb, 0, 2, '7');
    GameBoardSet(gb, 1, 2, '8');
    GameBoardSet(gb, 2, 2, '9');

    /*GameBoardSet(gb, 0, 3, 'A');
    GameBoardSet(gb, 1, 3, 'B');
    GameBoardSet(gb, 2, 3, 'C');*/

    //GameBoardPrint(gb);

    /*printf("\n");

    for (int i = 0; i < (gb.columns * gb.rows); i++) {
        printf(" %c ", *(gb.board + (i)));
    }*/

    GameBoardDestroy(&gb);

    GameInit(ViewMenuPressedKeyCall, ViewMenuPaintCall);
    GameStart();
    GameStop();

    return 0;
}
