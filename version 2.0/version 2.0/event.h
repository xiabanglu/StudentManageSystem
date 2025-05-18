#ifndef EVENT_H
#define EVENT_H

#include <stdio.h>
#include <stdlib.h>
#include "login.h"
#include "log.h"
#include "search.h"

extern School *school;
int rank = 0;

void handle_show_records()
{
    printf("学生记录:\n");
    for (int i = 0; i < school->size; i++)
    {
        for (int j = 0; j < school->grades[i]->size; j++)
        {
            Clazz *clazz = school->grades[i]->classes[j];
            for (int k = 0; k < clazz->size; k++)
            {
                Student *student = clazz->students[k];
                if (student == NULL)
                    continue;
                printf("ID: %d, 姓名: %s, 性别: %s, 年龄: %d, 所属学校:%s\n", student->indices.id, student->info.name, student->info.gender, student->info.age, student->info.schoolName);
            }
        }
    }
}

void handle_login()
{
    char username[20];
    char password[20];

    printf("请按照格式输入: \n");
    printf("用户名 密码 \n");
    scanf("%s %s", username, password);

    rank = login("user.txt", username, password);

    if (rank == -1)
    {
        Log("File is error", ERROR);
        rank = 0;
        return;
    }

    if (rank == 0)
    {
        Log("Login failed", ERROR);
        return;
    }
    else
    {
        if (rank == 1)
        {
            Log("Login successful", INFO);
        }
        else
        {
            Log("Login as admin", INFO);
        }

    }
}

void handle_register()
{
    char username[20];
    char password[20];

    printf("请按照格式输入: \n");
    printf("用户名 密码 \n");
    scanf("%s %s", username, password);

    register_user("user.txt", username, password);
    Log("Register successful", INFO);
}

void handle_delete_user()
{
    char username[20];
    char password[20];

    printf("请按照格式输入: \n");
    printf("用户名 密码 \n");
    scanf("%s %s", username, password);

    delete_user("user.txt", username);
    Log("User deleted", INFO);
}

void handle_insert_record()
{
    int id;
    Info *newStudent = (Info *)malloc(sizeof(Info));

    if (newStudent == NULL)
    {
        printf("Memory allocation failed\n");
        return;
    }

    printf("请按照格式输入: \n");
    printf("ID 姓名 性别 年龄 所属学校: \n");
    scanf("%d %s %s %d %s", &id, newStudent->name, newStudent->gender, &newStudent->age, newStudent->schoolName);

    registerStudent(school, id, newStudent);
    Log("Student registered", INFO);
    free(newStudent);
}

void handle_delete_record()
{
    int id;
    printf("请输入ID: \n");
    scanf("%d", &id);
    deleteStudent(school, id);
}

void handle_update_record()
{
    int id;
    double score[10];
    Info *newStudent = (Info *)malloc(sizeof(Info));

    if (newStudent == NULL)
    {
        printf("Memory allocation failed\n");
        return;
    }

    printf("请按照格式输入: \n");
    printf("ID 姓名 性别 年龄 所属学校: \n");
    scanf("%d %s %s %d %s", &id, newStudent->name, newStudent->gender, &newStudent->age, newStudent->schoolName);

    printf("请录入十次成绩: \n");
    for (int i = 0; i < 10; i++)
    {
        scanf("%lf", &score[i]);
    }

    updateStudent(school, id, newStudent, score);
    free(newStudent);
}

void handle_find_record()
{
    int id;
    printf("请输入ID: \n");
    scanf("%d", &id);

    if (id <= 0)
    {
        Log("Invalid id", ERROR);
        getchar();
        return;
    }

    Student **student = getStudent(school, id);
    if (student == NULL)
    {
        Log("Student not found", ERROR);
        return;
    }
    else
        Log("Student found", INFO);

    printf("姓名: %s 性别: %s 年龄: %d 所属学校: %s\n各科分数: ", (*student)->info.name, (*student)->info.gender, (*student)->info.age, (*student)->info.schoolName);
    for (int i = 0; i < 10; i++)
    {
        printf("%lf ", (*student)->score[i]);
    }
    printf("\n");
}

void handle_quit()
{
    printf("欢迎下次使用\n");
}

#endif // EVENT_H