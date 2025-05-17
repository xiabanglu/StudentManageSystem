#pragma once

#include "student.h"
#include "class.h"
#include "school.h"

// 加载学生信息
void loadStudentFromFile(School *school, const char *filename)
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
        int id;         // 学生ID
        char name[50];  // 学生姓名
        int age;        // 学生年龄
        float score[7]; // 学生成绩数组

        // 从读取的行中解析出学生信息
        sscanf(line, "%d %s %d %f %f %f %f %f %f %f", &id, name, &age, &score[0], &score[1], &score[2], &score[3], &score[4], &score[5], &score[6]);
        registerStudent(school, id, name, age, score); // 注册学生信息
    }

    fclose(file); // 关闭文件
}