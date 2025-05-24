#include <time.h>
#include <stdio.h>
#include <string.h>
#include "log.h"

char current_username[32] = "unknown";

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

void set_username(const char *username)
{
    strncpy(current_username, username, sizeof(current_username) - 1);
    current_username[sizeof(current_username) - 1] = '\0';
}

void clear_username()
{
    strcpy(current_username, "unknown");
}

void Log(const char *message, LOG_LEVEL level)
{
    time_t now = time(NULL);
    struct tm *t = localtime(&now);

    const char *level_str = LogLevelToString(level);

    switch (level)
    {
    case INFO:
        printf("\033[32m[%04d-%02d-%02d %02d:%02d:%02d %s][%s] %s\033[0m\n",
               t->tm_year + 1900, t->tm_mon + 1, t->tm_mday,
               t->tm_hour, t->tm_min, t->tm_sec, level_str, current_username, message);
        break;
    case WARNING:
        printf("\033[33m[%04d-%02d-%02d %02d:%02d:%02d %s][%s] %s\033[0m\n",
               t->tm_year + 1900, t->tm_mon + 1, t->tm_mday,
               t->tm_hour, t->tm_min, t->tm_sec, level_str, current_username, message);
        break;
    case ERROR:
        printf("\033[31m[%04d-%02d-%02d %02d:%02d:%02d %s][%s] %s\033[0m\n",
               t->tm_year + 1900, t->tm_mon + 1, t->tm_mday,
               t->tm_hour, t->tm_min, t->tm_sec, level_str, current_username, message);
        break;
    default:
        printf("[%04d-%02d-%02d %02d:%02d:%02d][%s] %s\n",
               t->tm_year + 1900, t->tm_mon + 1, t->tm_mday,
               t->tm_hour, t->tm_min, t->tm_sec, current_username, message);
        break;
    }

    FILE *file = fopen("logInfo.txt", "a");
    if (file == NULL)
    {
        // 避免递归调用
        fprintf(stderr, "打开logInfo.txt失败\n");
        return;
    }
    fprintf(file, "[%04d-%02d-%02d %02d:%02d:%02d %s][%s] %s\n",
            t->tm_year + 1900, t->tm_mon + 1, t->tm_mday,
            t->tm_hour, t->tm_min, t->tm_sec, level_str, current_username, message);
    fclose(file);
}