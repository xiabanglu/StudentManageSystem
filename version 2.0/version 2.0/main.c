#include "menu.h"

School *school = NULL;

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

    // loadFromFile()

    int is_quit = 0;

    Menu *login_menu = create_menu(MENU_LOGIN);
    Menu *show_menu = create_menu(MENU_FUNCTION);

    while (!is_quit)
    {
        printf("\033[1;33m请选择操作:\033[0m\n");
        event_loop(login_menu, &is_quit);
        printf("\033[1;32m---------------------------------\033[0m\n");
    }
    is_quit = 0;

    if (rank != 1 || rank != 2 || rank != 3)
    {
        return 0;
    }

    while (!is_quit)
    {
        printf("\033[1;33m请选择操作:\033[0m\n");
        event_loop(show_menu, &is_quit);
        printf("\033[1;32m---------------------------------\033[0m\n");
    }
    is_quit = 0;

    if (rank != 1 || rank != 2 || rank != 3)
    {
        return 0;
    }
}