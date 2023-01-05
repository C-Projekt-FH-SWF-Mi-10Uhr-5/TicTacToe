output: main.o Game.o GameAI.o GameBoard.o GameMaster.o Player.o ViewBoard.o ViewMenu.o
	gcc main.o Game.o GameAI.o GameBoard.o GameMaster.o Player.o ViewBoard.o ViewMenu.o -lncurses -o TicTacToe

main.o: #main.c
	gcc -c src/main.c 

Game.o: #Game.c
	gcc -c src/Game.c 

GameAI.o: #GameAI.c
	gcc -c src/GameAI.c

GameBoard.o: #GameBoard.c
	gcc -c src/GameBoard.c

GameMaster.o: #GameMaster.c
	gcc -c src/GameMaster.c

Player.o: #Player.c
	gcc -c src/Player.c

ViewBoard.o: #ViewBoard.c
	gcc -c src/ViewBoard.c 

ViewMenu.o: #ViewMenu.c
	gcc -c src/ViewMenu.c

clean:
	del *.o
	del TicTacToe.exe
#	rm *.o
#	rm TicTacToe.exe
