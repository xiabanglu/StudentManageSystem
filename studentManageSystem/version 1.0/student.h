#ifndef STUDENT_H
#define STUDENT_H

// 学生最大数量
#define StudentMaxNum 100

// 学生结构体
typedef struct Student
{
    int id;
    wchar_t account[20];
    wchar_t password[20];
    wchar_t name[20];
    wchar_t gender[20];
    wchar_t age[20];
    wchar_t grade[20];
    wchar_t classNum[20];

} Student;

// 学生数组
extern Student students[StudentMaxNum];

// 学生函数声明
int LoadStudentFromFile();
int SaveStudentToFile();
int CountStudentNum();

#endif // STUDENT_H
