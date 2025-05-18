#include "event.h"

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

// 暂定权限等级为 rank     1:普通用户    2：管理员    3：开发人员
static const MenuItem login_items[] = {
    {"l - login     (登录)", 'l', handle_login},
    {"r - register  (注册)", 'r', handle_register_user}, // 只能注册普通用户 (权限rank：1)
    {"q - quit      (退出)", 'q', handle_quit},
    {NULL, '\0', NULL}};

static const MenuItem function_items[] = {
    {"i - insert student        (增)", 'i', handle_insert_record},               // 所需权限rank: 2,3
    {"d - delete student        (删)", 'd', handle_delete_record},               // 所需权限rank: 2,3
    {"u - update student        (改)", 'u', handle_update_record},               // 所需权限rank: 2,3
    {"s - show single student   (查单个)", 's', handle_show_record},             // 所需权限rank: 1,2,3
    {"b - show all student      (查所有)", 'b', handle_show_records},            // 所需权限rank: 2,3
    //{"c - score statistics      (成绩统计)", 'c', handle_score_statistics},    //所需权限rank: 2,3    接入scoreCounter.h
    {"r - register admin        (注册管理员)", 'r', handle_register_admin},      //所需权限rank: 3
    {"e - delete user account   (注销普通用户账号)", 'e', handle_delete_user},    // 所需权限rank: 2,3
    {"a - delete admin account  (注销管理员账号)", 'a', handle_delete_admin},     //所需权限rank: 3
    {"q - quit                  (退出)", 'q', handle_quit},
    {NULL, '\0', NULL}};

// 函数声明
Menu *create_menu(MenuType type);
char getchoice(const char *greet, const MenuItem *items);
void event_loop(Menu *menu, int *is_quit);

// 创建菜单
Menu *create_menu(MenuType type)
{
    Menu *menu = (Menu *)malloc(sizeof(Menu));

    menu->type = type;

    if (type == MENU_LOGIN)
    {
        menu->title = "Login Menu (登录菜单)";
        menu->items = login_items;
    }
    else
    {
        menu->title = "Function Menu (功能菜单)";
        menu->items = function_items;
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
        printf("menu (菜单): %s\n", greet);

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
                if (item->handler)
                    item->handler();
                if (selected == 'q')
                {
                    *is_quit = 1;
                }
                break;
            }
        }

    } while (selected != 'q');
}