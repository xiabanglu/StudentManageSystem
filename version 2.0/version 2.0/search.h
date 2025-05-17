#ifndef SEARCH_H
#define SEARCH_H

#include <stdlib.h>
#include "log.h"

// 班级学生最大数量
#define _MAX_STUDENT_NUM_PER_CLASS_ 60
// 年级最大班级数量
#define _MAX_CLASS_NUM_PER_GRADE_ 20
// 学校最大年级数量
#define _MAX_GRADE_NUM_PER_SCHOOL_ 4

// 账号结构体
typedef struct Account
{
    char *username; // 用户名
    char *password; // 密码
} Account;

// 学生信息结构体
typedef struct Info
{
    char name[50];
    char gender[10];
    int age;
    char schoolName[50];
} Info;

// 学生解析ID结构体
typedef struct StudentIndices
{
    int id; // 总ID 20240201

    // 解析后id
    int studentId; // 学生ID 01
    int classId;   // 班级ID 02
    int gradeId;   // 年级ID 2024
} StudentIndices;

// 学生结构体
typedef struct Student
{
    StudentIndices indices; // id信息
    Account account;        // 登录信息
    Info info;              // 学生信息
    double score[11];       // 成绩信息
} Student;

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

// 年级结构体
typedef struct Grade
{
    Class **classes; // 班级指针数组
    int size;        // 年级中班级数量
    int schoolName;  // 学校
    int gradeId;     // 年级ID
} Grade;

// 学校结构体
typedef struct School
{
    Grade **grades;         // 年级指针数组
    int size;               // 学校年级数量
    const char *schoolName; // 学校名称
} School;

School *createSchool(const char *schoolName, int gradeCount);
void DeleteSchool(School *school);
StudentIndices explainStudentId(int id);
Student **getStudent(School *school, int id);
void registerStudent(School *school, int id, Info *newStudentInfo);
void deleteStudent(School *school, int id);
void DeleteStudent(Student *student);
void updateStudent(School *school, int id, Info *newStudentInfo, double score[10]);
int getSum(Student *student);
void initGrade(Grade **grade, int classCount);
Grade **getGrade(School *school, int gradeId);
void DeleteGrade(Grade *grade);
void initClass(Class **class, int studentCount);
Class **getClass(Grade *grade, int classId);
void DeleteClass(Class *class);

#endif // SEARCH_H