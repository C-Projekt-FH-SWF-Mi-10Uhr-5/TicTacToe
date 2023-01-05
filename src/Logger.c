#include "../include/Logger.h"

#ifdef DEBUG

    #include <stdio.h>
    #include <time.h>

    FILE * LOGGER_FILE;
    
    void LoggerInit() {
        LOGGER_FILE = fopen(".tictactoe.log", "a");
        if(LOGGER_FILE == NULL) {
            printf("ERROR: Logger can not create logfile!!!\n");
        }
        LoggerLog("Logger", "ini", "TicTacToe start !");
    }
    
    void LoggerClose() {
        LoggerLog("Logger", "end", "TicTacToe end !");
        fclose(LOGGER_FILE);
    }

    void LoggerLog(char* mod, char* lvl, char* msg) {
        time_t rawtime;
        struct tm *info;
        char buffer[20];

        time( &rawtime );
        info = localtime( &rawtime );
        strftime(buffer,20,"%Y%m%d %H:%M", info);

        if(LOGGER_FILE != NULL) {
            fprintf(LOGGER_FILE, "%s %s %s : %s\n", buffer, mod, lvl, msg);
        }
    }

#endif
