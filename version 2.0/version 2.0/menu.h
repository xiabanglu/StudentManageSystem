#ifndef MENU_H
#define MENU_H

#include "event.h"

typedef struct MenuItem
{
    const char *description;
    char choice;
    void (*handler)(void);
} MenuItem;

// 菜单类型枚举
typedef enum MenuType
{
    MENU_LOGIN,
    MENU_SHOW,
} MenuType;

// 菜单结构体
typedef struct Menu
{
    const char *title;
    MenuType type;
    const MenuItem *items; // 指向菜单项数组
} Menu;

// 登录菜单项
static const MenuItem login_items[] = {
    {"l - student login", 'l', handle_login},
    {"r - register", 'r', handle_register},
    {"k - delete user", 'k', handle_delete_user},
    {NULL, '\0', NULL} // 结束标记
};

// 主菜单项
static const MenuItem show_items[] = {
    {"i - insert new record", 'i', handle_insert_record},
    {"d - delete record", 'd', handle_delete_record},
    {"u - update record", 'u', handle_update_record},
    {"f - find record", 'f', handle_find_record},
    {"q - quit", 'q', handle_quit},
    {"a - show all records", 'a', handle_show_records},
    {NULL, '\0', NULL} // 结束标记
};

// 创建菜单
Menu *create_menu(MenuType type)
{
    Menu *menu = (Menu *)malloc(sizeof(Menu));
    menu->type = type;

    if (type == MENU_LOGIN)
    {
        menu->title = "Login Menu";
        menu->items = login_items;
    }
    else
    {
        menu->title = "Show Menu";
        menu->items = show_items;
    }

    return menu;
}

// 获取用户选择
char getchoice(const char *greet, const MenuItem *items)
{
    char selected;
    const MenuItem *item;

    do
    {
        printf("\033[1;32m-------------------------\033[0m\n");
        printf("Menu: %s\n", greet);

        // 打印菜单项
        for (item = items; item->description != NULL; item++)
        {
            printf("%s\n", item->description);
        }

        // 获取输入
        selected = getchar();
        while (selected == '\n')
            selected = getchar();
        while (getchar() != '\n')
            ; // 清空输入缓冲区

        // 检查选择是否有效
        for (item = items; item->description != NULL; item++)
        {
            if (selected == item->choice)
            {
                return selected;
            }
        }

        printf("Incorrect choice, select again\n");
    } while (1);
}

// 事件循环
void event_loop(Menu *menu, int *is_quit)
{
    char selected;
    const MenuItem *item;

    do
    {
        selected = getchoice(menu->title, menu->items);
        printf("\033[1;32m-------------------------\033[0m\n");

        for (item = menu->items; item->description != NULL; item++)
        {
            if (selected == item->choice)
            {
                item->handler();
                if (selected == 'l' && rank)
                {
                    *is_quit = 1;
                    selected = 'q';
                }
                if (selected == 'q')
                    *is_quit = 1;
                break;
            }
        }

        printf("\033[1;32m-------------------------\033[0m\n");
    } while (selected != 'q');
}

#endif // MENU_H