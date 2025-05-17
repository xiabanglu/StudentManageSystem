#pragma once

#include <string.h>
#include <stdio.h>

// 用户登录函数
int login(const char *file_path, const int id, char *password)
{
    FILE *file = fopen(file_path, "r"); // 打开用户文件进行读取
    if (file == NULL)
    {
        printf("Error opening file\n"); // 如果文件打开失败，打印错误信息
        return -1;                      // 返回错误代码
    }

    char line[256];                         // 用于存储每一行的内容
    while (fgets(line, sizeof(line), file)) // 逐行读取文件内容
    {
        int file_id, flag;                                         // 文件中的用户ID和标志
        char file_password[50];                                    // 文件中的用户密码
        sscanf(line, "%d %d %s", &file_id, &flag, file_password);  // 解析用户信息
        if (file_id == id && strcmp(file_password, password) == 0) // 检查ID和密码是否匹配
        {
            fclose(file); // 关闭文件
            return flag;  // 返回用户标志
        }
    }

    fclose(file); // 关闭文件
    return 0;     // 返回未找到用户
}

// 注册用户的函数
void register_user(const char *file_path, const int id, const char *password)
{
    FILE *file = fopen(file_path, "a"); // 以追加模式打开用户文件
    if (file == NULL)
    {
        printf("Error opening file\n"); // 如果文件打开失败，打印错误信息
        return;
    }

    fprintf(file, "%d 1 %s\n", id, password);  // 将用户ID和密码写入文件
    printf("User registered successfully!\n"); // 打印注册成功信息
    fclose(file);                              // 关闭文件
}

// 删除用户的函数
void delete_user(const char *file_path, const int id)

{
    FILE *file = fopen(file_path, "r"); // 打开用户文件进行读取
    if (file == NULL)
    {
        printf("Error opening file\n"); // 如果文件打开失败，打印错误信息
        return;
    }

    FILE *temp_file = fopen("temp.txt", "w"); // 创建临时文件用于存储未删除的用户
    if (temp_file == NULL)
    {
        printf("Error opening temporary file\n"); // 如果临时文件打开失败，打印错误信息
        fclose(file);                             // 关闭原文件
        return;
    }

    char line[256];                         // 用于存储每一行的内容
    while (fgets(line, sizeof(line), file)) // 逐行读取文件内容
    {
        int file_id;                  // 文件中的用户ID
        sscanf(line, "%d", &file_id); // 解析用户ID
        if (file_id != id)            // 如果ID不匹配，则写入临时文件
        {
            fputs(line, temp_file);
        }
    }

    fclose(file);      // 关闭原文件
    fclose(temp_file); // 关闭临时文件

    remove(file_path);                      // 删除原文件
    rename("temp.txt", file_path);          // 将临时文件重命名为原文件名
    printf("User deleted successfully!\n"); // 打印删除成功信息
}