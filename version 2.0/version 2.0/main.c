#include "common.h"
#include "menu.h"
#include "search.h"
#include "file.h"

// 全局变量定义
School *school = NULL;
int rank = 0;

int main()
{
    // 初始化界面
    printf(HEADER_LINE "\n");

    printf(COLOR_YELLOW "                  欢迎使用学生管理系统!\n" COLOR_RESET);
    printf(COLOR_YELLOW "            Welcome to student manage system!\n" COLOR_RESET);

    // 初始化学校
    school = initSchool("NUIST", _MAX_GRADE_NUM_PER_SCHOOL_, _MAX_CLASS_NUM_PER_GRADE_, _MAX_STUDENT_NUM_PER_CLASS_);

    // 加载学生数据
    loadStudentFromFile("student.txt", school);

    // 创建菜单
    Menu *login_menu = create_menu(MENU_LOGIN);
    Menu *function_menu = create_menu(MENU_FUNCTION);

    while (1)
    {
        // 登录菜单循环
        int login_quit = 0;
        while (!login_quit)
        {
            event_loop(login_menu, &login_quit, MENU_LOGIN);
            if (login_quit == 2 && rank == 0)
            {
                free(login_menu);
                free(function_menu);
                freeSchool(school);
                return 0;
            }
        }
        // 功能菜单循环
        int func_quit = 0;
        while (!func_quit && rank > 0)
        {
            event_loop(function_menu, &func_quit, MENU_FUNCTION);
            if (func_quit)
            {
                rank = 0;       // 重置权限
                login_quit = 0; // 返回登录菜单
            }
        }

        int score_quit = 0;
        while (!score_quit && rank > 0)
        {
            event_loop(score_menu, &score_quit, MENU_SCORE);
            if (score_quit)
            {
                func_quit = 0; // 返回功能菜单
            }
        }
    }
}

// gcc main.c event.c file.c login.c menu.c search.c log.c -o main.exe