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

// 班级按学生总分排序

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

// 班级学科的最高分和最低分
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

// 班级学生总分的最高分和最低分

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

// 年级按班级总分平均分排序

// 年级某学科的最高分和最低分
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

// 年级学生总分的最高分和最低分

// 年级内所有学生某学科的平均分
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

// 年级内所有学生总分的平均分
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