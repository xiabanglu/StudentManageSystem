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
    int score[20];
} Student;

// 学生数组
extern Student students[STUDENTMAXNUM];

#endif // STUDENT_H
