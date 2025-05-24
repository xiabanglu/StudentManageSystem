#ifndef SCORE_H
#define SCORE_H

#include "common.h"
#include "search.h"

// 函数声明
double getStudentSum(Student *student);

Class *getSortedClassByTotalScore(Class *class);
void getClassSubjectRange(Class *class, int subjectIdx, double *max, double *min);
void getClassTotalRange(Class *class, double *max, double *min);
double getClassSubjectAvg(Class *class, int subjectIdx);
double getClassTotalAvg(Class *class);

#endif