#include "common.h"
#include "menu.h"
#include "search.h"
#include "file.h"

// 全局变量定义
School *school = NULL;
int rank = 0;

int is_quit = 0;

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

    Menu *current_menu = NULL;

    while (!is_quit)
    {
        current_menu = event_loop(current_menu, &is_quit);
        system("cls");
    }
}

// gcc main.c event.c file.c login.c menu.c search.c log.c -o main.exe