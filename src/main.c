
#include "../include/Game.h"
#include "../include/ViewMenu.h"

int main(int argc, char *argv[]) {

    GameInit(ViewMenuPressedKeyCall, ViewMenuPaintCall);
    GameStart();
    GameStop();

    return 0;
}
