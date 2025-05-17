#ifndef STUDENT_H
#define STUDENT_H

#include "account.h"
#include "info.h"

// 班级学生最大数量
#define _MAX_STUDENT_NUM_PER_CLASS_ 60

// 学生结构体
typedef struct Student
{
	StudentIndices indices; // id信息
	Account account;		// 登录信息
	Info info;				// 学生信息
	double score[11];		// 成绩信息
} Student;

// 学生解析ID结构体
typedef struct StudentIndices
{
	int id; // 总ID 20240201

	// 解析后id
	int studentId; // 学生ID 01
	int classId;   // 班级ID 02
	int gradeId;   // 年级ID 2024
} StudentIndices;

// 函数声明
StudentIndices explainStudentId(int id);
Student **getStudent(School *school, int id);
void registerStudent(School *school, int id, Info *newStudentInfo);
void deleteStudent(School *school, int id);
void updateStudent(School *school, int id, Info *newStudentInfo, double score[10]);

#endif // STUDENT_H
