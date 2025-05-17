#ifndef GRADE_H
#define GRADE_H

#include "class.h"

// 学校最大年级数量
#define _MAX_GRADE_NUM_PER_SCHOOL_ 4

// 年级结构体
typedef struct Grade
{
    Class **classes;      // 班级指针数组
    int size;             // 年级中班级数量
    int schoolName;       // 学校
    int gradeId;          // 年级ID
} Grade;

//函数声明
void initGrade(Grade **grade, int classCount);
Grade **getGrade(School *school, int gradeId);

#endif // GRADE_H