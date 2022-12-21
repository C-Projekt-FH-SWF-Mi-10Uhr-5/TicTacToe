output: main.o Game.o GameBoard.o ViewBoard.o ViewMenu.o
	gcc main.o Game.o GameBoard.o ViewBoard.o ViewMenu.o -lncurses -o TicTacToe

main.o: #main.c
	gcc -c src/main.c 

Game.o: #Game.c
	gcc -c src/Game.c 

GameBoard.o: #GameBoard.c
	gcc -c src/GameBoard.c

ViewBoard.o: #ViewBoard.c
	gcc -c src/ViewBoard.c 

ViewMenu.o: #ViewMenu.c
	gcc -c src/ViewMenu.c

clean:
	del TicTacToe.exe
	del *.o
#	rm TicTacToe.exe
#	rm *.o