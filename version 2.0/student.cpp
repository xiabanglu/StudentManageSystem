#include "student.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "errorcode.h"

#define _CRT_SECURE_NO_WARNINGS

// 学生数组初始化
Student students[STUDENTMAXNUM] = { { -1 } };

// 计算学生数量
int countStudentNum() {
    int count = 0;
    while (students[count].id != -1 && count < STUDENTMAXNUM) count++;
    return count;
}

// 从文件中加载学生信息
int loadStudentFromFile() {
    // 初始化缓存
    for (int i = 0; i < STUDENTMAXNUM; i++) students[i].id = -1;

    FILE* file;
    const char* fileName = "studentInfo.txt";
    const char* mode = "r";

    int error = fopen_s(&file, fileName, mode);
    // 文件读写错误
    if (error != 0) {
        printf("failed to open file: %s\n", fileName);
        // 标准错误码
        return FILE_IS_NULL_CODE;
    }

    int count = 0;
    char buffer[512];
    while (count < STUDENTMAXNUM && fgets(buffer, 512, file)) {
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') buffer[--len] = '\0';
        if (len > 0 && buffer[len - 1] == '\r') buffer[--len] = '\0';

        // 加载学生信息
        if (sscanf_s(buffer,
            "%d,%19[^,],%19[^,],%19[^,],%19[^,],%19[^,],%19[^,],%19[^,],"
            "%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf",
            &students[count].id,
            students[count].account, (unsigned)_countof(students[count].account),
            students[count].password, (unsigned)_countof(students[count].password),
            students[count].name, (unsigned)_countof(students[count].name),
            students[count].gender, (unsigned)_countof(students[count].gender),
            students[count].age, (unsigned)_countof(students[count].age),
            students[count].grade, (unsigned)_countof(students[count].grade),
            students[count].classNum, (unsigned)_countof(students[count].classNum),
            &students[count].score[0], &students[count].score[1], &students[count].score[2],
            &students[count].score[3], &students[count].score[4], &students[count].score[5],
            &students[count].score[6], &students[count].score[7], &students[count].score[8],
            &students[count].score[9]) == 18) {
            count++;
        }
    }
    if (count < STUDENTMAXNUM) students[count].id = -1;
    fclose(file);

    return SUCCESS_LOAD_STUDENT_CODE;
}

// 保存学生信息到文件
int saveStudentToFile() {
    FILE* file;
    const char* fileName = "studentInfo.txt";
    const char* mode = "w";

    int error = fopen_s(&file, fileName, mode);
    // 文件读写错误
    if (error != 0) {
        printf("failed to open file: %s\n", fileName);
        // 标准错误码
        return FILE_IS_NULL_CODE;
    }
    int count = countStudentNum();

    for (int i = 0; i < count; i++) {
        fprintf(file, "%d,%s,%s,%s,%s,%s,%s,%s",
            students[i].id, students[i].account, students[i].password,
            students[i].name, students[i].gender, students[i].age,
            students[i].grade, students[i].classNum);

        // 写入 score 数组
        for (int j = 0; j < 10; j++) {
            fprintf(file, ",%lf", students[i].score[j]);
        }
        fprintf(file, "\n");
    }
    fclose(file);
    return SUCCESS_SAVE_STUDENT_CODE;
}
