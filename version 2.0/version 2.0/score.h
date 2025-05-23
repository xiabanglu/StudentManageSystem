#ifndef SCORE_H
#define SCORE_H

#include "common.h"
#include "search.h"

typedef struct ScoreLevelCount
{
    int fail;      // 不及格人数
    int pass;      // 及格人数
    int good;      // 良好人数
    int excellent; // 优秀人数
} ScoreLevelCount;

// 函数声明
double getStudentSum(Student *student);

void sortClassByTotalScore(Class *class);
ScoreLevelCount countClassSubjectLevels(Class *class, int subjectIdx);
void getClassSubjectRange(Class *class, int subjectIdx, double *max, double *min);
void getClassTotalScoreRange(Class *class, double *max, double *min);
double getClassSubjectAvg(Class *class, int subjectIdx);
double getClassTotalAvg(Class *class);

void sortGradeByClassAvg(Grade *grade);
void getGradeSubjectRange(Grade *grade, int subjectIdx, double *max, double *min);
double getGradeSubjectAvg(Grade *grade, int subjectIdx);
double getGradeTotalAvg(Grade *grade);
ScoreLevelCount countGradeSubjectLevels(Grade *grade, int subjectIdx);
void getGradeTotalScoreRange(Grade *grade, double *max, double *min);




#endif