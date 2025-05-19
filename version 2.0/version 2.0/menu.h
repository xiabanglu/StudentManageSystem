#ifndef MENU_H
#define MENU_H

#include "common.h"

// 菜单选项
typedef struct MenuItem
{
    const char *description; // 菜单描述
    char choice;             // 选择开关
    void (*handler)(void);   // 回调函数
} MenuItem;

// 菜单类型枚举
typedef enum MenuType
{
    MENU_LOGIN,    // 登录
    MENU_FUNCTION, // 功能
} MenuType;

// 菜单结构体
typedef struct Menu
{
    const char *title;     // 菜单名
    MenuType type;         // 菜单类型
    const MenuItem *items; // 菜单选项
} Menu;

// 函数声明
Menu *create_menu(MenuType type);
char getchoice(const char *greet, const MenuItem *items);
void event_loop(Menu *menu, int *is_quit, MenuType type);

#endif