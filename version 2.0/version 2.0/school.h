#ifndef SCHOOL_H
#define SCHOOL_H

#include <stdlib.h>
#include "school.h"
#include "grade.h"
#include "class.h"
#include "student.h"

// 学校结构体
typedef struct School
{
    Grade **grades;         // 年级指针数组
    int size;               // 学校年级数量
    const char *schoolName; // 学校名称
} School;

// 创建学校
School *createSchool(const char *schoolName, int gradeCount)
{
    School *school = (School *)malloc(sizeof(School));
    school->size = gradeCount;
    school->schoolName = schoolName;

    school->grades = (Grade **)malloc(sizeof(Grade *) * gradeCount);
    for (int i = 0; i < gradeCount; i++)
    {
        school->grades[i] = (Grade *)malloc(sizeof(Grade));
        school->grades[i]->gradeId = i + 1;
    }

    return school;
}

// 删除学校
void DeleteSchool(School *school)
{
    if (school)
    {
        if (school->grades)
        {
            for (int i = 0; i < school->size; i++)
            {
                DeleteGrade(school->grades[i]);
            }
            free(school->grades);
        }
        free(school);
    }
}

#endif // SCHOOL_H