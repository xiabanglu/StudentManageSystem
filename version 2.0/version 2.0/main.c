#include "common.h"
#include "menu.h"
#include "search.h"
#include "file.h"

// 全局变量定义
School *school = NULL;
int rank = 0;

// 循环变量
int login_quit = 0;
int func_quit = 0;
int score_quit = 0;

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
    Menu *score_menu = create_menu(MENU_SCORE);

    while (1)
    {
        while (!login_quit)
        {
            event_loop(login_menu, &login_quit, MENU_LOGIN);
            if (login_quit == 1 && rank > 0)
            {
                login_quit = 1;
                func_quit = 0;
                score_quit = 1;
            }
            else if (login_quit == 2 && rank == 0)
            {
                free(login_menu);
                free(function_menu);
                free(score_menu);
                freeSchool(school);
                return 0;
            }
        }
        while (!func_quit && rank > 0)
        {
            event_loop(function_menu, &func_quit, MENU_FUNCTION);
            if (func_quit == 1 && rank > 0)
            {
                login_quit = 1;
                func_quit = 1;
                score_quit = 0;
            }
            else if (func_quit == 2 && rank > 0)
            {
                rank = 0;
                login_quit = 0;
                func_quit = 1;
                score_quit = 1;
            }
        }
        while (!score_quit && rank > 0)
        {
            event_loop(score_menu, &score_quit, MENU_SCORE);
            if (score_quit == 2 && rank > 0)
            {
                login_quit = 1;
                func_quit = 0;
                score_quit = 1;
            }
        }
    }
}

// gcc main.c event.c file.c login.c menu.c search.c log.c -o main.exe