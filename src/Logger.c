#include "../include/Logger.h"

#ifdef DEBUG

    #include <stdio.h>
    #include <time.h>
    #include <ctype.h>

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

    void LoggerStart(char* mod, char* lvl) {
        time_t rawtime;
        struct tm *info;
        char buffer[20];

        time( &rawtime );
        info = localtime( &rawtime );
        strftime(buffer,20,"%Y%m%d %H:%M", info);

        if(LOGGER_FILE != NULL) {
            fprintf(LOGGER_FILE, "%s %s %s : ", buffer, mod, lvl);
        }
    }

    void LoggerString(char* msg) {
        if(LOGGER_FILE != NULL) {
            fprintf(LOGGER_FILE, "%s", msg);
        }
    }

    void LoggerChar(char c) {
        if(LOGGER_FILE != NULL) {
            if (isprint(c)) {
                fprintf(LOGGER_FILE, "'%c'", c);
            } else {
                fprintf(LOGGER_FILE, "'%d'", c);
            }
        }
    }

    void LoggerInt(int i) {
        if(LOGGER_FILE != NULL) {
            fprintf(LOGGER_FILE, "%d", i);
        }
    }

    void LoggerEnd() {
        if(LOGGER_FILE != NULL) {
            fprintf(LOGGER_FILE, "\n");
        }
    }

#endif
