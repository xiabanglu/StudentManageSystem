#ifndef LOGIN_H
#define LOGIN_H

#include <string.h>
#include <stdio.h>

// 登录验证
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
        char file_username[50];
        char file_password[50];
        sscanf(line, "%s %s %d", file_username, file_password, &flag);
        if (strcmp(file_username, username) == 0 && strcmp(file_password, password) == 0)
        {
            fclose(file);
            return flag;
        }
    }

    fclose(file);
    return 0;
}

#endif // LOGIN_H