#ifndef CLASS_H
#define CLASS_H

// 年级最大班级数量
#define _MAX_CLASS_NUM_PER_GRADE_ 20

// 班级结构体
typedef struct Class
{
    Student **students; // 学生指针数组
    int size;           // 班级学生数量
    int capacity;       // 班级最大容量
    int schoolName;     // 学校
    int gradeId;        // 年级ID
    int classId;        // 班级ID
} Class;

// 函数声明
void initClass(Class **class, int studentCount);
Class **getClass(Grade *grade, int classId);
void DeleteClass(Class *class);

#endif // CLASS_H