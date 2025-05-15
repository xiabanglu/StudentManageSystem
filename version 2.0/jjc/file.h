#pragma once

#include "search.h"

void CompileFile(School *school, const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Error opening file\n");
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), file))
    {
        int id;
        char name[50];
        int age;
        float score[7];

        sscanf(line, "%d %s %d %f %f %f %f %f %f %f", &id, name, &age, &score[0], &score[1], &score[2], &score[3], &score[4], &score[5], &score[6]);
        registerStudent(school, id, name, age, score);
    }

    fclose(file);
}