#include <stdlib.h>
#include "school.h"
#include "grade.h"
#include "class.h"
#include "student.h"

// 初始化班级
void initClass(Class **class, int studentCount)
{
    (*class)->students = (Student **)malloc(sizeof(Student *) * studentCount);
    (*class)->size = studentCount;
    (*class)->capacity = studentCount;

    for (int i = 0; i < studentCount; i++)
    {
        (*class)->students[i] = (Student *)malloc(sizeof(Student));
        (*class)->students[i]->indices.classId = (*class)->classId;
        (*class)->students[i]->indices.gradeId = (*class)->gradeId;
        (*class)->students[i]->indices.id = (*class)->gradeId * 10000 + (*class)->classId * 100 + i + 1;
    }
}

// 获取班级
Class **getClass(Grade *grade, int classId)
{
    for (int i = 0; i < grade->size; i++)
    {
        if (grade->classes[i]->classId == classId)
        {
            return &grade->classes[i];
        }
    }

    return NULL;
}

// 删除班级
void DeleteClass(Class *class)
{
    if (class)
    {
        if (class->students)
        {
            for (int i = 0; i < class->size; i++)
            {
                DeleteStudent(class->students[i]);
            }
            free(class->students);
        }
        free(class);
    }
}