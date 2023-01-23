#include "../include/Logger.h"

#ifdef DEBUG

    #include <stdio.h>
    #include <time.h>
    #include <ctype.h>

    FILE * LOGGER_FILE;
    
    void LoggerInit() {
        LOGGER_FILE = fopen(".tictactoe.log", "a");
        if(LOGGER_FILE == NULL) {
            printf("ERROR: Logger can not create logfile!!!\n"); // Versuche daraufhinzuweisen, dass das Logfile nicht erstellt werden konnte
        }
        LoggerLog("Logger", "ini", "TicTacToe start !"); // Informire im Logfile: Das Spiel wurde gestartet
    }
    
    void LoggerClose() {
        LoggerLog("Logger", "end", "TicTacToe end !"); // Informire im Logfile: Das Spiel wurde beendet
        fclose(LOGGER_FILE);
    }

    void LoggerLog(char* mod, char* lvl, char* msg) {
        time_t rawtime;
        struct tm *info;
        char buffer[20];

        time( &rawtime ); // ermittle die Zeit
        info = localtime( &rawtime );
        strftime(buffer,20,"%Y%m%d %H:%M", info); // benutze ein sinnvolles Zeitformat fuer das Logfile

        if(LOGGER_FILE != NULL) {
            fprintf(LOGGER_FILE, "%s %s %s : %s\n", buffer, mod, lvl, msg); // erstelle den Logeintrag
        }
    }

    void LoggerStart(char* mod, char* lvl) {
        time_t rawtime;
        struct tm *info;
        char buffer[20];

        time( &rawtime ); // ermittle die Zeit
        info = localtime( &rawtime );
        strftime(buffer,20,"%Y%m%d %H:%M", info); // benutze ein sinnvolles Zeitformat fuer das Logfile

        if(LOGGER_FILE != NULL) {
            fprintf(LOGGER_FILE, "%s %s %s : ", buffer, mod, lvl); // erstelle den Anfang eines Logeintrags
        }
    }

    void LoggerString(char* msg) {
        if(LOGGER_FILE != NULL) {
            fprintf(LOGGER_FILE, "%s", msg); // Fuege dem Logeintrag eine Zeichenkette hinzu
        }
    }

    void LoggerChar(char c) {
        if(LOGGER_FILE != NULL) {
            if (isprint(c)) { // Ist das Zeichen druckbar?
                fprintf(LOGGER_FILE, "'%c'", c); // Fuege dem Logeintrag ein Zeichen hinzu
            }
            else {
                fprintf(LOGGER_FILE, "'%d'", c); // Fuege dem Logeintrag das Zeichen als Zahl hinzu (weil nicht druckbar)
            }
        }
    }

    void LoggerInt(int i) {
        if(LOGGER_FILE != NULL) {
            fprintf(LOGGER_FILE, "%d", i); // Fuege dem Logeintrag eine Ganzzahl hinzu
        }
    }

    void LoggerEnd() {
        if(LOGGER_FILE != NULL) {
            fprintf(LOGGER_FILE, "\n"); // Schliesse den Logeintrag
        }
    }

#endif
