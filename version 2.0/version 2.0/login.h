#ifndef LOGIN_H
#define LOGIN_H

#include <string.h>
#include <stdio.h>

// 用户登录函数
int login(const char *file_path, char *username, char *password)
{
    FILE *file = fopen(file_path, "r");
    if (file == NULL)
    {
        printf("Error opening file\n");
        return -1;
    }

    char line[256];
    while (fgets(line, sizeof(line), file))
    {
        int flag;
        char file_uesrname[50];
        char file_password[50];
        sscanf(line, "%s %s %d", file_uesrname, file_password, &flag);
        if (strcmp(file_uesrname, username) == 0 && strcmp(file_password, password) == 0)
        {
            fclose(file);
            return flag;
        }
    }

    fclose(file);
    return 0;
}

// 注册用户的函数
void register_user(const char *file_path, char *username, const char *password)
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

// 删除用户的函数
void delete_user(const char *file_path, char *username)
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
        sscanf(line, "%s", file_username);
        if (file_username != username)
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

#endif // LOGIN_H