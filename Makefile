output: main.o Game.o GameAI.o GameBoard.o ViewBoard.o ViewMenu.o ViewMultiplayer.o ViewSettings.o
	gcc main.o Game.o GameAI.o GameBoard.o ViewBoard.o ViewMenu.o ViewMultiplayer.o ViewSettings.o -lncurses -o TicTacToe

main.o: #main.c
	gcc -c src/main.c 

Game.o: #Game.c
	gcc -c src/Game.c 

GameAI.o: #GameAI.c
	gcc -c src/GameAI.c

GameBoard.o: #GameBoard.c
	gcc -c src/GameBoard.c

ViewBoard.o: #ViewBoard.c
	gcc -c src/ViewBoard.c 

ViewMenu.o: #ViewMenu.c
	gcc -c src/ViewMenu.c

ViewSettings.o: #ViewSetting.c
	gcc -c src/ViewSettings.c

ViewMultiplayer.o: #ViewMultiplayer.c
	gcc -c src/ViewMultiplayer.c

clean:
	del TicTacToe.exe
	del *.o
#	rm TicTacToe.exe
#	rm *.o