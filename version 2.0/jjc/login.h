#pragma once

#include <string.h>
#include <stdio.h>

int login(const char *file_path, const int id, char *password)
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
        int file_id, flag;
        char file_password[50];
        sscanf(line, "%d %d %s", &file_id, &flag, file_password);
        if (file_id == id && strcmp(file_password, password) == 0)
        {
            fclose(file);
            return flag;
        }
    }

    fclose(file);
    return 0;
}

void register_user(const char *file_path, const int id, const char *password)
{
    FILE *file = fopen(file_path, "a");
    if (file == NULL)
    {
        printf("Error opening file\n");
        return;
    }

    fprintf(file, "%d %s\n", id, password);
    printf("User registered successfully!\n");
    fclose(file);
}

void delete_user(const char *file_path, const int id)
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
        int file_id;
        sscanf(line, "%d", &file_id);
        if (file_id != id)
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