#include "menu.h"
#include "file.h"
#include "event.h"
#include "login.h"
#include <stdlib.h>
#include "school.h"
#include "grade.h"
#include "class.h"
#include "student.h"

int main()
{
    printf("\033[1;32m-------------------------\033[0m\n");

    // 初始化
    School *school = createSchool("NUIST", _MAX_GRADE_NUM_PER_SCHOOL_);
    for (int i = 0; i < _MAX_GRADE_NUM_PER_SCHOOL_; i++)
    {
        initGrade(&school->grades[i], _MAX_CLASS_NUM_PER_GRADE_);

        for (int j = 0; j < _MAX_CLASS_NUM_PER_GRADE_; j++)
        {
            initClass(&school->grades[i]->classes[j], _MAX_STUDENT_NUM_PER_CLASS_);
        }
    }

    // 读取学生信息
    loadStudentFromFile(school, "student.txt");

    // 退出标志
    int is_quit = 0;

    Menu *login_menu = create_login_menu(); // 创建登录菜单
    Menu *menu = create_show_menu();        // 创建显示菜单

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