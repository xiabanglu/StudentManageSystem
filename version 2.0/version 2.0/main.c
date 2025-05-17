#include "menu.h"

School *school = NULL;
int rank = 0;

int main()
{
    printf("\033[1;32m-------------------------\033[0m\n");

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

    int is_quit = 0;

    Menu *login_menu = create_menu(MENU_LOGIN);
    Menu *show_menu = create_menu(MENU_SHOW);

    printf("Please login:\n");

    while (!is_quit)
    {
        event_loop(login_menu, &is_quit);
    }

    is_quit = 0;
    printf("\033[1;34mWelcome to the Student Management System\033[0m\n");

    while (!is_quit)
    {
        printf("\033[1;33mPlease select an option:\033[0m\n");
        event_loop(show_menu, &is_quit);
        printf("\033[1;32m-------------------------\033[0m\n");
    }

    return 0;
}