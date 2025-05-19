#include "menu.h"
#include "event.h"

// 颜色定义
#define COLOR_RESET "\033[0m"
#define COLOR_CYAN "\033[1;36m"
#define COLOR_YELLOW "\033[1;33m"
#define COLOR_GREEN "\033[1;32m"
#define COLOR_RED "\033[1;31m"
#define COLOR_WHITE "\033[1;37m"

// 显示登陆菜单
void display_menu_login()
{
    printf("\033[1;36m┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\033[0m\n");
    printf("\033[1;36m┃          \033[1;33m学生成绩管理系统\033[1;36m          ┃\033[0m\n");
    printf("\033[1;36m┃        \033[1;33mLogin Menu (登录菜单)     \033[1;36m  ┃\033[0m\n");
    printf("\033[1;36m┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫\033[0m\n");
    printf("\033[1;36m┃                                    ┃\033[0m\n");
    printf("\033[1;36m┃    \033[1;32m[l] ────>  login      (登录)    \033[1;36m┃\033[0m\n");
    printf("\033[1;36m┃                                    ┃\033[0m\n");
    printf("\033[1;36m┃    \033[1;32m[r] ────>  register   (注册)    \033[1;36m┃\033[0m\n");
    printf("\033[1;36m┃                                    ┃\033[0m\n");
    printf("\033[1;36m┃    \033[1;31m[q] ────>  quit       (退出)    \033[1;36m┃\033[0m\n");
    printf("\033[1;36m┃                                    ┃\033[0m\n");
    printf("\033[1;36m┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\033[0m\n");
}

// 打印功能菜单框架
void print_menu_frame()
{
    printf(COLOR_CYAN "┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓" COLOR_RESET "\n");
    printf(COLOR_CYAN "┃                    " COLOR_YELLOW "学生成绩管理系统" COLOR_CYAN "                     ┃" COLOR_RESET "\n");
    printf(COLOR_CYAN "┃                " COLOR_YELLOW "Function Menu (功能菜单)     " COLOR_CYAN "            ┃" COLOR_RESET "\n");
    printf(COLOR_CYAN "┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫" COLOR_RESET "\n");
    printf(COLOR_CYAN "┃                                                         ┃" COLOR_RESET "\n");
}

// 打印菜单底部
void print_menu_footer()
{
    printf(COLOR_CYAN "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛" COLOR_RESET "\n");
}

// 打印菜单项
void print_menu_item(const char *content, const char *color)
{
    char temp = content[1];
    printf(COLOR_CYAN "┃   ");
    printf("%s", color);
    printf("%-55s", content); // 50字符宽度保持对齐
    if (temp != 'q')
    {
        printf(COLOR_CYAN "   ┃" COLOR_RESET "\n");
    }
    else
    {
        printf(COLOR_CYAN "   ┃" COLOR_RESET "\n");
    }
    printf(COLOR_CYAN "┃" COLOR_RESET "                                                         " COLOR_CYAN "┃" COLOR_RESET "\n");
}

// 显示功能菜单
void display_menu_function()
{
    print_menu_frame();
    print_menu_item("[i] ────>  insert student        (添加学生信息)", COLOR_GREEN);
    print_menu_item("[d] ────>  delete student        (删除学生信息)", COLOR_GREEN);
    print_menu_item("[u] ────>  update student        (修改学生信息)", COLOR_GREEN);
    print_menu_item("[s] ────>  show single student   (查询单个学生)", COLOR_GREEN);
    print_menu_item("[b] ────>  show all students     (显示所有学生)", COLOR_GREEN);
    print_menu_item("[r] ────>  register admin        (注册管理员)", COLOR_GREEN);
    print_menu_item("[e] ────>  delete user account   (注销普通用户账号)", COLOR_GREEN);
    print_menu_item("[a] ────>  delete admin account  (注销管理员账号)", COLOR_GREEN);
    print_menu_item("[q] ────>  quit                  (退出)", COLOR_RED);
    print_menu_footer();
}

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