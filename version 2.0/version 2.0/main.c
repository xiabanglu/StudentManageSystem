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
    printf(COLOR_GREEN "欢迎使用学生管理系统\n" COLOR_RESET);
    printf(COLOR_GREEN "Welcome to student manage system\n" COLOR_RESET);

    // 初始化学校数据结构
    school = createSchool("NUIST", _MAX_GRADE_NUM_PER_SCHOOL_);
    if (school == NULL)
    {
        printf("创建学校失败\n");
        return -1;
    }

    // 加载学生数据
    loadStudentFromFile("student.txt", school);

    // 创建菜单(只需创建一次)
    Menu *login_menu = create_menu(MENU_LOGIN);
    Menu *function_menu = create_menu(MENU_FUNCTION);
    // int is_quit = 0;

    while (1)
    {
        // 登录菜单循环
        int login_quit = 0;
        while (!login_quit)
        {
            event_loop(login_menu, &login_quit, 1);
            if (login_quit == 1 && rank == 0)
            { // 退出程序
                FreeSchool(school);
                return 0;
            }
        }

        // 功能菜单循环
        int func_quit = 0;
        while (!func_quit && rank > 0)
        {
            event_loop(function_menu, &func_quit, 0);
            if (func_quit)
            {
                rank = 0;       // 重置权限
                login_quit = 0; // 返回登录菜单
            }
        }
    }

    // 释放资源
    free(login_menu);
    free(function_menu);
    FreeSchool(school);
    Log("系统已安全退出", INFO);
    return 0;
}

// gcc main.c event.c file.c login.c menu.c search.c log.c -o main.exe