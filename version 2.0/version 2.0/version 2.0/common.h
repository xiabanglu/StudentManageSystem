#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// 全局变量声明
extern struct School *school;
extern int rank;

// 日志级别枚举
typedef enum LOG_LEVEL {
    INFO,
    WARING,
    ERROR
} LOG_LEVEL;

// 公共函数声明
void Log(const char *message, LOG_LEVEL level);

#endif