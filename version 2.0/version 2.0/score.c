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
void sortClassByTotalScore(Class *class)
{
    for (int i = 0; i < class->size - 1; i++)
    {
        for (int j = 0; j < class->size - i - 1; j++)
        {
            Student *stu1 = class->students[j];
            Student *stu2 = class->students[j + 1];
            if (stu1 && stu2)
            {
                double sum1 = getStudentSum(stu1);
                double sum2 = getStudentSum(stu2);
                if (sum1 < sum2)
                {
                    Student *temp = class->students[j];
                    class->students[j] = class->students[j + 1];
                    class->students[j + 1] = temp;
                }
            }
        }
    }
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
void getClassTotalScoreRange(Class *class, double *max, double *min)
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

// 年级按班级总分平均分排序（降序）
void sortGradeByClassAvg(Grade *grade)
{
    double *averages = malloc(grade->size * sizeof(double));
    Class **classes = malloc(grade->size * sizeof(Class *));

    // 计算各班级平均分
    for (int i = 0; i < grade->size; i++)
    {
        classes[i] = grade->classes[i];
        averages[i] = getClassTotalAvg(grade->classes[i]);
    }

    // 冒泡排序
    for (int i = 0; i < grade->size - 1; i++)
    {
        for (int j = 0; j < grade->size - i - 1; j++)
        {
            if (averages[j] < averages[j + 1])
            {
                // 交换平均值
                double tempAvg = averages[j];
                averages[j] = averages[j + 1];
                averages[j + 1] = tempAvg;

                // 交换班级指针
                Class *tempClass = classes[j];
                classes[j] = classes[j + 1];
                classes[j + 1] = tempClass;
            }
        }
    }

    free(averages);
}

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
void getGradeTotalScoreRange(Grade *grade, double *max, double *min)
{
    *max = -1;
    *min = 101;
    for (int i = 0; i < grade->size; i++)
    {
        Class *class = grade->classes[i];
        for (int j = 0; j < class->size; j++)
        {
            Student *stu = class->students[j];
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
}

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