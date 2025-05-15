#pragma once
#include "search.h"
#include "login.h"
#include <string.h>

// 删除学生的函数
void deleteStudent_(School *school, int id)
{
    DeleteStudent(*getStudent(school, id)); // 从学校中删除指定ID的学生
}

// 更新学生信息的函数
void updateStudent_(School *school, int id, char *name, int age, float score[7])
{
    Student **student = getStudent(school, id); // 获取指定ID的学生

    if (student == NULL)
    {
        printf("Student not found\n"); // 如果学生未找到，打印提示信息
        return;
    }

    (*student)->age = age; // 更新学生年龄
    if ((*student)->name == NULL)
    {
        (*student)->name = (char *)malloc(sizeof(char) * 10); // 为学生姓名分配内存
    }

    strcpy((*student)->name, name); // 更新学生姓名

    for (int i = 0; i < 7; i++)
    {
        (*student)->score[i] = score[i]; // 更新学生成绩
    }
}

// 事件回调函数的联合体
typedef union EventCallback
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

// 事件类型的枚举
typedef enum EventType
{
    EVENT_REGISTER_STUDENT, // 注册学生事件
    EVENT_LOGIN_USER, // 用户登录事件
    EVENT_DELETE_STUDENT, // 删除学生事件
    EVENT_UPDATE_STUDENT, // 更新学生事件
    EVENT_GET_STUDENT, // 获取学生事件
    EVENT_GET_CLASS, // 获取班级事件
    EVENT_GET_GRADE, // 获取年级事件
    EVENT_REGISTER_USER, // 注册用户事件
    EVENT_DELETE_USER, // 删除用户事件
} EventType;

// 事件结构体
typedef struct Event
{
    EventType event_type; // 事件类型
    EventCallback callback; // 事件回调函数
} Event;

// 注册事件的函数
void registerEvent(Event *event, EventType type)
{
    event->event_type = type; // 设置事件类型

    switch (type)
    {
    case EVENT_REGISTER_STUDENT:
        event->callback.registerStudent = registerStudent; // 注册学生回调
        break;
    case EVENT_DELETE_STUDENT:
        event->callback.deleteStudent = deleteStudent_; // 删除学生回调
        break;
    case EVENT_UPDATE_STUDENT:
        event->callback.updateStudent = updateStudent_; // 更新学生回调
        break;
    case EVENT_GET_STUDENT:
        event->callback.getStudent = getStudent; // 获取学生回调
        break;
    case EVENT_GET_CLASS:
        event->callback.getClass = getClass; // 获取班级回调
        break;
    case EVENT_GET_GRADE:
        event->callback.getGrade = getGrade; // 获取年级回调
        break;
    case EVENT_REGISTER_USER:
        event->callback.registerUser = register_user; // 注册用户回调
        printf("register_user\n");
        break;
    case EVENT_DELETE_USER:
        event->callback.deleteUser = delete_user; // 删除用户回调
        break;
    case EVENT_LOGIN_USER:
        event->callback.login = login; // 登录回调
        break;
    default:
        break; // 默认情况不做处理
    }
}