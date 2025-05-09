#ifndef STUDENT_H
#define STUDENT_H

#include "account.h"
#include "info.h"
#include "score.h"

// 学生最大数量
#define STUDENTMAXNUM 1000

// 学生结构体
typedef struct Student
{
	int id;
	Account account;
	Info info;
	Score score;
} Student;

// 学生数组
extern Student students[STUDENTMAXNUM];

// 函数声明
int countStudentNum();
int loadStudentFromFile();
int saveStudentToFile();

#endif // STUDENT_H
