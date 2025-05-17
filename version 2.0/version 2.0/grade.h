#ifndef GRADE_H
#define GRADE_H

#include <stdlib.h>
#include "school.h"
#include "grade.h"
#include "class.h"
#include "student.h"

// 学校最大年级数量
#define _MAX_GRADE_NUM_PER_SCHOOL_ 4

// 年级结构体
typedef struct Grade
{
    Class **classes; // 班级指针数组
    int size;        // 年级中班级数量
    int schoolName;  // 学校
    int gradeId;     // 年级ID
} Grade;

// 初始化年级
void initGrade(Grade **grade, int classCount)
{
    (*grade)->classes = (Class **)malloc(sizeof(Class *) * classCount);
    (*grade)->size = classCount;

    for (int i = 0; i < classCount; i++)
    {
        (*grade)->classes[i] = (Class *)malloc(sizeof(Class));
        (*grade)->classes[i]->classId = i + 1;
        (*grade)->classes[i]->gradeId = (*grade)->gradeId;
    }
}

// 获取年级
Grade **getGrade(School *school, int gradeId)
{
    for (int i = 0; i < school->size; i++)
    {
        if (school->grades[i]->gradeId == gradeId)
        {
            return &school->grades[i];
        }
    }

    return NULL;
}

// 删除年级
void DeleteGrade(Grade *grade)
{
    if (grade)
    {
        if (grade->classes)
        {
            for (int i = 0; i < grade->size; i++)
            {
                DeleteClass(grade->classes[i]);
            }
            free(grade->classes);
        }
        free(grade);
    }
}

#endif // GRADE_H