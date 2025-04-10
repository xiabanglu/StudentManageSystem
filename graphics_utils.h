#ifndef GRAPHICS_UTILS_H
#define GRAPHICS_UTILS_H

#include <graphics.h>

//窗口宽度和高度
#define WIN_WIDTH 800
#define WIN_HEIGHT 600

//表格参数
#define TABLE_ROWS 10
#define TABLE_COLS 8
#define CELL_WIDTH 100
#define CELL_HEIGHT 40
#define TABLE_WIDTH (CELL_WIDTH * TABLE_COLS)
#define TABLE_HEIGHT (CELL_HEIGHT * (TABLE_ROWS + 1))

//最大字符长度
#define MAX_STRING_LENGTH 7

//背景图
extern IMAGE img;

//函数声明
void LoadBgk();
void SetHeightText(int height);
void DrawButton(int x, int y, int width, int height, const wchar_t* text, int fontsize);
void DrawTable(int x, int y, int width, int height, int rows, int cols);
bool IsMouseInRect(int x, int y, int width, int height);

#endif // GRAPHICS_UTILS_H
