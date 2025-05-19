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
    printf("\033[1;32m---------------------------------\033[0m\n");
    printf("\033[1;34m欢迎使用学生成绩管理系统!\033[0m\n");
    printf("\033[1;34m(Welcome to student manage system!)\033[0m\n");

    // 初始化学校数据结构
    school = createSchool("NUIST", _MAX_GRADE_NUM_PER_SCHOOL_);
    if (school == NULL)
    {
        printf("创建学校失败\n");
        return -1;
    }

    // 初始化年级和班级
    for (int i = 0; i < _MAX_GRADE_NUM_PER_SCHOOL_; i++)
    {
        initGrade(&school->grades[i], _MAX_CLASS_NUM_PER_GRADE_);
        for (int j = 0; j < _MAX_CLASS_NUM_PER_GRADE_; j++)
        {
            initClass(&school->grades[i]->classes[j], _MAX_STUDENT_NUM_PER_CLASS_);
        }
    }

    // 加载学生数据
    loadStudentFromFile("student.txt", school);


    // 创建菜单(只需创建一次)
    Menu *login_menu = create_menu(MENU_LOGIN);
    Menu *function_menu = create_menu(MENU_FUNCTION);
    int is_quit = 0;

    while (!is_quit)
    {
        event_loop(login_menu, &is_quit, 1);
    }

    is_quit = 0;

    while (!is_quit)
    {
        printf("\033[1;33mPlease select an option:\033[0m\n");
        event_loop(function_menu, &is_quit, 0);
        printf("\033[1;32m-------------------------\033[0m\n");
    }

    // 释放资源
    free(login_menu);
    free(function_menu);
    FreeSchool(school);
    Log("系统已安全退出", INFO);
    return 0;
}