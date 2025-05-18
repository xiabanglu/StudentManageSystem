#ifndef FILE_H
#define FILE_H

#include <string.h>
#include <stdio.h>

#include "search.h"

// 程序入口初始化信息
// loadStudentFromFile(){}

// 保存注册user信息
void save_register_user_to_file(const char *file_path, char *username, const char *password)
{
    FILE *file = fopen(file_path, "a");
    if (file == NULL)
    {
        printf("Error opening file\n");
        return;
    }

    fprintf(file, "%s %s 1\n", username, password);
    printf("User registered successfully!\n");
    fclose(file);
}

// 删除user信息
void delete_user_from_file(const char *file_path, char *username, char *password)
{
    FILE *file = fopen(file_path, "r");
    if (file == NULL)
    {
        printf("Error opening file\n");
        return;
    }

    FILE *temp_file = fopen("temp.txt", "w");
    if (temp_file == NULL)
    {
        printf("Error opening temporary file\n");
        fclose(file);
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), file))
    {
        char file_username[50];
        char file_password[50];
        sscanf(line, "%s %s", file_username, file_password);
        if (strcmp(file_username, username) != 0 && strcmp(file_password, password) != 0)
        {
            fputs(line, temp_file);
        }
    }

    fclose(file);
    fclose(temp_file);

    remove(file_path);
    rename("temp.txt", file_path);
    printf("User deleted successfully!\n");
}

// 保存注册admin信息
// void save_register_admin_to_file(const char *file_path, char *username, const char *password)

// 删除admin信息
// void delete_admin_from_file(const char *file_path, char *username, char *password)

// 保存学生信息
// void save_register_student_to_file(const char *file_path, int id, Student *newStudent, double *score)
// {
//     FILE *file = fopen(file_path, "a");
//     if (file == NULL)
//     {
//         printf("Error opening file\n");
//         return;
//     }

//     fprintf(file, "%d %s %s %d %s %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf\n",
//             id, newStudent->info.name, newStudent->info.gender, newStudent->info.age, newStudent->info.schoolName,
//             score[0], score[1], score[2], score[3], score[4], score[5],
//             score[6], score[7], score[8], score[9]);

//     printf("Student registered successfully!\n");
//     fclose(file);
// }

// 删去文件中某条学生数据
// void delete_student_from_file(){}

// 更新文件中某条学生数据
// void update_student_from_file(){}

#endif // FILE_H