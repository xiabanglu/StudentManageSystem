#include "score.h"

// 某同学总分
double getStudentSum(Student *student)
{
    int sum = 0;
    for (int i = 0; i < 10; i++)
    {
        sum += student->score[i];
    }
    return sum;
}

// 班级按学生总分排序（降序）
Class *getSortedClassByTotalScore(Class *class)
{
    // 分配新Class结构体
    Class *sortedClass = (Class *)malloc(sizeof(Class));
    sortedClass->classId = class->classId;
    sortedClass->size = class->size;
    sortedClass->students = (Student **)malloc(class->size * sizeof(Student *));
    // 复制学生指针
    for (int i = 0; i < class->size; i++)
    {
        sortedClass->students[i] = class->students[i];
    }
    // 排序（冒泡法）
    for (int i = 0; i < sortedClass->size - 1; i++)
    {
        for (int j = 0; j < sortedClass->size - i - 1; j++)
        {
            Student *stu1 = sortedClass->students[j];
            Student *stu2 = sortedClass->students[j + 1];
            if (stu1 && stu2)
            {
                double sum1 = getStudentSum(stu1);
                double sum2 = getStudentSum(stu2);
                if (sum1 < sum2)
                {
                    Student *temp = sortedClass->students[j];
                    sortedClass->students[j] = sortedClass->students[j + 1];
                    sortedClass->students[j + 1] = temp;
                }
            }
        }
    }
    return sortedClass;
}

// 班级学生某学科的最高分和最低分
void getClassSubjectRange(Class *class, int subjectIdx, double *max, double *min)
{
    *max = -1;
    *min = 101;

    for (int i = 0; i < class->size; i++)
    {
        Student *stu = class->students[i];
        if (stu && stu->indices.id != 0) // 仅处理有效学生
        {
            double score = stu->score[subjectIdx];
            if (score > *max)
                *max = score;
            if (score < *min)
                *min = score;
        }
    }

    // 处理无有效数据的情况
    if (*max == -1)
        *max = 0;
    if (*min == 101)
        *min = 0;
}

// 班级学生总分的最高分和最低分
void getClassTotalRange(Class *class, double *max, double *min)
{
    *max = -1;
    *min = 101;
    for (int i = 0; i < class->size; i++)
    {
        Student *stu = class->students[i];
        if (stu)
        {
            double sum = getStudentSum(stu);
            if (sum > *max)
                *max = sum;
            if (sum < *min)
                *min = sum;
        }
    }
}

// 班级所有学生某学科的平均分
double getClassSubjectAvg(Class *class, int subjectIdx)
{
    double sum = 0;
    int cnt = 0;
    for (int i = 0; i < class->size; i++)
    {
        Student *stu = class->students[i];
        if (stu)
        {
            sum += stu->score[subjectIdx];
            cnt++;
        }
    }
    return cnt ? sum / cnt : 0;
}

// 班级内所有学生总分的平均分
double getClassTotalAvg(Class *class)
{
    double sum = 0;
    int cnt = 0;
    for (int i = 0; i < class->size; i++)
    {
        Student *stu = class->students[i];
        if (stu)
        {
            sum += getStudentSum(stu);
            cnt++;
        }
    }
    return cnt ? sum / cnt : 0;
}