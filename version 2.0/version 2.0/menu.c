#include "menu.h"
#include "event.h"

// 暂定权限等级为 rank     1:普通用户    2：管理员    3：开发人员
static const MenuItem login_items[] = {
    {COLOR_YELLOW "l - login     (登录)" COLOR_RESET, 'l', handle_login},
    {COLOR_YELLOW "r - register  (注册)" COLOR_RESET, 'r', handle_register_user}, // 只能注册普通用户 (权限rank：1)
    {COLOR_YELLOW "q - quit      (退出)" COLOR_RESET, 'q', handle_quit},
    {NULL, '\0', NULL}};

static const MenuItem function_items[] = {
    {COLOR_YELLOW "i - insert student        (增)" COLOR_RESET, 'i', handle_insert_record},    // 所需权限rank: 2,3
    {COLOR_YELLOW "d - delete student        (删)" COLOR_RESET, 'd', handle_delete_record},    // 所需权限rank: 2,3
    {COLOR_YELLOW "u - update student        (改)" COLOR_RESET, 'u', handle_update_record},    // 所需权限rank: 2,3
    {COLOR_YELLOW "s - show single student   (查单个)" COLOR_RESET, 's', handle_show_record},  // 所需权限rank: 1,2,3
    {COLOR_YELLOW "b - show all student      (查所有)" COLOR_RESET, 'b', handle_show_records}, // 所需权限rank: 2,3
    //{COLOR_YELLOW"c - score statistics      (成绩统计)"COLOR_RESET, 'c', handle_score_statistics},    //所需权限rank: 2,3    接入scoreCounter.h
    {COLOR_YELLOW "r - register admin        (注册管理员)" COLOR_RESET, 'r', handle_register_admin},    // 所需权限rank: 3
    {COLOR_YELLOW "e - delete user account   (注销普通用户账号)" COLOR_RESET, 'e', handle_delete_user}, // 所需权限rank: 2,3
    {COLOR_YELLOW "a - delete admin account  (注销管理员账号)" COLOR_RESET, 'a', handle_delete_admin},  // 所需权限rank: 3
    {COLOR_YELLOW "q - quit                  (退出)" COLOR_RESET, 'q', handle_quit},
    {NULL, '\0', NULL}};

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
        printf(HEADER_LINE "\n");
        printf(COLOR_YELLOW "menu (菜单): %s\n" COLOR_RESET, greet);

        // 打印菜单项
        for (item = items; item->description != NULL; item++)
        {
            printf(COLOR_YELLOW "%s\n" COLOR_RESET, item->description);
        }

        printf(HEADER_LINE "\n");

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

        Log("no this choice(没有这个选项)", WARING);
    } while (1);

    return '0';
}

// 事件循环
void event_loop(Menu *menu, int *is_quit, MenuType type)
{
    char selected;
    const MenuItem *item;

    do
    {
        selected = getchoice(menu->title, menu->items);
        printf(HEADER_LINE "\n");

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
                // 处理退出逻辑
                if (selected == 'q')
                {
                    if (type == MENU_LOGIN)
                    {
                        *is_quit = 2; // 登录界面退出程序
                    }
                    else if (type == MENU_FUNCTION)
                    {
                        Log("返回登录界面...", INFO);
                        *is_quit = 1; // 功能界面返回登录
                    }
                }
                break;
            }
        }
    } while (!*is_quit);
}