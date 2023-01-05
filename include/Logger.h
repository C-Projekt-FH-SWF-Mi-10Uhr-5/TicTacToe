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

        #define LOGGER_INIT LoggerInit();
        #define LOGGER_CLOSE LoggerClose();

        #define LOGGER_LOG(f, m) LoggerLog(f, "log", m);
        #define LOGGER_ERR(f, m) LoggerLog(f, "err", m);

    #else

        #define LOGGER_INIT
        #define LOGGER_CLOSE

        #define LOGGER_LOG(f, m)
        #define LOGGER_ERR(f, m)

    #endif

#endif

