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
    printf(HEADER_LINE "\n");
    printf(COLOR_YELLOW "                  欢迎使用学生管理系统!\n" COLOR_RESET);
    printf(COLOR_YELLOW "            Welcome to student manage system!\n" COLOR_RESET);
    school = initSchool("NUIST", _MAX_GRADE_NUM_PER_SCHOOL_, _MAX_CLASS_NUM_PER_GRADE_, _MAX_STUDENT_NUM_PER_CLASS_);
    loadStudentFromFile("student.txt", school);

    Menu *current_menu = NULL;
    while (!is_quit)
    {
        current_menu = event_loop(current_menu, &is_quit);
       system("cls");
    }
}

// version 2.0 使用方法：

// 开发环境：VScode

// 编译方法：打开本项目文件夹，右击空白处打开终端，输入该命令行指令：gcc main.c event.c file.c login.c menu.c search.c log.c score.c -o main.exe 并回车，即可生成 main.exe

// 双击运行 main.exe 即可 (Tips: account.txt, student.txt, logInfo.txt 必须同属一个文件夹下!)