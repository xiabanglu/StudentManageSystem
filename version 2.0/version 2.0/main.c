#include "menu.h"

School *school = NULL;
int rank = 0;

int main()
{
    printf("\033[1;32m---------------------------------\033[0m\n");
    printf("\033[1;34mWelcome to student manage system!\033[0m\n");
    printf("\033[1;34m(欢迎使用学生成绩管理系统!)\033[0m\n");

    school = createSchool("NUIST", _MAX_GRADE_NUM_PER_SCHOOL_);
    if (school == NULL)
    {
        printf("Failed to create school\n");
        return -1;
    }

    for (int i = 0; i < _MAX_GRADE_NUM_PER_SCHOOL_; i++)
    {
        initGrade(&school->grades[i], _MAX_CLASS_NUM_PER_GRADE_);

        for (int j = 0; j < _MAX_CLASS_NUM_PER_GRADE_; j++)
        {
            initClass(&school->grades[i]->classes[j], _MAX_STUDENT_NUM_PER_CLASS_);
        }
    }

    // 加载学生信息
    loadStudentFromFile("student.txt", school);

    int is_quit = 0;
    Menu *login_menu = create_menu(MENU_LOGIN);
    Menu *function_menu = create_menu(MENU_FUNCTION);

    while (!is_quit)
    {
        rank = 0;                                   // 重置权限状态
        Menu *login_menu = create_menu(MENU_LOGIN); // 每次循环创建新的登录菜单
        int login_quit = 0;
        printf("\033[1;33m=== 登录界面 ===\033[0m\n");
        event_loop(login_menu, &login_quit, 1); // 登录循环

        free(login_menu); // 释放登录菜单内存

        if (login_quit)
        {
            is_quit = 1; // 登录界面按q退出程序
            continue;
        }

        if (rank > 0)
        { // 登录成功
            Menu *function_menu = create_menu(MENU_FUNCTION);
            int func_quit = 0;
            printf("\033[1;33m=== 功能菜单 ===\033[0m\n");
            while (!func_quit)
            {
                event_loop(function_menu, &func_quit, 0); // 功能循环
            }
            free(function_menu); // 释放功能菜单内存
        }
    }

    FreeSchool(school);
    Log("系统已安全退出", INFO);
    return 0;
}