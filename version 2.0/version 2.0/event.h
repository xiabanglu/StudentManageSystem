#include <stdio.h>
#include <stdlib.h>

#include "file.h"
#include "login.h"
// #include "log.h"
// #include "search.h"

extern School *school;
int rank = 0;

// 函数声明
void handle_login();
void handle_register_user();
void handle_quit();
void handle_insert_record();
void handle_delete_record();
void handle_update_record();
void handle_show_record();
void handle_show_records();
// void handle_score_statistics();
void handle_register_admin();
void handle_delete_user();
void handle_delete_admin();

void handle_login()
{
    char username[20];
    char password[20];
    printf("请依次输入: \n");
    printf("用户名:\n");
    scanf("%s", username);
    printf("密码:\n");
    scanf("%s", password);

    rank = login("user.txt", username, password);

    if (rank == -1)
    {
        Log("File is error!(不存在该文件!)", ERROR);
        rank = 0;
        return;
    }

    if (rank == 0)
    {
        Log("Login failed!(登录失败!)", ERROR);
        return;
    }
    else
    {
        if (rank == 1)
        {
            Log("Login successful!(登录成功!)", INFO);
        }
        else if (rank == 2)
        {
            Log("Login as admin(管理员权限)", INFO);
        }
        else if (rank == 3)
        {
            Log("Login as developer(开发人员权限)", INFO);
        }
    }
}

void handle_register_user()
{
    char username[20];
    char password[20];
    printf("请依次输入: \n");
    printf("用户名:\n");
    scanf("%s", username);
    printf("密码:\n");
    scanf("%s", password);

    save_register_user_to_file("user.txt", username, password);
}

void handle_insert_record()
{
    if (rank != 2 && rank != 3)
    {
        Log("Your authority is insufficient!(你的权限不够！)", ERROR);
        return;
    }

    int id;
    Student *newStudent = (Student *)malloc(sizeof(Student));
    double score[10];

    if (newStudent == NULL)
    {
        Log("Memory allocation failure!(内存分配失败!)", ERROR);
        return;
    }

    printf("请按照格式输入: \n");
    printf("ID 姓名 性别 年龄 所属学校: \n");
    scanf("%d %s %s %d %s",
          &id, newStudent->info.name, newStudent->info.gender,
          &newStudent->info.age, newStudent->info.schoolName);

    printf("请依次录入十次成绩(空格间隔每门成绩): \n");
    scanf("%lf %lf %lf %lf %lf %lf %lf %lf %lf %lf ", &score[0], &score[1], &score[2],
          &score[3], &score[4], &score[5], &score[6], &score[7], &score[8], &score[9]);

    registerStudent(school, id, newStudent, score);
    free(newStudent);
}

void handle_delete_record()
{
    if (rank != 2 && rank != 3)
    {
        Log("Your authority is insufficient!(你的权限不够！)", ERROR);
        return;
    }

    int id;
    printf("请输入ID: \n");
    scanf("%d", &id);

    deleteStudent(school, id);
}

void handle_update_record()
{
    if (rank != 2 && rank != 3)
    {
        Log("Your authority is insufficient!(你的权限不够！)", ERROR);
        return;
    }

    int id;
    Student *newStudent = (Student *)malloc(sizeof(Student));
    double score[10];

    if (newStudent == NULL)
    {
        Log("Memory allocation failure!(内存分配失败!)", ERROR);
        return;
    }

    printf("请按照格式输入: \n");
    printf("ID 姓名 性别 年龄 所属学校: \n");
    scanf("%d %s %s %d %s",
          &id, newStudent->info.name, newStudent->info.gender,
          &newStudent->info.age, newStudent->info.schoolName);

    printf("请依次录入十次成绩(空格间隔每门成绩): \n");
    scanf("%lf %lf %lf %lf %lf %lf %lf %lf %lf %lf ", &score[0], &score[1], &score[2],
          &score[3], &score[4], &score[5], &score[6], &score[7], &score[8], &score[9]);

    updateStudent(school, id, newStudent, score);
    free(newStudent);
}

void handle_show_record()
{
    if (rank != 1 && rank != 2 && rank != 3)
    {
        Log("Your authority is insufficient!(你的权限不够！)", ERROR);
        return;
    }

    int id;
    printf("请输入ID: \n");
    scanf("%d", &id);

    if (id <= 0)
    {
        Log("Invalid id!(ID错误!)", ERROR);
        return;
    }

    Student **student = getStudent(school, id);
    if (student == NULL)
    {
        Log("Student not found!(学生未找到!)", ERROR);
        return;
    }
    else
        Log("Student found!(该学生信息如下:)", INFO);

    printf("姓名: %s 性别: %s 年龄: %d 所属学校: %s\n各科分数\n: ", (*student)->info.name,
           (*student)->info.gender, (*student)->info.age, (*student)->info.schoolName);

    for (int i = 0; i < 10; i++)
    {
        printf("%lf ", (*student)->score[i]);
    }
    printf("\n");
}

void handle_show_records()
{
    if (rank != 2 && rank != 3)
    {
        Log("Your authority is insufficient!(你的权限不够！)", ERROR);
        return;
    }

    Log("所有学生信息如下:", INFO);
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
                printf("ID: %d, 姓名: %s, 性别: %s, 年龄: %d, 所属学校:%s\n", student->indices.id,
                       student->info.name, student->info.gender, student->info.age, student->info.schoolName);
            }
        }
    }
}

// void handle_score_statistics(){}

void handle_register_admin()
{
    if (rank != 3)
    {
        Log("Your authority is insufficient!(你的权限不够！)", ERROR);
        return;
    }
    char username[20];
    char password[20];
    printf("请依次输入: \n");
    printf("用户名:\n");
    scanf("%s", username);
    printf("密码:\n");
    scanf("%s", password);

    save_register_admin_to_file("user.txt", username, password);
}

void handle_delete_user()
{
    if (rank != 2 && rank != 3)
    {
        Log("Your authority is insufficient!(你的权限不够！)", ERROR);
        return;
    }

    char username[20];
    char password[20];
    printf("请依次输入: \n");
    printf("用户名:\n");
    scanf("%s", username);
    printf("密码:\n");
    scanf("%s", password);

    delete_user_from_file("user.txt", username, password);
}

void handle_delete_admin()
{
    if (rank != 3)
    {
        Log("Your authority is insufficient!(你的权限不够！)", ERROR);
        return;
    }

    char username[20];
    char password[20];
    printf("请依次输入: \n");
    printf("用户名:\n");
    scanf("%s", username);
    printf("密码:\n");
    scanf("%s", password);

    delete_admin_from_file("user.txt", username, password);
}

void handle_quit()
{
    Log("欢迎下次使用！", INFO);
}