/**
 * @file Logger.h
 * @brief 
 * @version 0.1
 * @date 2023-01-05
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef LOGGER_H
#define LOGGER_H

    #ifdef DEBUG // Fuegt den Logger hinzu

        #include <stdio.h>
        #include <time.h>

        /**
         * @brief Richtet den Logger ein und oeffnet das Logfile
         */
        void LoggerInit();

        /**
         * @brief Schliesst das Logfile
         */
        void LoggerClose();

        /**
         * @brief Erstellt einen Log-Eintrag
         * @param mod Das Modul z.B. Dateiname
         * @param lvl Die Wichtigkeit des eintrages z.B. err, log oder inf
         * @param msg Die Nachricht
         */
        void LoggerLog(char* mod, char* lvl, char* msg);



        /**
         * @brief Beginnt einen Log-Eintrag
         * @param mod Das Modul z.B. Dateiname
         * @param lvl Die Wichtigkeit des eintrages z.B. err, log oder inf
         */
        void LoggerStart(char* mod, char* lvl);

        /**
         * @brief Erweitert den Log-Eintrag um eine Zeichenkette
         * @param msg Die Nachricht
         */
        void LoggerString(char* msg);

        /**
         * @brief Erweitert den Log-Eintrag um ein Zeichen
         * @param c Das Zeichen
         */
        void LoggerChar(char c);

        /**
         * @brief Erweitert den Log-Eintrag um eine Ganzzahl
         * @param i Die Ganzzahl
         */
        void LoggerInt(int i);

        /**
         * @brief Beendet den Log-Eintrag
         */
        void LoggerEnd();


        /**
         * @brief Richtet den Logger ein und oeffnet das Logfile
         */
        #define LOGGER_INIT LoggerInit();
        /**
         * @brief Schliesst das Logfile
         */
        #define LOGGER_CLOSE LoggerClose();

        /**
         * @brief Erstellt einen Log-Eintrag
         * @param f Das Modul z.B. Dateiname
         * @param m Die Nachricht
         */
        #define LOGGER_LOG(f, m) LoggerLog(f, "log", m);
        /**
         * @brief Erstellt einen Log-Eintrag fuer einen Fehler
         * @param f Das Modul z.B. Dateiname
         * @param m Die Nachricht
         */
        #define LOGGER_ERR(f, m) LoggerLog(f, "err", m);

        /**
         * @brief Beginnt einen Log-Eintrag
         * @param f Das Modul z.B. Dateiname
         * @param m Die Wichtigkeit des eintrages z.B. err, log oder inf
         */
        #define LOGGER_START(f, m) LoggerStart(f, m);
        /**
         * @brief Erweitert den Log-Eintrag um eine Zeichenkette
         * @param c Die Nachricht
         */
        #define LOGGER_STR(c) LoggerString(c);
        /**
         * @brief Erweitert den Log-Eintrag um ein Zeichen
         * @param c Das Zeichen
         */
        #define LOGGER_CHAR(c) LoggerChar(c);
        /**
         * @brief Erweitert den Log-Eintrag um eine Ganzzahl
         * @param i Die Ganzzahl
         */
        #define LOGGER_INT(i) LoggerInt(i);
        /**
         * @brief Beendet den Log-Eintrag
         */
        #define LOGGER_END() LoggerEnd();

    #else // Ansonsten wird der Logger entfernt
          // Es werden Platzhalter eingefuegt

        /**
         * @brief Richtet den Logger ein und oeffnet das Logfile
         */
        #define LOGGER_INIT
        /**
         * @brief Schliesst das Logfile
         */
        #define LOGGER_CLOSE

        /**
         * @brief Erstellt einen Log-Eintrag
         * @param f Das Modul z.B. Dateiname
         * @param m Die Nachricht
         */
        #define LOGGER_LOG(f, m)
        /**
         * @brief Erstellt einen Log-Eintrag fuer einen Fehler
         * @param f Das Modul z.B. Dateiname
         * @param m Die Nachricht
         */
        #define LOGGER_ERR(f, m)

        /**
         * @brief Beginnt einen Log-Eintrag
         * @param f Das Modul z.B. Dateiname
         * @param m Die Wichtigkeit des eintrages z.B. err, log oder inf
         */
        #define LOGGER_START(f, m)
        /**
         * @brief Erweitert den Log-Eintrag um eine Zeichenkette
         * @param c Die Nachricht
         */
        #define LOGGER_STR(c)
        /**
         * @brief Erweitert den Log-Eintrag um ein Zeichen
         * @param c Das Zeichen
         */
        #define LOGGER_CHAR(c)
        /**
         * @brief Erweitert den Log-Eintrag um eine Ganzzahl
         * @param i Die Ganzzahl
         */
        #define LOGGER_INT(i)
        /**
         * @brief Beendet den Log-Eintrag
         */
        #define LOGGER_END()

    #endif

#endif

