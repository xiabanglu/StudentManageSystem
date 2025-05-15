#include "menu.h"
#include "file.h"
#include "search.h"

// 主函数
int main()
{
    printf("\033[1;32m-------------------------\033[0m\n");
    school = createSchool("NUIST", _MAX_GRADE_NUM_); // 创建学校实例
    for (int i = 0; i < _MAX_GRADE_NUM_; i++)
    {
        initGrade(&school->Grades[i], _MAX_CLASS_NUM_); // 初始化年级
        for (int j = 0; j < _MAX_CLASS_NUM_; j++)
        {
            initClass(&school->Grades[i]->Classes[j], _MAX_STUDENT_NUM_); // 初始化班级
        }
    }

    CompileFile(school, "data.txt"); // 从文件中编译学生信息
    int is_quit = 0; // 退出标志
    Menu *login_menu = create_login_menu(); // 创建登录菜单
    Menu *menu = create_show_menu(); // 创建显示菜单

    printf("please login:\n");

    while (!is_quit) // 登录循环
    {
        event_loop(login_menu, &is_quit); // 处理登录菜单事件
    }

    is_quit = 0; // 重置退出标志
    printf("\033[1;34mWelcome to the Student Management System\033[0m\n");

    while (!is_quit) // 主菜单循环
    {
        printf("\033[1;33mPlease select an option:\033[0m\n");
        event_loop(menu, &is_quit); // 处理主菜单事件
        printf("\033[1;32m-------------------------\033[0m\n");
    }
}