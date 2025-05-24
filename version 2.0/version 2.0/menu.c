#include "menu.h"
#include "event.h"
#include "score.h"
#include "log.h"

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
    {"[b] ────>  show all students     (查询所有学生)", 'b', handle_show_records},
    {"[c] ────>  score statistics      (统计学生成绩)", 'c', handle_score_statistics},
    {"[r] ────>  register admin        (注册管理员号)", 'r', handle_register_admin},
    {"[e] ────>  delete user account   (注销普通用户)", 'e', handle_delete_user},
    {"[a] ────>  delete admin account  (注销管理员号)", 'a', handle_delete_admin},
    {"[q] ────>  quit                  (返回登录菜单)", 'q', handle_quit},
    {NULL, '\0', NULL}};

static const MenuItem score_items[] = {
    {"[s] ────>  student score      (学生分数情况)", 's', handle_student_score},
    {"[c] ────>  class score        (班级分数情况)", 'c', handle_class_score},
    {"[q] ────>  quit               (返回功能菜单)", 'q', handle_quit},
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
        char message[10];
        scanf("%10s", message);
        size_t len = strlen(message);
        if (len - 1)
        {
            Log("读取输入时:请输入单个字符而不是字符串", WARNING);
            return '0';
        }
        else
        {
            selected = message[0];
        }

        // 检查选择是否有效
        for (item = items; item->description != NULL; item++)
        {
            if (selected == item->choice)
            {
                return selected;
            }
        }

        printf(HEADER_LINE "\n");
        Log("读取输入时:没有这个选项", WARNING);
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
                else if (selected == 'c' && menu->type == MENU_FUNCTION)
                {
                    if (rank != 2 && rank != 3)
                    {
                        Log("学生统计信息时:你的权限不够", ERROR);
                        return NULL;
                    }
                    menu = MenuLists[2];
                    return menu;
                }
                else if (selected == 'q')
                {
                    if (menu->type == MENU_LOGIN)
                    {
                        *is_quit = 1;
                        return menu;
                    }
                    else if (menu->type == MENU_FUNCTION)
                    {
                        rank = 0;
                        clear_username();
                        menu = MenuLists[0];
                        return menu;
                    }
                    else if (menu->type == MENU_SCORE)
                    {
                        menu = MenuLists[1];
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
    //                "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
    printf(COLOR_CYAN "             ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓" COLOR_RESET "\n");
    printf(COLOR_CYAN "             ┃          " COLOR_YELLOW "学生成绩管理系统" COLOR_CYAN "          ┃" COLOR_RESET "\n");
    printf(COLOR_CYAN "             ┃        " COLOR_YELLOW "Login Menu (登录菜单)     " COLOR_CYAN "  ┃" COLOR_RESET "\n");
    printf(COLOR_CYAN "             ┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫" COLOR_RESET "\n");
    printf(COLOR_CYAN "             ┃                                    ┃" COLOR_RESET "\n");
    printf(COLOR_CYAN "             ┃    " COLOR_GREEN "[l] ────>  login      (登录)    " COLOR_CYAN "┃" COLOR_RESET "\n");
    printf(COLOR_CYAN "             ┃                                    ┃" COLOR_RESET "\n");
    printf(COLOR_CYAN "             ┃    " COLOR_GREEN "[r] ────>  register   (注册)    " COLOR_CYAN "┃" COLOR_RESET "\n");
    printf(COLOR_CYAN "             ┃                                    ┃" COLOR_RESET "\n");
    printf(COLOR_CYAN "             ┃    " COLOR_RED "[q] ────>  quit       (退出)    " COLOR_CYAN "┃" COLOR_RESET "\n");
    printf(COLOR_CYAN "             ┃                                    ┃" COLOR_RESET "\n");
    printf(COLOR_CYAN "             ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛" COLOR_RESET "\n");
}

// 显示功能菜单
void display_menu_function()
{
    //                "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
    printf(COLOR_CYAN "┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n" COLOR_RESET);
    printf(COLOR_CYAN "┃                      " COLOR_YELLOW "学生成绩管理系统" COLOR_CYAN "                         ┃\n" COLOR_RESET);
    printf(COLOR_CYAN "┃                   " COLOR_YELLOW "Function Menu (功能菜单)     " COLOR_CYAN "               ┃\n" COLOR_RESET);
    printf(COLOR_CYAN "┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫\n" COLOR_RESET);
    printf(COLOR_CYAN "┃                                                               ┃\n" COLOR_RESET);
    printf(COLOR_CYAN "┃        " COLOR_GREEN "[i] ────>  insert student        (添加学生信息)   " COLOR_CYAN "     ┃\n" COLOR_RESET);
    printf(COLOR_CYAN "┃                                                               ┃\n" COLOR_RESET);
    printf(COLOR_CYAN "┃        " COLOR_GREEN "[d] ────>  delete student        (删除学生信息)   " COLOR_CYAN "     ┃\n" COLOR_RESET);
    printf(COLOR_CYAN "┃                                                               ┃\n" COLOR_RESET);
    printf(COLOR_CYAN "┃        " COLOR_GREEN "[u] ────>  update student        (修改学生信息)   " COLOR_CYAN "     ┃\n" COLOR_RESET);
    printf(COLOR_CYAN "┃                                                               ┃\n" COLOR_RESET);
    printf(COLOR_CYAN "┃        " COLOR_GREEN "[s] ────>  show single student   (查询单个学生)   " COLOR_CYAN "     ┃\n" COLOR_RESET);
    printf(COLOR_CYAN "┃                                                               ┃\n" COLOR_RESET);
    printf(COLOR_CYAN "┃        " COLOR_GREEN "[b] ────>  show all students     (查询所有学生)   " COLOR_CYAN "     ┃\n" COLOR_RESET);
    printf(COLOR_CYAN "┃                                                               ┃\n" COLOR_RESET);
    printf(COLOR_CYAN "┃        " COLOR_GREEN "[c] ────>  score statistics      (统计学生成绩)   " COLOR_CYAN "     ┃\n" COLOR_RESET);
    printf(COLOR_CYAN "┃                                                               ┃\n" COLOR_RESET);
    printf(COLOR_CYAN "┃        " COLOR_GREEN "[r] ────>  register admin        (注册管理员号)   " COLOR_CYAN "     ┃\n" COLOR_RESET);
    printf(COLOR_CYAN "┃                                                               ┃\n" COLOR_RESET);
    printf(COLOR_CYAN "┃        " COLOR_GREEN "[e] ────>  delete user account   (注销普通用户)   " COLOR_CYAN "     ┃\n" COLOR_RESET);
    printf(COLOR_CYAN "┃                                                               ┃\n" COLOR_RESET);
    printf(COLOR_CYAN "┃        " COLOR_GREEN "[a] ────>  delete admin account  (注销管理员号)   " COLOR_CYAN "     ┃\n" COLOR_RESET);
    printf(COLOR_CYAN "┃                                                               ┃\n" COLOR_RESET);
    printf(COLOR_CYAN "┃        " COLOR_RED "[q] ────>  quit                  (返回登录菜单)   " COLOR_CYAN "     ┃\n" COLOR_RESET);
    printf(COLOR_CYAN "┃                                                               ┃\n" COLOR_RESET);
    printf(COLOR_CYAN "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n" COLOR_RESET);
}

// 显示成绩菜单
void display_menu_score()
{
    //                "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
    printf(COLOR_CYAN "    ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n" COLOR_RESET);
    printf(COLOR_CYAN "    ┃                  " COLOR_YELLOW "学生成绩管理系统" COLOR_CYAN "                    ┃\n" COLOR_RESET);
    printf(COLOR_CYAN "    ┃               " COLOR_YELLOW "Score Menu (成绩菜单)        " COLOR_CYAN "          ┃\n" COLOR_RESET);
    printf(COLOR_CYAN "    ┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫\n" COLOR_RESET);
    printf(COLOR_CYAN "    ┃                                                      ┃\n" COLOR_RESET);
    printf(COLOR_CYAN "    ┃        " COLOR_GREEN "[s] ────>  student      (学生分数情况)     " COLOR_CYAN "   ┃\n" COLOR_RESET);
    printf(COLOR_CYAN "    ┃                                                      ┃\n" COLOR_RESET);
    printf(COLOR_CYAN "    ┃        " COLOR_GREEN "[c] ────>  class        (班级分数情况)     " COLOR_CYAN "   ┃\n" COLOR_RESET);
    printf(COLOR_CYAN "    ┃                                                      ┃\n" COLOR_RESET);
    printf(COLOR_CYAN "    ┃        " COLOR_RED "[q] ────>  quit         (返回功能菜单)     " COLOR_CYAN "   ┃\n" COLOR_RESET);
    printf(COLOR_CYAN "    ┃                                                      ┃\n" COLOR_RESET);
    printf(COLOR_CYAN "    ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n" COLOR_RESET);
}