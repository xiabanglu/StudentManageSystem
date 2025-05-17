#ifndef FILE_H
#define FILE_H

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

    fclose(file); // 关闭文件
}

#endif // FILE_H