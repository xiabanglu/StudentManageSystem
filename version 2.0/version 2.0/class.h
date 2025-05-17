#ifndef CLASS_H
#define CLASS_H

#include <stdlib.h>
#include "school.h"
#include "grade.h"
#include "class.h"
#include "student.h"

// 年级最大班级数量
#define _MAX_CLASS_NUM_PER_GRADE_ 20

// 班级结构体
typedef struct Class
{
    Student **students; // 学生指针数组
    int size;           // 班级学生数量
    int capacity;       // 班级最大容量
    int schoolName;     // 学校
    int gradeId;        // 年级ID
    int classId;        // 班级ID
} Class;

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

#endif // CLASS_H