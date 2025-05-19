#include "event.h"
#include "login.h"
#include "file.h"

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
        Log("用户文件损坏或不存在!", ERROR);
        rank = 0;
        return;
    }

    if (rank == 0)
    {
        Log("用户名或密码错误!", ERROR);
        return;
    }

    // 成功登录提示
    char success_msg[50];
    sprintf(success_msg, "%s 登录成功，权限等级: %d",
            (rank == 1) ? "用户" : (rank == 2) ? "管理员"
                                               : "开发者",
            rank);
    Log(success_msg, INFO);
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
    // 功能菜单退出时自动重置rank
    if (rank > 0)
    {
        Log("正在返回登录界面...", INFO);
        rank = 0; // 重置权限等级
    }
}