#pragma once
#include "search.h"
#include "login.h"
#include <string.h>

void deleteStudent_(School *school, int id)
{
    DeleteStudent(*getStudent(school, id));
}

void updateStudent_(School *school, int id, char *name, int age, float score[7])
{
    Student **student = getStudent(school, id);

    if (student == NULL)
    {
        printf("Student not found\n");
        return;
    }

    (*student)->age = age;
    if ((*student)->name == NULL)
    {
        (*student)->name = (char *)malloc(sizeof(char) * 10);
    }

    strcpy((*student)->name, name);

    for (int i = 0; i < 7; i++)
    {
        (*student)->score[i] = score[i];
    }
}

typedef struct EventCallback
{
    void (*registerStudent)(School *school, int id, char *name, int age, float score[7]);
    void (*deleteStudent)(School *school, int id);
    void (*updateStudent)(School *school, int id, char *name, int age, float score[7]);

    Student **(*getStudent)(School *school, int id);
    Class_ **(*getClass)(Grade *grade, int id);
    Grade **(*getGrade)(School *school, int id);
    School *(*getSchool)(int id);

    void (*registerUser)(const char *file_path, const int id, const char *password);
    void (*deleteUser)(const char *file_path, const int id);
    int (*login)(const char *file_path, const int id, char *password);
} EventCallback;

typedef enum EventType
{

    EVENT_REGISTER_STUDENT,
    EVENT_LOGIN_USER,

    EVENT_DELETE_STUDENT,
    EVENT_UPDATE_STUDENT,

    EVENT_GET_STUDENT,
    EVENT_GET_CLASS,
    EVENT_GET_GRADE,

    EVENT_REGISTER_USER,
    EVENT_DELETE_USER,
} EventType;

typedef struct Event
{
    EventType event_type;

    EventCallback callback;
} Event;

void registerEvent(Event *event, EventType type)
{
    event->event_type = type;

    switch (type)
    {
    case EVENT_REGISTER_STUDENT:
        event->callback.registerStudent = registerStudent;
        break;
    case EVENT_DELETE_STUDENT:
        event->callback.deleteStudent = deleteStudent_;
        break;
    case EVENT_UPDATE_STUDENT:
        event->callback.updateStudent = updateStudent_;
        break;
    case EVENT_GET_STUDENT:
        event->callback.getStudent = getStudent;
        break;
    case EVENT_GET_CLASS:
        event->callback.getClass = getClass;
        break;
    case EVENT_GET_GRADE:
        event->callback.getGrade = getGrade;
        break;
    case EVENT_REGISTER_USER:
        event->callback.registerUser = register_user;
        printf("register_user\n");
        break;
    case EVENT_DELETE_USER:
        event->callback.deleteUser = delete_user;
        break;
    case EVENT_LOGIN_USER:
        event->callback.login = login;
        break;
    default:
        break;
    }
}