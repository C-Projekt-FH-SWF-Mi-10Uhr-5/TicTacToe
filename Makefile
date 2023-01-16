output: main.o Game.o GameAI.o GameBoard.o GameMaster.o Logger.o Player.o ViewBoard.o ViewHighscore.o ViewMenu.o ViewMultiplayer.o ViewSettings.o
	gcc main.o Game.o GameAI.o GameBoard.o GameMaster.o Logger.o Player.o ViewBoard.o ViewHighscore.o ViewMenu.o ViewMultiplayer.o ViewSettings.o -lncurses -o TicTacToe

main.o: #main.c
	gcc $(USER_DEFINES) -c src/main.c 

Game.o: #Game.c
	gcc $(USER_DEFINES) -c src/Game.c 

GameAI.o: #GameAI.c
	gcc $(USER_DEFINES) -c src/GameAI.c

GameBoard.o: #GameBoard.c
	gcc $(USER_DEFINES) -c src/GameBoard.c

GameMaster.o: #GameMaster.c
	gcc $(USER_DEFINES) -c src/GameMaster.c

Logger.o: #Logger.c
	gcc $(USER_DEFINES) -c src/Logger.c

Player.o: #Player.c
	gcc $(USER_DEFINES) -c src/Player.c

ViewBoard.o: #ViewBoard.c
	gcc $(USER_DEFINES) -c src/ViewBoard.c 

ViewHighscore.o: #ViewHighscore.c
	gcc $(USER_DEFINES) -c src/ViewHighscore.c

ViewMenu.o: #ViewMenu.c
	gcc $(USER_DEFINES) -c src/ViewMenu.c

ViewSettings.o: #ViewSetting.c
	gcc $(USER_DEFINES) -c src/ViewSettings.c

ViewMultiplayer.o: #ViewMultiplayer.c
	gcc $(USER_DEFINES) -c src/ViewMultiplayer.c

clean:
	del *.o
	del TicTacToe.exe
#	rm *.o
#	rm TicTacToe.exe
