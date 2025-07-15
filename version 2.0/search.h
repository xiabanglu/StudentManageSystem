#ifndef SEARCH_H
#define SEARCH_H

#include "common.h"

// 学校最大年级数量
#define _MAX_GRADE_NUM_PER_SCHOOL_ 4

// 年级最大班级数量
#define _MAX_CLASS_NUM_PER_GRADE_ 20

// 班级最大学生数量
#define _MAX_STUDENT_NUM_PER_CLASS_ 60

// 学生信息结构体
typedef struct Info
{
	char name[10];
	char gender[10];
	int age;
	char schoolName[15];
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
	Info info;				// 学生信息
	double score[10];		// 成绩信息
} Student;

// 班级结构体
typedef struct Class
{
	Student **students;
	int size;				// 班级学生数量
	const char *schoolName; // 所属学校名称
	int gradeId;			// 年级ID
	int classId;			// 班级ID
} Class;

// 年级结构体
typedef struct Grade
{
	Class **classes;
	int size;				// 年级中班级数量
	const char *schoolName; // 所属学校名称
	int gradeId;			// 年级ID
} Grade;

// 学校结构体
typedef struct School
{
	Grade **grades;			// 年级指针数组
	int size;				// 学校年级数量
	const char *schoolName; // 学校名称
} School;

// 函数声明
StudentIndices explainStudentId(int id);
void registerStudent(School *school, int id, Student *newStudent, double *score);
void deleteStudent(School *school, int id);
void updateStudent(School *school, int id, Student *newStudent, double *score);

Student *getStudent(School *school, int id);
Grade *getGrade(School *school, int gradeId);
Class *getClass(School *school, int gradeId, int classId);

School *initSchool(const char *schoolName, int maxGrade, int maxClass, int maxStudent);
void freeSchool(School *school);

#endif