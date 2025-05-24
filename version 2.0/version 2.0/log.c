#include <time.h>
#include <stdio.h>
#include "log.h"

const char *LogLevelToString(LOG_LEVEL level)
{
    switch (level)
    {
    case INFO:
        return "INFO";
    case WARNING:
        return "WARNING";
    case ERROR:
        return "ERROR";
    default:
        return "UNKNOWN";
    }
}

void Log(const char *message, LOG_LEVEL level)
{
    time_t now = time(NULL);
    struct tm *t = localtime(&now);

    const char *level_str = LogLevelToString(level);

    switch (level)
    {
    case INFO:
        printf("\033[32m[%04d-%02d-%02d %02d:%02d:%02d INFO] %s\033[0m\n",
               t->tm_year + 1900, t->tm_mon + 1, t->tm_mday,
               t->tm_hour, t->tm_min, t->tm_sec, message);
        break;
    case WARNING:
        printf("\033[33m[%04d-%02d-%02d %02d:%02d:%02d WARNING] %s\033[0m\n",
               t->tm_year + 1900, t->tm_mon + 1, t->tm_mday,
               t->tm_hour, t->tm_min, t->tm_sec, message);
        break;
    case ERROR:
        printf("\033[31m[%04d-%02d-%02d %02d:%02d:%02d ERROR] %s\033[0m\n",
               t->tm_year + 1900, t->tm_mon + 1, t->tm_mday,
               t->tm_hour, t->tm_min, t->tm_sec, message);
        break;
    default:
        printf("[%04d-%02d-%02d %02d:%02d:%02d] %s\n",
               t->tm_year + 1900, t->tm_mon + 1, t->tm_mday,
               t->tm_hour, t->tm_min, t->tm_sec, message);
        break;
    }

    FILE *file = fopen("logInfo.txt", "a");
    if (file == NULL)
    {
        Log("打开logInfo.txt失败", ERROR);
        return;
    }
    fprintf(file, "[%04d-%02d-%02d %02d:%02d:%02d %s] %s\n",
            t->tm_year + 1900, t->tm_mon + 1, t->tm_mday,
            t->tm_hour, t->tm_min, t->tm_sec, level_str, message);
    fclose(file);
}