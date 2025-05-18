#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "search.h"

typedef struct ScoreLevelCount
{
    int fail;      // 不及格人数
    int pass;      // 及格人数
    int good;      // 良好人数
    int excellent; // 优秀人数
} ScoreLevelCount;

// 函数声明
int getSum(Student *student);
double getClassSubjectMax(Class *class, int subjectIdx);
double getGradeSubjectMax(Grade *grade, int subjectIdx);
double getClassSubjectAvg(Class *class, int subjectIdx);
double getClassSubjectVariance(Class *class, int subjectIdx);
double getClassSubjectMedian(Class *class, int subjectIdx);
double getGradeSubjectAvg(Grade *grade, int subjectIdx);
double getGradeSubjectVariance(Grade *grade, int subjectIdx);
double getGradeSubjectMedian(Grade *grade, int subjectIdx);
double getClassTotalAvg(Class *class);
double getGradeTotalAvg(Grade *grade);
ScoreLevelCount countClassSubjectLevels(Class *class, int subjectIdx);
ScoreLevelCount countGradeSubjectLevels(Grade *grade, int subjectIdx);
int cmpDouble(const void *a, const void *b);

// ScoreLevelCount c = countClassSubjectLevels(class, 0);
// printf("语文 不及格:%d 及格:%d 良好:%d 优秀:%d\n", c.fail, c.pass, c.good, c.excellent);
// 如需统计所有学科，可以循环 subjectIdx 0~9，分别调用上述函数即可。

// 某同学总分
// 暂规定score[11],包含十门学科成绩，第十一位存放总分
int getSum(Student *student)
{
    int sum = 0;
    for (int i = 0; i < 10; i++)
    {
        sum += student->score[i];
    }
    return sum;
}

// 班级某学科最高分
double getClassSubjectMax(Class *class, int subjectIdx)
{
    double max = -1;
    for (int i = 0; i < class->size; i++)
    {
        Student *stu = class->students[i];
        if (stu && stu->score[subjectIdx] > max)
            max = stu->score[subjectIdx];
    }
    return max;
}

// 年级某学科最高分
double getGradeSubjectMax(Grade *grade, int subjectIdx)
{
    double max = -1;
    for (int i = 0; i < grade->size; i++)
    {
        Class *class = grade->classes[i];
        double classMax = getClassSubjectMax(class, subjectIdx);
        if (classMax > max)
            max = classMax;
    }
    return max;
}

// 班级某学科平均分
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

// 班级某学科方差
double getClassSubjectVariance(Class *class, int subjectIdx)
{
    double mean = getClassSubjectAvg(class, subjectIdx);
    double variance = 0;
    int cnt = 0;
    for (int i = 0; i < class->size; i++)
    {
        Student *stu = class->students[i];
        if (stu)
        {
            variance += (stu->score[subjectIdx] - mean) * (stu->score[subjectIdx] - mean);
            cnt++;
        }
    }
    return cnt ? variance / cnt : 0;
}

// 班级某学科中位数
double getClassSubjectMedian(Class *class, int subjectIdx)
{
    double temp[class->size];
    int cnt = 0;
    for (int i = 0; i < class->size; i++)
    {
        Student *stu = class->students[i];
        if (stu)
            temp[cnt++] = stu->score[subjectIdx];
    }
    if (cnt == 0)
        return 0;
    qsort(temp, cnt, sizeof(double), cmpDouble);
    if (cnt % 2)
        return temp[cnt / 2];
    else
        return (temp[cnt / 2 - 1] + temp[cnt / 2]) / 2.0;
}

// 年级某学科平均分
double getGradeSubjectAvg(Grade *grade, int subjectIdx)
{
    double sum = 0;
    int cnt = 0;
    for (int i = 0; i < grade->size; i++)
    {
        Class *class = grade->classes[i];
        for (int j = 0; j < class->size; j++)
        {
            Student *stu = class->students[j];
            if (stu)
            {
                sum += stu->score[subjectIdx];
                cnt++;
            }
        }
    }
    return cnt ? sum / cnt : 0;
}

// 年级某学科方差
double getGradeSubjectVariance(Grade *grade, int subjectIdx)
{
    double mean = getGradeSubjectAvg(grade, subjectIdx);
    double variance = 0;
    int cnt = 0;
    for (int i = 0; i < grade->size; i++)
    {
        Class *class = grade->classes[i];
        for (int j = 0; j < class->size; j++)
        {
            Student *stu = class->students[j];
            if (stu)
            {
                variance += (stu->score[subjectIdx] - mean) * (stu->score[subjectIdx] - mean);
                cnt++;
            }
        }
    }
    return cnt ? variance / cnt : 0;
}

// 年级某学科中位数
double getGradeSubjectMedian(Grade *grade, int subjectIdx)
{
    double temp[_MAX_STUDENT_NUM_PER_CLASS_ * _MAX_CLASS_NUM_PER_GRADE_];
    int cnt = 0;
    for (int i = 0; i < grade->size; i++)
    {
        Class *class = grade->classes[i];
        for (int j = 0; j < class->size; j++)
        {
            Student *stu = class->students[j];
            if (stu)
                temp[cnt++] = stu->score[subjectIdx];
        }
    }
    if (cnt == 0)
        return 0;
    qsort(temp, cnt, sizeof(double), cmpDouble);
    if (cnt % 2)
        return temp[cnt / 2];
    else
        return (temp[cnt / 2 - 1] + temp[cnt / 2]) / 2.0;
}

// 班级总分平均分
double getClassTotalAvg(Class *class)
{
    double sum = 0;
    int cnt = 0;
    for (int i = 0; i < class->size; i++)
    {
        Student *stu = class->students[i];
        if (stu)
        {
            sum += getSum(stu);
            cnt++;
        }
    }
    return cnt ? sum / cnt : 0;
}

// 年级总分平均分
double getGradeTotalAvg(Grade *grade)
{
    double sum = 0;
    int cnt = 0;
    for (int i = 0; i < grade->size; i++)
    {
        Class *class = grade->classes[i];
        for (int j = 0; j < class->size; j++)
        {
            Student *stu = class->students[j];
            if (stu)
            {
                sum += getSum(stu);
                cnt++;
            }
        }
    }
    return cnt ? sum / cnt : 0;
}

// 班级某学科分数等级人数统计
ScoreLevelCount countClassSubjectLevels(Class *class, int subjectIdx)
{
    ScoreLevelCount counter = {0, 0, 0, 0};
    for (int i = 0; i < class->size; i++)
    {
        Student *stu = class->students[i];
        if (stu)
        {
            double s = stu->score[subjectIdx];
            if (s < 60)
                counter.fail++;
            else if (s < 80)
                counter.pass++;
            else if (s < 90)
                counter.good++;
            else
                counter.excellent++;
        }
    }
    return counter;
}

// 年级某学科分数等级人数统计
ScoreLevelCount countGradeSubjectLevels(Grade *grade, int subjectIdx)
{
    ScoreLevelCount counter = {0, 0, 0, 0};
    for (int i = 0; i < grade->size; i++)
    {
        Class *class = grade->classes[i];
        ScoreLevelCount c = countClassSubjectLevels(class, subjectIdx);
        counter.fail += c.fail;
        counter.pass += c.pass;
        counter.good += c.good;
        counter.excellent += c.excellent;
    }
    return counter;
}

int cmpDouble(const void *a, const void *b)
{
    double diff = *(double *)a - *(double *)b;
    return (diff > 0) - (diff < 0);
}