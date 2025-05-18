#include <stdio.h>

typedef enum LOG_LEVEL
{
    INFO,
    WARING,
    ERROR
} LOG_LEVEL;

void Log(const char *message, LOG_LEVEL level)
{
    switch (level)
    {
    case INFO:
        printf("\033[32m[INFO] %s\033[0m\n", message); // 绿色
        break;
    case WARING:
        printf("\033[33m[WARNING] %s\033[0m\n", message); // 黄色
        break;
    case ERROR:
        printf("\033[31m[ERROR] %s\033[0m\n", message); // 红色
        break;
    default:
        printf("%s\n", message);
        break;
    }
}