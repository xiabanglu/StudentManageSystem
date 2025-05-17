#ifndef EVENT_H
#define EVENT_H

#include <stdio.h>
#include <stdlib.h>
#include "login.h"
#include "log.h"
#include "search.h"

School *school;
int rank;

void handle_show_records()
{
    printf("Student records:\n");
    for (int i = 0; i < school->size; i++)
    {
        for (int j = 0; j < school->grades[i]->size; j++)
        {
            Class *class = school->grades[i]->classes[j];
            for (int k = 0; k < class->size; k++)
            {
                Student *student = class->students[k];
                if (student == NULL)
                    continue;
                printf("ID: %d, Name: %s, Gender: %s, Age: %d, FromSchool:%s\n", student->indices.id, student->info.name, student->info.gender, student->info.age, student->info.schoolName);
            }
        }
    }
}

void handle_login()
{
    char username[10];
    char password[10];

    printf("请输入账号和密码: \n");
    scanf("%s", username);
    scanf("%s", password);

    rank = login("user.txt", username, password);

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

        printf("\033[34m欢迎进入学生管理系统 \033[0m\n");
    }
}

void handle_register()
{
    char username[10];
    char password[10];
    register_user("user.txt", username, password);
    Log("Register successful", INFO);
}

void handle_delete_user()
{
    char username[10];
    char password[10];
    printf("Enter user id and password: \n");
    scanf("%s %s", username, password);
    delete_user("user.txt", username);
    Log("User deleted", INFO);
}

void handle_insert_record()
{
    int id;
    Info *newStudent = (Info *)malloc(sizeof(Info)); // 为 newStudent 分配内存
    if (newStudent == NULL)
    {
        printf("Memory allocation failed\n");
        return; // 检查内存分配是否成功
    }
    printf("Enter student id, name, gender, age, formSchool: \n");
    scanf("%d %s %s %d %s", &id, newStudent->name, newStudent->gender, &newStudent->age, newStudent->schoolName);
    registerStudent(school, id, newStudent);
    Log("Student registered", INFO);
    free(newStudent); // 使用完后释放内存
}

void handle_delete_record()
{
    int id;
    scanf("%d", &id);
    deleteStudent(school, id);
}

void handle_update_record()
{
    int id;
    double score[10];
    Info *newStudent = (Info *)malloc(sizeof(Info)); // 为 newStudent 分配内存
    if (newStudent == NULL)
    {
        printf("Memory allocation failed\n");
        return; // 检查内存分配是否成功
    }
    printf("Enter student id, name, gender, age, formSchool: \n");
    scanf("%d %s %s %d %s", &id, newStudent->name, newStudent->gender, &newStudent->age, newStudent->schoolName);
    for (int i = 0; i < 10; i++)
    {
        scanf("%lf", &score[i]);
    }
    updateStudent(school, id, newStudent, score);
    free(newStudent); // 使用完后释放内存
}

void handle_find_record()
{
    int id;
    printf("Enter student id: \n");
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
    printf("name: %s gender: %s age: %d fromSchool: %s\nscore: ", (*student)->info.name, (*student)->info.gender, (*student)->info.age, (*student)->info.schoolName);
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