#include <stdlib.h>
#include "school.h"
#include "grade.h"
#include "class.h"
#include "student.h"

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