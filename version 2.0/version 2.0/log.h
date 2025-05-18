#include <stdio.h>
#include <time.h>

typedef enum LOG_LEVEL
{
    INFO,
    WARING,
    ERROR
} LOG_LEVEL;

void Log(const char *message, LOG_LEVEL level)
{
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    
    switch (level) {
    case INFO:
        printf("\033[32m[%02d:%02d:%02d INFO] %s\033[0m\n", 
               t->tm_hour, t->tm_min, t->tm_sec, message);
        break;
    case WARING:
        printf("\033[33m[%02d:%02d:%02d WARNING] %s\033[0m\n",
               t->tm_hour, t->tm_min, t->tm_sec, message);
        break;
    case ERROR:
        printf("\033[31m[%02d:%02d:%02d ERROR] %s\033[0m\n",
               t->tm_hour, t->tm_min, t->tm_sec, message);
        break;
    default:
        printf("[%02d:%02d:%02d] %s\n",
               t->tm_hour, t->tm_min, t->tm_sec, message);
        break;
    }
}