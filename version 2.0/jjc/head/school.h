#ifndef SCHOOL_H
#define SCHOOL_H

// 学校结构体
typedef struct School
{
    Grade **grades;         // 年级指针数组
    int size;               // 学校年级数量
    const char *schoolName; // 学校名称
} School;

// 函数声明
School *createSchool(const char *schoolName, int gradeCount);
void DeleteSchool(School *school);

#endif // SCHOOL_H