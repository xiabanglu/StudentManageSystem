#ifndef __SEARCH_H__
#define __SEARCH_H__

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define _MAX_STUDENT_NUM_ 60
#define _MAX_CLASS_NUM_ 20
#define _MAX_GRADE_NUM_ 4

typedef struct Student
{
    int id;
    int age;
    int class_id;
    int grade_id;

    float score[7];
    char *name;
} Student;

typedef struct Class_
{
    Student **Students;

    int size;
    int Capacity;
    int grade_id;
    int class_id;
} Class_;

typedef struct Grade
{
    Class_ **Classes;

    int size;
    int grade_id;
} Grade;

typedef struct School
{
    Grade **Grades;

    int size;
    const char *name;
} School;

typedef struct student_indices
{
    int student_id;
    int class_id;
    int grade_id;
} student_indices;

student_indices CompileId(int id)
{
    //* 示例: id = 2024010101
    int student_id = id % 100;
    id /= 100;
    int class_id = id % 100;
    id /= 100;
    int grade_id = id % 100;

    student_indices i;
    i.class_id = class_id;
    i.student_id = student_id;
    i.grade_id = grade_id;

    return i;
}

School *createSchool(const char *name, int grade_count)
{
    School *school = (School *)malloc(sizeof(School));
    school->size = grade_count;
    school->name = name;

    school->Grades = (Grade **)malloc(sizeof(Grade *));
    for (int i = 0; i < grade_count; i++)
    {
        school->Grades[i] = (Grade *)malloc(sizeof(Grade));
        school->Grades[i]->grade_id = i + 1;
    }

    return school;
}

void initGrade(Grade **grade, int class_count)
{
    (*grade)->Classes = (Class_ **)malloc(sizeof(Class_ *) * class_count);
    (*grade)->size = class_count;

    for (int i = 0; i < class_count; i++)
    {
        (*grade)->Classes[i] = (Class_ *)malloc(sizeof(Class_));
        (*grade)->Classes[i]->class_id = i + 1;
        (*grade)->Classes[i]->grade_id = (*grade)->grade_id;
    }
}

void initClass(Class_ **class_, int student_count)
{
    (*class_)->Students = (Student **)malloc(sizeof(Student *) * student_count);
    (*class_)->size = student_count;
    (*class_)->Capacity = student_count;

    for (int i = 0; i < student_count; i++)
    {
        (*class_)->Students[i] = (Student *)malloc(sizeof(Student));
        (*class_)->Students[i]->class_id = (*class_)->class_id;
        (*class_)->Students[i]->grade_id = (*class_)->grade_id;
        (*class_)->Students[i]->id = (*class_)->grade_id * 10000 + (*class_)->class_id * 100 + i + 1;
    }
}

Grade **getGrade(School *school, int grade_id)
{
    for (int i = 0; i < school->size; i++)
    {
        if (school->Grades[i]->grade_id == grade_id)
        {
            return &school->Grades[i];
        }
    }

    return NULL;
}

Class_ **getClass(Grade *grade, int class_id)
{
    for (int i = 0; i < grade->size; i++)
    {
        if (grade->Classes[i]->class_id == class_id)
        {
            return &grade->Classes[i];
        }
    }

    return NULL;
}

Student **getStudent(School *school, int id)
{
    student_indices indices = CompileId(id);

    Grade **grade = getGrade(school, indices.grade_id);

    if (grade == NULL)
    {
        printf("id is error: grade error!\n");
        return NULL;
    }

    Class_ **class_ = getClass(*grade, indices.class_id);
    if (class_ == NULL)
    {
        printf("id is error: class is error\n");
        return NULL;
    }

    if (indices.student_id > (*class_)->size)
    {
        printf("id is error: student is error\n");
        return NULL;
    }
    else
    {
        return &(*class_)->Students[indices.student_id - 1];
    }

    return NULL;
}

void recoding_score_class(Class_ *class_, float *score[7])
{
    for (int i = 0; i < class_->size; i++)
    {
        for (int i = 0; i < 7; i++)
        {
            class_->Students[i]->score[i] = score[i][i];
        }
    }
}

void change_score_student(School *school, int id, float score[7])
{
    Student **student = getStudent(school, id);
    for (int i = 0; i < 7; i++)
    {
        (*student)->score[i] = score[i];
    }
}

void registerStudent(School *school, int id, char *name, int age, float score[7])
{

    student_indices ind = CompileId(id);
    Grade **grade = getGrade(school, ind.grade_id);
    Class_ **class_ = getClass(*grade, ind.class_id);

    (*class_)->Students[ind.student_id - 1]->name = (char *)malloc(sizeof(char) * strlen(name));
    strcpy((*class_)->Students[ind.student_id - 1]->name, name);
    (*class_)->Students[ind.student_id - 1]->age = age;
    (*class_)->Students[ind.student_id - 1]->id = id;
    (*class_)->Students[ind.student_id - 1]->class_id = ind.class_id;
    (*class_)->Students[ind.student_id - 1]->grade_id = ind.grade_id;

    for (int i = 0; i < 7; i++)
    {
        (*class_)->Students[ind.student_id - 1]->score[i] = score[i];
    }
}

void DeleteStudent(Student *student)
{
    if (student)
    {
        free(student);
    }
}

void DeleteClass(Class_ *class_)
{
    if (class_)
    {
        if (class_->Students)
        {
            for (int i = 0; i < class_->size; i++)
            {
                DeleteStudent(class_->Students[i]);
            }
            free(class_->Students);
        }
        free(class_);
    }
}

void DeleteGrade(Grade *grade)
{
    if (grade)
    {
        if (grade->Classes)
        {
            for (int i = 0; i < grade->size; i++)
            {
                DeleteClass(grade->Classes[i]);
            }
            free(grade->Classes);
        }
        free(grade);
    }
}

void DeleteSchool(School *school)
{
    if (school)
    {
        if (school->Grades)
        {
            for (int i = 0; i < school->size; i++)
            {
                DeleteGrade(school->Grades[i]);
            }
            free(school->Grades);
        }
        free(school);
    }
}

#endif //__SEARCH_H__