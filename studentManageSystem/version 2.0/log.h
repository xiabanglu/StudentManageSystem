#ifndef LOG_H
#define LOG_H

#include "common.h"

extern char current_username[32];

// 日志级别枚举
typedef enum LOG_LEVEL
{
    INFO,
    WARNING,
    ERROR
} LOG_LEVEL;

// 函数声明
void Log(const char *message, LOG_LEVEL level);
const char *LogLevelToString(LOG_LEVEL level);
void set_username(const char *username);
void clear_username();

#endif