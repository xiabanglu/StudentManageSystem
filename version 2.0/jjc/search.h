#ifndef __SEARCH_H__
#define __SEARCH_H__

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define _MAX_STUDENT_NUM_ 60 // 最大学生数量
#define _MAX_CLASS_NUM_ 20 // 最大班级数量
#define _MAX_GRADE_NUM_ 4 // 最大年级数量

// 学生结构体
typedef struct Student
{
    int id; // 学生ID
    int age; // 学生年龄
    int class_id; // 班级ID
    int grade_id; // 年级ID

    float score[7]; // 学生成绩数组
    char *name; // 学生姓名
} Student;

// 班级结构体
typedef struct Class_
{
    Student **Students; // 学生指针数组
    int size; // 班级中学生数量
    int Capacity; // 班级容量
    int grade_id; // 年级ID
    int class_id; // 班级ID
} Class_;

// 年级结构体
typedef struct Grade
{
    Class_ **Classes; // 班级指针数组
    int size; // 年级中班级数量
    int grade_id; // 年级ID
} Grade;

// 学校结构体
typedef struct School
{
    Grade **Grades; // 年级指针数组
    int size; // 学校中年级数量
    const char *name; // 学校名称
} School;

// 学生索引结构体
typedef struct student_indices
{
    int student_id; // 学生ID
    int class_id; // 班级ID
    int grade_id; // 年级ID
} student_indices;

// 编译ID的函数
student_indices CompileId(int id)
{
    //* 示例: id = 2024010101
    int student_id = id % 100; // 获取学生ID
    id /= 100;
    int class_id = id % 100; // 获取班级ID
    id /= 100;
    int grade_id = id % 100; // 获取年级ID

    student_indices i; // 创建学生索引结构体
    i.class_id = class_id; // 设置班级ID
    i.student_id = student_id; // 设置学生ID
    i.grade_id = grade_id; // 设置年级ID

    return i; // 返回学生索引
}

// 创建学校的函数
School *createSchool(const char *name, int grade_count)
{
    School *school = (School *)malloc(sizeof(School)); // 分配学校内存
    school->size = grade_count; // 设置年级数量
    school->name = name; // 设置学校名称

    school->Grades = (Grade **)malloc(sizeof(Grade *) * grade_count); // 分配年级指针数组内存
    for (int i = 0; i < grade_count; i++)
    {
        school->Grades[i] = (Grade *)malloc(sizeof(Grade)); // 为每个年级分配内存
        school->Grades[i]->grade_id = i + 1; // 设置年级ID
    }

    return school; // 返回学校实例
}

// 初始化年级的函数
void initGrade(Grade **grade, int class_count)
{
    (*grade)->Classes = (Class_ **)malloc(sizeof(Class_ *) * class_count); // 分配班级指针数组内存
    (*grade)->size = class_count; // 设置班级数量

    for (int i = 0; i < class_count; i++)
    {
        (*grade)->Classes[i] = (Class_ *)malloc(sizeof(Class_)); // 为每个班级分配内存
        (*grade)->Classes[i]->class_id = i + 1; // 设置班级ID
        (*grade)->Classes[i]->grade_id = (*grade)->grade_id; // 设置年级ID
    }
}

// 初始化班级的函数
void initClass(Class_ **class_, int student_count)
{
    (*class_)->Students = (Student **)malloc(sizeof(Student *) * student_count); // 分配学生指针数组内存
    (*class_)->size = student_count; // 设置学生数量
    (*class_)->Capacity = student_count; // 设置班级容量

    for (int i = 0; i < student_count; i++)
    {
        (*class_)->Students[i] = (Student *)malloc(sizeof(Student)); // 为每个学生分配内存
        (*class_)->Students[i]->class_id = (*class_)->class_id; // 设置班级ID
        (*class_)->Students[i]->grade_id = (*class_)->grade_id; // 设置年级ID
        (*class_)->Students[i]->id = (*class_)->grade_id * 10000 + (*class_)->class_id * 100 + i + 1; // 计算学生ID
    }
}

// 获取年级的函数
Grade **getGrade(School *school, int grade_id)
{
    for (int i = 0; i < school->size; i++)
    {
        if (school->Grades[i]->grade_id == grade_id) // 查找匹配的年级ID
        {
            return &school->Grades[i]; // 返回年级指针
        }
    }

    return NULL; // 未找到年级
}

// 获取班级的函数
Class_ **getClass(Grade *grade, int class_id)
{
    for (int i = 0; i < grade->size; i++)
    {
        if (grade->Classes[i]->class_id == class_id) // 查找匹配的班级ID
        {
            return &grade->Classes[i]; // 返回班级指针
        }
    }

    return NULL; // 未找到班级
}

// 获取学生的函数
Student **getStudent(School *school, int id)
{
    student_indices indices = CompileId(id); // 编译ID获取学生索引

    Grade **grade = getGrade(school, indices.grade_id); // 获取年级

    if (grade == NULL)
    {
        printf("id is error: grade error!\n"); // 年级错误提示
        return NULL;
    }

    Class_ **class_ = getClass(*grade, indices.class_id); // 获取班级
    if (class_ == NULL)
    {
        printf("id is error: class is error\n"); // 班级错误提示
        return NULL;
    }

    if (indices.student_id > (*class_)->size) // 检查学生ID是否有效
    {
        printf("id is error: student is error\n"); // 学生错误提示
        return NULL;
    }
    else
    {
        return &(*class_)->Students[indices.student_id - 1]; // 返回学生指针
    }

    return NULL; // 默认返回NULL
}

// 记录班级成绩的函数
void recoding_score_class(Class_ *class_, float *score[7])
{
    for (int i = 0; i < class_->size; i++)
    {
        for (int i = 0; i < 7; i++)
        {
            class_->Students[i]->score[i] = score[i][i]; // 记录成绩
        }
    }
}

// 修改学生成绩的函数
void change_score_student(School *school, int id, float score[7])
{
    Student **student = getStudent(school, id); // 获取学生
    for (int i = 0; i < 7; i++)
    {
        (*student)->score[i] = score[i]; // 更新成绩
    }
}

// 注册学生的函数
void registerStudent(School *school, int id, char *name, int age, float score[7])
{
    student_indices ind = CompileId(id); // 编译ID获取学生索引
    Grade **grade = getGrade(school, ind.grade_id); // 获取年级
    Class_ **class_ = getClass(*grade, ind.class_id); // 获取班级

    (*class_)->Students[ind.student_id - 1]->name = (char *)malloc(sizeof(char) * strlen(name)); // 为学生姓名分配内存
    strcpy((*class_)->Students[ind.student_id - 1]->name, name); // 复制学生姓名
    (*class_)->Students[ind.student_id - 1]->age = age; // 设置学生年龄
    (*class_)->Students[ind.student_id - 1]->id = id; // 设置学生ID
    (*class_)->Students[ind.student_id - 1]->class_id = ind.class_id; // 设置班级ID
    (*class_)->Students[ind.student_id - 1]->grade_id = ind.grade_id; // 设置年级ID

    for (int i = 0; i < 7; i++)
    {
        (*class_)->Students[ind.student_id - 1]->score[i] = score[i]; // 设置学生成绩
    }
}

// 删除学生的函数
void DeleteStudent(Student *student)
{
    if (student)
    {
        free(student); // 释放学生内存
    }
}

// 删除班级的函数
void DeleteClass(Class_ *class_)
{
    if (class_)
    {
        if (class_->Students)
        {
            for (int i = 0; i < class_->size; i++)
            {
                DeleteStudent(class_->Students[i]); // 删除每个学生
            }
            free(class_->Students); // 释放学生指针数组内存
        }
        free(class_); // 释放班级内存
    }
}

// 删除年级的函数
void DeleteGrade(Grade *grade)
{
    if (grade)
    {
        if (grade->Classes)
        {
            for (int i = 0; i < grade->size; i++)
            {
                DeleteClass(grade->Classes[i]); // 删除每个班级
            }
            free(grade->Classes); // 释放班级指针数组内存
        }
        free(grade); // 释放年级内存
    }
}

// 删除学校的函数
void DeleteSchool(School *school)
{
    if (school)
    {
        if (school->Grades)
        {
            for (int i = 0; i < school->size; i++)
            {
                DeleteGrade(school->Grades[i]); // 删除每个年级
            }
            free(school->Grades); // 释放年级指针数组内存
        }
        free(school); // 释放学校内存
    }
}

#endif //__SEARCH_H__