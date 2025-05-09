#include "student.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "errorcode.h"

#define _CRT_SECURE_NO_WARNINGS

// 学生数组初始化
Student students[STUDENTMAXNUM];

// 计算学生数量
int countStudentNum()
{
    int count = 0;
    while (students[count].id != -1 && count < STUDENTMAXNUM)
        count++;
    return count;
}

// 从文件中加载学生信息
int loadStudentFromFile()
{

    FILE *file;
    const char *fileName = "studentInfo.txt";
    const char *mode = "r";

    int error = fopen_s(&file, fileName, mode);
    // 文件读写错误
    if (error != 0)
    {
        printf("failed to open file: %s\n", fileName);
        // 标准错误码
        return FILE_IS_NULL_CODE;
    }

    int count = 0;
    char buffer[2025];
    while (count < STUDENTMAXNUM && fgets(buffer, 2025, file))
    {
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n')
            buffer[--len] = '\0';
        if (len > 0 && buffer[len - 1] == '\r')
            buffer[--len] = '\0';

        // 加载学生信息
        if (sscanf_s(buffer,
                     "%d,%19[^,],%19[^,],%19[^,],%19[^,],%19[^,],%19[^,],%19[^,],%19[^,],"
                     "%f,%f,%f,%f,%f,%f,%f,%f,%f,%f",
                     &students[count].id,
                     students[count].account.username, (unsigned)_countof(students[count].account.username),
                     students[count].account.password, (unsigned)_countof(students[count].account.password),
                     students[count].info.name, (unsigned)_countof(students[count].info.name),
                     students[count].info.gender, (unsigned)_countof(students[count].info.gender),
                     students[count].info.age, (unsigned)_countof(students[count].info.age),
                     students[count].info.grade, (unsigned)_countof(students[count].info.grade),
                     students[count].info.classNum, (unsigned)_countof(students[count].info.classNum),
                     students[count].info.stuNum, (unsigned)_countof(students[count].info.stuNum),
                     &students[count].score.advancedMath,
                     &students[count].score.linearAlgebra,
                     &students[count].score.programming,
                     &students[count].score.probability,
                     &students[count].score.discreteMath,
                     &students[count].score.database,
                     &students[count].score.computerNetwork,
                     &students[count].score.operatingSystem,
                     &students[count].score.computerOrganization,
                     &students[count].score.dataStructureAndAlgorithm) == 19)
        {
            count++;
        }
    }

    fclose(file);
    return SUCCESS_LOAD_STUDENT_CODE;
}

// 保存学生信息到文件
int saveStudentToFile()
{

    FILE *file;
    int count = countStudentNum();
    const char *fileName = "studentInfo.txt";
    const char *mode = "w";

    int error = fopen_s(&file, fileName, mode);
    // 文件读写错误
    if (error != 0)
    {
        printf("failed to open file: %s\n", fileName);
        // 标准错误码
        return FILE_IS_NULL_CODE;
    }

    for (int i = 0; i < count; i++)
    {
        fprintf(file, "%d,%s,%s,%s,%s,%s,%s,%s,%s,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f\n",
                students[i].id,
                students[i].account.username,
                students[i].account.password,
                students[i].info.name,
                students[i].info.gender,
                students[i].info.age,
                students[i].info.grade,
                students[i].info.classNum,
                students[i].info.stuNum,
                students[i].score.advancedMath,
                students[i].score.linearAlgebra,
                students[i].score.programming,
                students[i].score.probability,
                students[i].score.discreteMath,
                students[i].score.database,
                students[i].score.computerNetwork,
                students[i].score.operatingSystem,
                students[i].score.computerOrganization,
                students[i].score.dataStructureAndAlgorithm);
    }

    fclose(file);
    return SUCCESS_SAVE_STUDENT_CODE;
}
