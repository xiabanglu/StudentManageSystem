#include <stdlib.h>
#include "school.h"
#include "grade.h"
#include "class.h"
#include "student.h"

// 记录班级成绩的函数
void recoding_score_class(Class *class, float *score[7])
{
    for (int i = 0; i < class->size; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            ((int*)(&class->students[i]->score))[j];
        }
    }
}

// 修改学生成绩的函数
void change_score_student(School *school, int id, float score[7])
{
    Student **student = getStudent(school, id);
    for (int i = 0; i < 7; i++)
    {
        (*student)->score[i] = score[i];
    }
}