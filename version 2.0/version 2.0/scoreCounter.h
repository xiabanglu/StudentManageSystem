#ifndef SCORECOUNTER_H
#define SCORECOUNTER_H

#include "common.h"

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

#endif