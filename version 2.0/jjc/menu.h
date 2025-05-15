#ifndef __MENU_H__
#define __MENU_H__

int flag = 0;

#include "event.h"
#include "search.h"
#include <stdio.h>
#include <stdlib.h>

School *school = NULL;

typedef enum MenuType
{
    MENU_LOGIN,
    MENU_SHOW,
} MenuType;

typedef struct Menu
{
    const char *show;
    Event *event;
    MenuType type;
} Menu;

const char *show_menu[] = {
    "i - insert new record",
    "d - delete record",
    "u - update record",
    "f - find record",
    "q - quit",
    NULL};

const char *login_menu[] = {
    "l - student login",
    "r - register",
    "k - delete user",
    NULL};

Menu *create_show_menu()
{
    Menu *menu = (Menu *)malloc(sizeof(Menu));
    menu->show = "Show Menu";
    menu->event = (Event *)malloc(sizeof(Event) * 3);
    menu->event[0].event_type = EVENT_REGISTER_STUDENT;
    menu->event[1].event_type = EVENT_DELETE_STUDENT;
    menu->event[2].event_type = EVENT_UPDATE_STUDENT;

    for (int i = 0; i < 3; i++)
    {
        registerEvent(&menu->event[i], menu->event[i].event_type);
    }
    menu->type = MENU_SHOW;
    return menu;
}

Menu *create_login_menu()
{
    Menu *menu = (Menu *)malloc(sizeof(Menu));
    menu->show = "Login Menu";
    menu->event = (Event *)malloc(sizeof(Event) * 3);

    menu->event[0].event_type = EVENT_LOGIN_USER;
    menu->event[1].event_type = EVENT_REGISTER_USER;
    menu->event[2].event_type = EVENT_DELETE_USER;

    for (int i = 0; i < 3; i++)
    {
        registerEvent(&menu->event[i], menu->event[i].event_type);
    }

    menu->type = MENU_LOGIN;
    return menu;
}

char getchoice(const char *greet, const char *choices[])
{
    short chosen = 0;
    char selected;
    const char **option;
    do
    {
        printf("\033[1;32m-------------------------\033[0m\n");
        printf("Menu: %s\n", greet);
        option = choices;

        while (*option)
        {
            printf("%s\n", *option);
            option++;
        }

        selected = getchar();
        while (selected == '\n')
        {
            selected = getchar();
        }
        while (getchar() != '\n')
            ; // clear the input buffer

        option = choices;
        while (*option)
        {
            if (selected == *option[0])
            {
                chosen = 1;
                break;
            }
            option++;
        }
        if (!chosen)
        {
            printf("Incorrect choice, select again\n");
        }
    } while (!chosen);
    return selected;
}

void event_loop(Menu *menu, int *is_quit)
{
    int selected;
    int id;
    char name[10];
    int age;
    float score[7];
    char password[20];
    do
    {
        switch (menu->type)
        {
        case MENU_LOGIN:
            selected = getchoice("Login Menu", login_menu);
            break;
        case MENU_SHOW:
            selected = getchoice("Show Menu", show_menu);
            break;
        default:
            printf("Invalid menu type\n");
            return;
        }
        printf("\033[1;32m-------------------------\033[0m\n");
        switch (selected)
        {
        case 'l':
            printf("User login\n");
            printf("Enter ID and password:\n");
            scanf("%d", &id);
            scanf("%s", password);
            flag = menu->event[0].callback.login("user.txt", id, password);
            if (flag)
            {
                printf("Login successful! %d\n", flag);
                *is_quit = 1;
                return;
            }
            else
            {
                printf("Login failed!\n");
            }
            break;
        case 'r':
            printf("Register\n");
            printf("Enter ID and password:\n");
            scanf("%d", &id);
            scanf("%s", password);
            menu->event[1].callback.registerUser("user.txt", id, password);

            break;
        case 'k':
            printf("Delete user\n");
            printf("Enter ID:\n");
            scanf("%d", &id);
            menu->event[2].callback.deleteUser("user.txt", id);
            break;
        case 'i':
        {
            if (flag == 1)
            {
                printf("\033[31mYou are not logged in as admin\033[0m\n");
                break;
            }
            printf("Insert new record\n");
            printf("Enter student ID, name, age and scores(7):\n");
            scanf("%d", &id);
            scanf("%s", name);
            scanf("%d", &age);

            for (int i = 0; i < 7; i++)
            {
                scanf("%f", &score[i]);
            }
            menu->event[0].callback.registerStudent(school, id, name, age, score);
            break;
        }
        case 'd':
        {
            if (flag == 1)
            {
                printf("\033[31mYou are not logged in as admin\033[0m\n");
                break;
            }
            printf("Delete record\n");
            printf("Enter student ID:\n");
            scanf("%d", &id);
            menu->event[1].callback.deleteStudent(school, id);
            break;
        }
        case 'u':
        {
            if (flag == 1)
            {
                printf("\033[31mYou are not logged in as admin\033[0m\n");
                break;
            }
            printf("Update record\n");
            printf("Enter student ID, name, age and scores(7):\n");

            scanf("%d", &id);
            scanf("%s", name);
            scanf("%d", &age);
            for (int i = 0; i < 7; i++)
            {
                scanf("%f", &score[i]);
            }
            menu->event[2].callback.updateStudent(school, id, name, age, score);
            break;
        }
        case 'q':
            printf("Quit\n");
            *is_quit = 1;
            break;
        case 'f':
        {
            printf("Find student\n");
            printf("Enter student ID:\n");
            scanf("%d", &id);
            Student **student = getStudent(school, id);
            if (student != NULL)
            {
                printf("Student found: %s, %d\n", (*student)->name, (*student)->age);
            }
            else
            {
                printf("\033[31mStudent not found\033[0m\n");
            }
            break;
        }
        default:
            printf("Invalid choice\n");
            break;
        }
        printf("\033[1;32m-------------------------\033[0m\n");
    } while (selected != 'q');
}

#endif // __MENU_H__