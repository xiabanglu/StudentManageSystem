#ifndef SCORE_H
#define SCORE_H

// 暂规定score[11],包含十门学科成绩，第十一位存放总分

#include <stdlib.h>
#include "school.h"
#include "grade.h"
#include "class.h"
#include "student.h"

// 计算总分
int getSum(Student *student)
{
    int sum = 0;
    for (int i = 0; i < 10; i++)
    {
        sum += student->score[i];
    }
    return sum;
}

#endif // SCORE_H
