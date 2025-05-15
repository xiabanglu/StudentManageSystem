#include "menu.h"
#include "file.h"
#include "search.h"

int main()
{
    printf("\033[1;32m-------------------------\033[0m\n");
    school = createSchool("NUIST", _MAX_GRADE_NUM_);
    for (int i = 0; i < _MAX_GRADE_NUM_; i++)
    {
        initGrade(&school->Grades[i], _MAX_CLASS_NUM_);
        for (int j = 0; j < _MAX_CLASS_NUM_; j++)
        {
            initClass(&school->Grades[i]->Classes[j], _MAX_STUDENT_NUM_);
        }
    }

    CompileFile(school, "data.txt");
    int is_quit = 0;
    Menu *login_menu = create_login_menu();
    Menu *menu = create_show_menu();

    printf("please login:\n");

    while (!is_quit)
    {
        event_loop(login_menu, &is_quit);
    }

    is_quit = 0;
    printf("\033[1;34mWelcome to the Student Management System\033[0m\n");

    while (!is_quit)
    {
        printf("\033[1;33mPlease select an option:\033[0m\n");
        event_loop(menu, &is_quit);
        printf("\033[1;32m-------------------------\033[0m\n");
    }
}