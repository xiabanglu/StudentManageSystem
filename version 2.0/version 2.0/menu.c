#include "menu.h"
#include "event.h"

// 暂定权限等级为 rank     1:普通用户    2：管理员    3：开发人员
static const MenuItem login_items[] = {
    {"[l] ────>  login      (登录)", 'l', handle_login},
    {"[r] ────>  register   (注册)", 'r', handle_register_user},
    {"[q] ────>  quit       (退出)", 'q', handle_quit},
    {NULL, '\0', NULL}};

static const MenuItem function_items[] = {
    {"[i] ────>  insert student        (添加学生信息)", 'i', handle_insert_record},
    {"[d] ────>  delete student        (删除学生信息)", 'd', handle_delete_record},
    {"[u] ────>  update student        (修改学生信息)", 'u', handle_update_record},
    {"[s] ────>  show single student   (查询单个学生)", 's', handle_show_record},
    {"[b] ────>  show all students     (显示所有学生)", 'b', handle_show_records},
    {"[c] ────>  score statistics      (成绩统计)", 'c', handle_score_statistics},
    {"[r] ────>  register admin        (注册管理员)", 'r', handle_register_admin},
    {"[e] ────>  delete user account   (注销普通用户账号)", 'e', handle_delete_user},
    {"[a] ────>  delete admin account  (注销管理员账号)", 'a', handle_delete_admin},
    {"[q] ────>  quit                  (返回)", 'q', handle_quit},
    {NULL, '\0', NULL}};

static const MenuItem score_items[] = {
    {"[s] ────>  student      (学生分数情况)", 's', handle_student_score},
    {"[c] ────>  class    (班级分数情况)", 'c', handle_class_score},
    {"[q] ────>  quit       (返回)", 'q', handle_quit},
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
    else if (type == MENU_FUNCTION)
    {
        menu->title = "Function Menu (功能菜单)";
        menu->items = function_items;
    }
    else if (type == MENU_SCORE)
    {
        menu->title = "Score Menu (成绩菜单)";
        menu->items = score_items;
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
        if (strcmp(greet, "Login Menu (登录菜单)") == 0)
        {
            display_menu_login();
        }
        else if (strcmp(greet, "Function Menu (功能菜单)") == 0)
        {
            display_menu_function();
        }
        else if (strcmp(greet, "Score Menu (成绩菜单)") == 0)
        {
            display_menu_score();
        }

        printf(HEADER_LINE "\n");
        printf(INPUT_PROMPT COLOR_YELLOW "Please enter a choice(请选择一个操作):\n\n" COLOR_RESET);
        printf(INPUT_PROMPT);

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

        printf(HEADER_LINE "\n");
        Log("no this choice(没有这个选项)", WARNING);
    } while (1);

    return '0';
}

// 事件循环
Menu *event_loop(Menu *menu, int *is_quit)
{
    char selected;
    const MenuItem *item;

    static Menu *MenuLists[3] = {NULL, NULL, NULL};

    if (menu == NULL)
    {
        for (int i = 0; i < 3; i++)
        {
            MenuLists[i] = create_menu(i);
        }
        menu = MenuLists[0];
    }

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
                    menu = MenuLists[1];
                    return menu;
                }
                if (selected == 'c')
                {
                    menu = MenuLists[2];
                    return menu;
                }
                if (selected == 'q')
                {
                    if (menu->type == MENU_LOGIN)
                    {
                        *is_quit = 1;
                        return menu;
                    }
                    else
                    {
                        menu = MenuLists[menu->type - 1];
                        return menu;
                    }
                }
            }
        }
    } while (!*is_quit);

    return menu;
}

// 显示登陆菜单
void display_menu_login()
{
    // printf(  "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━")
    printf("\033[1;36m         ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\033[0m\n");
    printf("\033[1;36m         ┃          \033[1;33m学生成绩管理系统\033[1;36m          ┃\033[0m\n");
    printf("\033[1;36m         ┃        \033[1;33mLogin Menu (登录菜单)     \033[1;36m  ┃\033[0m\n");
    printf("\033[1;36m         ┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫\033[0m\n");
    printf("\033[1;36m         ┃                                    ┃\033[0m\n");
    printf("\033[1;36m         ┃    \033[1;32m[l] ────>  login      (登录)    \033[1;36m┃\033[0m\n");
    printf("\033[1;36m         ┃                                    ┃\033[0m\n");
    printf("\033[1;36m         ┃    \033[1;32m[r] ────>  register   (注册)    \033[1;36m┃\033[0m\n");
    printf("\033[1;36m         ┃                                    ┃\033[0m\n");
    printf("\033[1;36m         ┃    \033[1;31m[q] ────>  quit       (退出)    \033[1;36m┃\033[0m\n");
    printf("\033[1;36m         ┃                                    ┃\033[0m\n");
    printf("\033[1;36m         ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\033[0m\n");
}

// 显示功能菜单
void display_menu_function()
{
    print_menu_function_frame();
    print_menu_function_item("[i] ────>  insert student        (添加学生信息)", COLOR_GREEN);
    print_menu_function_item("[d] ────>  delete student        (删除学生信息)", COLOR_GREEN);
    print_menu_function_item("[u] ────>  update student        (修改学生信息)", COLOR_GREEN);
    print_menu_function_item("[s] ────>  show single student   (查询单个学生)", COLOR_GREEN);
    print_menu_function_item("[b] ────>  show all students     (显示所有学生)", COLOR_GREEN);
    print_menu_function_item("[c] ────>  score statistics      (成绩统计)", COLOR_GREEN);
    print_menu_function_item("[r] ────>  register admin        (注册管理员号)", COLOR_GREEN);
    print_menu_function_item("[e] ────>  delete user account   (注销普通用户)", COLOR_GREEN);
    print_menu_function_item("[a] ────>  delete admin account  (注销管理员号)", COLOR_GREEN);
    print_menu_function_item("[q] ────>  quit                  (返回)", COLOR_RED);
    print_menu_function_footer();
}

// 显示成绩菜单
void display_menu_score()
{
    print_menu_score_frame();
    print_menu_score_item("[s] ────>  student      (学生分数情况)", COLOR_GREEN);
    print_menu_score_item("[c] ────>  class    (班级分数情况)", COLOR_GREEN);
    print_menu_score_item("[g] ────>  grade   (年级分数情况)", COLOR_GREEN);
    print_menu_score_item("[q] ────>  quit       (返回)", COLOR_RED);
    print_menu_score_footer();
}

// 打印功能菜单项
void print_menu_function_item(const char *content, const char *color)
{
    char temp = content[1];
    printf(COLOR_CYAN "┃   ");
    printf("%s", color);
    printf("%-58s", content); // 58字符宽度保持对齐
    printf(COLOR_CYAN "┃" COLOR_RESET "\n");
    printf(COLOR_CYAN "┃                                                         ┃" COLOR_RESET "\n");
}

// 打印功能菜单底部
void print_menu_function_footer()
{
    printf(COLOR_CYAN "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛" COLOR_RESET "\n");
}

// 打印功能菜单框架
void print_menu_function_frame()
{
    printf(COLOR_CYAN "┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓" COLOR_RESET "\n");
    printf(COLOR_CYAN "┃                    " COLOR_YELLOW "学生成绩管理系统" COLOR_CYAN "                     ┃" COLOR_RESET "\n");
    printf(COLOR_CYAN "┃                " COLOR_YELLOW "Function Menu (功能菜单)     " COLOR_CYAN "            ┃" COLOR_RESET "\n");
    printf(COLOR_CYAN "┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫" COLOR_RESET "\n");
    printf(COLOR_CYAN "┃                                                         ┃" COLOR_RESET "\n");
}

// 打印成绩菜单框架
void print_menu_score_frame()
{
    printf(COLOR_CYAN "┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓" COLOR_RESET "\n");
    printf(COLOR_CYAN "┃                         " COLOR_YELLOW "学生成绩管理系统" COLOR_CYAN "                         ┃" COLOR_RESET "\n");
    printf(COLOR_CYAN "┃                    " COLOR_YELLOW "  Score Menu (成绩菜单)     " COLOR_CYAN "                  ┃" COLOR_RESET "\n");
    printf(COLOR_CYAN "┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫" COLOR_RESET "\n");
    printf(COLOR_CYAN "┃                                                                  ┃" COLOR_RESET "\n");
}

// 打印成绩菜单项
void print_menu_score_item(const char *content, const char *color)
{
    printf(COLOR_CYAN "┃   ");
    printf("%s", color);
    printf("%-67s", content); // 67字符宽度保持对齐
    printf(COLOR_CYAN "┃" COLOR_RESET "\n");
    printf(COLOR_CYAN "┃                                                                  ┃" COLOR_RESET "\n");
}

// 打印成绩菜单底部
void print_menu_score_footer()
{
    printf(COLOR_CYAN "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛" COLOR_RESET "\n");
}