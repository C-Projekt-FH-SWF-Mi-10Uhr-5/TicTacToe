output: main.o Game.o GameBoard.o ViewBoard.o ViewMenu.o
	gcc main.o Game.o GameBoard.o ViewBoard.o ViewMenu.o -lncurses -o output

main.o: #main.c
	gcc -c main.c 

Game.o: #Game.c
	gcc -c Game.c 

GameBoard.o: #GameBoard.c
	gcc -c GameBoard.c

ViewBoard.o: #ViewBoard.c
	gcc -c ViewBoard.c 

ViewMenu.o: #ViewMenu.c
	gcc -c ViewMenu.c

clean:
	del output.exe
	del *.o