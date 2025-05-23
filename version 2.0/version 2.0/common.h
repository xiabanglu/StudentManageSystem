#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// 全局变量声明
extern struct School *school;
extern int rank;

// 颜色代码宏定义
#define COLOR_RESET "\033[0m"
#define COLOR_RED "\033[31m"
#define COLOR_GREEN "\033[32m"
#define COLOR_YELLOW "\033[33m"
#define COLOR_BLUE "\033[34m"
#define COLOR_CYAN "\033[36m"
#define COLOR_PINK "\033[35m"
#define COLOR_WHITE "\033[1;37m"

// 样式宏
#define BOLD_ON "\033[1m"
#define BOLD_OFF "\033[22m"
#define BLINK "\033[5m"

// 界面元素模板
#define HEADER_LINE COLOR_CYAN "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" COLOR_RESET
#define INPUT_PROMPT COLOR_YELLOW "➤ " COLOR_RESET

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

#endif