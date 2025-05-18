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
    const MenuItem *items;
} Menu;

static const MenuItem login_items[] = {
    {"l - login     (登录)", 'l', handle_login},
    {"r - register  (注册)", 'r', handle_register},
    {"q - quit      (退出)", 'q', handle_quit},
    {NULL, '\0', NULL}
};

static const MenuItem show_items[] = {
    {"i - insert record        (增)", 'i', handle_insert_record},
    {"d - delete record        (删)", 'd', handle_delete_record},
    {"u - update record        (改)", 'u', handle_update_record},
    {"f - find single record   (查单个)", 'f', handle_find_record},
    {"a - show all records     (查所有)", 'a', handle_show_records},
    {"q - quit                 (退出)", 'q', handle_quit},
    {NULL, '\0', NULL}
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
        printf("\033[1;32m---------------------------------\033[0m\n");
        printf("menu: %s\n", greet);

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

    return '0';
}

// 事件循环
void event_loop(Menu *menu, int *is_quit)
{
    char selected;
    const MenuItem *item;

    do
    {
        selected = getchoice(menu->title, menu->items);

        printf("\033[1;32m---------------------------------\033[0m\n");

        for (item = menu->items; item->description != NULL; item++)
        {
            if (selected == item->choice)
            {
                if (item->handler) item->handler();
                if (selected == 'q')
                {    *is_quit = 1;  }
                break;
            }
        }

        printf("\033[1;32m---------------------------------\033[0m\n");
    } while (selected != 'q');

}

#endif // MENU_H