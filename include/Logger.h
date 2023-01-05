/**
 * @file Logger.h
 * @author Fabian Grubba (grubba.fabiandavidjonah@fh-swf.de)
 * @brief 
 * @version 0.1
 * @date 2023-01-05
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef LOGGER_H
#define LOGGER_H

    #ifdef DEBUG

        #include <stdio.h>
        #include <time.h>

        void LoggerInit();
        void LoggerClose();
        void LoggerLog(char* mod, char* lvl, char* msg);

        void LoggerStart(char* mod, char* lvl);
        void LoggerString(char* msg);
        void LoggerChar(char c);
        void LoggerInt(int i);
        void LoggerEnd();

        #define LOGGER_INIT LoggerInit();
        #define LOGGER_CLOSE LoggerClose();

        #define LOGGER_LOG(f, m) LoggerLog(f, "log", m);
        #define LOGGER_ERR(f, m) LoggerLog(f, "err", m);

        
        #define LOGGER_START(f, m) LoggerStart(f, m);
        #define LOGGER_STR(c) LoggerString(c);
        #define LOGGER_CHAR(c) LoggerChar(c);
        #define LOGGER_INT(i) LoggerInt(i);
        #define LOGGER_END() LoggerEnd();

    #else

        #define LOGGER_INIT
        #define LOGGER_CLOSE

        #define LOGGER_LOG(f, m)
        #define LOGGER_ERR(f, m)

        #define LOGGER_START(f, m)
        #define LOGGER_STR(c)
        #define LOGGER_CHAR(c)
        #define LOGGER_INT(i)
        #define LOGGER_END()

    #endif

#endif

