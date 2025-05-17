#include <stdlib.h>
#include "school.h"
#include "grade.h"
#include "class.h"
#include "student.h"
#include "score.h"

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