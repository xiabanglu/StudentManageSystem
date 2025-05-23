#include "event.h"
#include "login.h"
#include "file.h"

void handle_login()
{
    char username[20];
    char password[20];
    printf(INPUT_PROMPT COLOR_YELLOW "Please enter as required(请按要求输入):\n\n" COLOR_RESET);
    printf(INPUT_PROMPT COLOR_YELLOW "username(用户名):\n" COLOR_RESET);
    printf(INPUT_PROMPT);
    scanf("%s", username);
    printf(INPUT_PROMPT COLOR_YELLOW "password(密码):\n" COLOR_RESET);
    printf(INPUT_PROMPT);
    scanf("%s", password);
    printf(HEADER_LINE "\n");

    rank = login("account.txt", username, password);

    if (rank == -1)
    {
        Log("no account.txt", ERROR);
        rank = 0;
        return;
    }

    if (rank == 0)
    {
        Log("Wrong username or password(用户名或密码错误)!", ERROR);
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
    printf(INPUT_PROMPT COLOR_YELLOW "Please enter as required(请按要求输入):\n\n" COLOR_RESET);
    printf(INPUT_PROMPT COLOR_YELLOW "username(用户名):\n" COLOR_RESET);
    printf(INPUT_PROMPT);
    scanf("%s", username);
    printf(INPUT_PROMPT COLOR_YELLOW "password(密码):\n" COLOR_RESET);
    printf(INPUT_PROMPT);
    scanf("%s", password);
    printf(HEADER_LINE "\n");

    save_user_to_file("account.txt", username, password);
}

void handle_insert_record()
{
    if (rank != 2 && rank != 3)
    {
        Log("Your authority is insufficient(你的权限不够)!", ERROR);
        return;
    }

    int id;
    Student *newStudent = (Student *)malloc(sizeof(Student));
    double score[10];

    if (newStudent == NULL)
    {
        Log("Memory allocation failure(内存分配失败)!", ERROR);
        return;
    }

    printf(INPUT_PROMPT COLOR_YELLOW "Please enter as required(请按格式输入):\n\n" COLOR_RESET);
    printf(INPUT_PROMPT COLOR_YELLOW "ID 姓名 性别 年龄 所属学校: \n" COLOR_RESET);
    printf(INPUT_PROMPT);
    scanf("%d %s %s %d %s",
          &id, newStudent->info.name, newStudent->info.gender,
          &newStudent->info.age, newStudent->info.schoolName);

    printf(INPUT_PROMPT COLOR_YELLOW "请依次录入十次成绩(空格间隔每门成绩): \n" COLOR_RESET);
    printf(INPUT_PROMPT);
    scanf("%lf %lf %lf %lf %lf %lf %lf %lf %lf %lf", &score[0], &score[1], &score[2],
          &score[3], &score[4], &score[5], &score[6], &score[7], &score[8], &score[9]);
    printf(HEADER_LINE "\n");

    registerStudent(school, id, newStudent, score);

    free(newStudent);
}

void handle_delete_record()
{
    if (rank != 2 && rank != 3)
    {
        Log("Your authority is insufficient(你的权限不够)!", ERROR);
        return;
    }

    int id;
    printf(INPUT_PROMPT COLOR_YELLOW "Please enter id(请输入ID): \n" COLOR_RESET);
    printf(INPUT_PROMPT);
    scanf("%d", &id);
    printf(HEADER_LINE "\n");

    deleteStudent(school, id);
}

void handle_update_record()
{
    if (rank != 2 && rank != 3)
    {
        Log("Your authority is insufficient(你的权限不够)!", ERROR);
        return;
    }

    int id;
    Student *newStudent = (Student *)malloc(sizeof(Student));
    double score[10];

    if (newStudent == NULL)
    {
        Log("Memory allocation failure(内存分配失败)!", ERROR);
        return;
    }

    printf(INPUT_PROMPT COLOR_YELLOW "Please enter as required(请按格式输入):\n\n" COLOR_RESET);
    printf(INPUT_PROMPT COLOR_YELLOW "ID 姓名 性别 年龄 所属学校: \n" COLOR_RESET);
    printf(INPUT_PROMPT);
    scanf("%d %s %s %d %s",
          &id, newStudent->info.name, newStudent->info.gender,
          &newStudent->info.age, newStudent->info.schoolName);

    printf(INPUT_PROMPT COLOR_YELLOW "请依次录入十次成绩(空格间隔每门成绩): \n" COLOR_RESET);
    printf(INPUT_PROMPT);
    scanf("%lf %lf %lf %lf %lf %lf %lf %lf %lf %lf", &score[0], &score[1], &score[2],
          &score[3], &score[4], &score[5], &score[6], &score[7], &score[8], &score[9]);
    printf(HEADER_LINE "\n");

    updateStudent(school, id, newStudent, score);
    free(newStudent);
}

void handle_show_record()
{
    if (rank != 1 && rank != 2 && rank != 3)
    {
        Log("Your authority is insufficient(你的权限不够)!", ERROR);
        return;
    }

    int id;
    printf(INPUT_PROMPT COLOR_YELLOW "Please enter id(请输入ID): \n" COLOR_RESET);
    printf(INPUT_PROMPT);
    scanf("%d", &id);
    printf(HEADER_LINE "\n");

    if (id <= 0)
    {
        Log("Invalid id(ID不合法)!", ERROR);
        return;
    }

    Student **student = getStudent(school, id);
    if (student == NULL)
    {
        Log("Student not found(学生未找到)!", ERROR);
        return;
    }
    else
    {
        Log("Student found(该学生信息如下):", INFO);
    }
    printf("姓名: %s 性别: %s 年龄: %d 所属学校: %s\n各科分数:", (*student)->info.name,
           (*student)->info.gender, (*student)->info.age, (*student)->info.schoolName);

    for (int i = 0; i < 10; i++)
    {
        printf("%.2lf ", (*student)->score[i]);
    }
    printf("\n");
}

void handle_show_records()
{
    if (rank != 2 && rank != 3)
    {
        Log("Your authority is insufficient(你的权限不够)!", ERROR);
        return;
    }

    Log("所有学生信息如下:", INFO);
    for (int i = 0; i < school->size; i++)
    {
        for (int j = 0; j < school->grades[i]->size; j++)
        {
            for (int k = 0; k < school->grades[i]->classes[j]->size; k++)
            {
                Student *student = school->grades[i]->classes[j]->students[k];
                // 仅显示有效ID的学生
                if (student != NULL && student->indices.id != 0)
                {
                    printf("ID: %d\t姓名: %s\t性别: %s\t年龄: %d\t所属学校:%s\n",
                           student->indices.id,
                           student->info.name,
                           student->info.gender,
                           student->info.age,
                           student->info.schoolName);
                }
            }
        }
    }
    printf("\n");
}

void handle_score_statistics()
{
    if (rank != 2 && rank != 3)
    {
        Log("Your authority is insufficient(你的权限不够)!", ERROR);
        return;
    }
}

void handle_register_admin()
{
    if (rank != 3)
    {
        Log("Your authority is insufficient(你的权限不够)!", ERROR);
        return;
    }

    char username[20];
    char password[20];
    printf(INPUT_PROMPT COLOR_YELLOW "Please enter as required(请按要求输入):\n\n" COLOR_RESET);
    printf(INPUT_PROMPT COLOR_YELLOW "username(用户名):\n" COLOR_RESET);
    printf(INPUT_PROMPT);
    scanf("%s", username);
    printf(INPUT_PROMPT COLOR_YELLOW "password(密码):\n" COLOR_RESET);
    printf(INPUT_PROMPT);
    scanf("%s", password);
    printf(HEADER_LINE "\n");

    save_admin_to_file("account.txt", username, password);
}

void handle_delete_user()
{
    if (rank != 2 && rank != 3)
    {
        Log("Your authority is insufficient(你的权限不够)!", ERROR);
        return;
    }

    char username[20];
    char password[20];
    printf(INPUT_PROMPT COLOR_YELLOW "Please enter as required(请按要求输入):\n\n" COLOR_RESET);
    printf(INPUT_PROMPT COLOR_YELLOW "username(用户名):\n" COLOR_RESET);
    printf(INPUT_PROMPT);
    scanf("%s", username);
    printf(INPUT_PROMPT COLOR_YELLOW "password(密码):\n" COLOR_RESET);
    printf(INPUT_PROMPT);
    scanf("%s", password);
    printf(HEADER_LINE "\n");

    int delrank = login("account.txt", username, password);
    if (delrank < 2)
    {
        delete_user_from_file("account.txt", username, password);
    }
    else
    {
        Log("Your can only delete user(你只能删除user)!", ERROR);
        return;
    }
}

void handle_delete_admin()
{
    if (rank != 3)
    {
        Log("Your authority is insufficient(你的权限不够)!", ERROR);
        return;
    }

    char username[20];
    char password[20];
    printf(INPUT_PROMPT COLOR_YELLOW "Please enter as required(请按要求输入):\n\n" COLOR_RESET);
    printf(INPUT_PROMPT COLOR_YELLOW "username(用户名):\n" COLOR_RESET);
    printf(INPUT_PROMPT);
    scanf("%s", username);
    printf(INPUT_PROMPT COLOR_YELLOW "password(密码):\n" COLOR_RESET);
    printf(INPUT_PROMPT);
    scanf("%s", password);
    printf(HEADER_LINE "\n");

    int delrank = login("account.txt", username, password);
    if (delrank < 3)
    {
        delete_admin_from_file("account.txt", username, password);
    }
    else
    {
        Log("Your can't delete developer(你不能删除developer)!", ERROR);
        return;
    }
}

void handle_quit()
{
    // 功能菜单退出时自动重置rank
    if (rank > 0)
    {
        rank = 0; // 重置权限等级
    }
}

void handle_sum_avg_per_student()
{
}

void handle_avg_per_class()
{
}

void handle_avg_per_grade()
{
}

void handle_ranking_list()
{
}