#ifndef STUDENT_H
#define STUDENT_H

// 学生最大数量
#define STUDENTMAXNUM 1000

// 学生结构体
typedef struct Student
{
    int id;
    char account[20];
    char password[20];
    char name[20];
    char gender[20];
    char age[20];
    char grade[20];
    char classNum[20];
	double score[10];//高数 线代 程序设计 概率论 离散数学 数据库 计算机网络 操作系统 计算机组成原理 数据结构与算法
} Student;

// 学生数组
extern Student students[STUDENTMAXNUM];

// 函数声明
int countStudentNum();
int loadStudentFromFile();
int saveStudentToFile();

#endif // STUDENT_H
