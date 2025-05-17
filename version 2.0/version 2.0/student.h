#ifndef STUDENT_H
#define STUDENT_H

#include "account.h"
#include "info.h"

#include <stdlib.h>
#include "school.h"
#include "grade.h"
#include "class.h"
#include "student.h"
#include "score.h"

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

// 解释学生ID
StudentIndices explainStudentId(int id)
{
	// 示例: id = 20240101

	// 学号: 01
	int studentId = id % 100;
	id /= 100;

	// 班级id:01
	int classId = id % 100;
	id /= 100;

	// 年级id:2024
	int gradeId = id;

	StudentIndices newIndice;
	newIndice.id = id;
	newIndice.studentId = studentId;
	newIndice.classId = classId;
	newIndice.gradeId = gradeId;

	return newIndice;
}

// 通过id获取学生
Student **getStudent(School *school, int id)
{
	StudentIndices indices = explainStudentId(id);

	Grade **grade = getGrade(school, indices.gradeId);
	if (grade == NULL)
	{
		printf("id is error: grade is error!\n");
		return NULL;
	}

	Class **class = getClass(*grade, indices.classId);
	if (class == NULL)
	{
		printf("id is error: class is error\n");
		return NULL;
	}

	if (indices.studentId > (*class)->size)
	{
		printf("id is error: student is error\n");
		return NULL;
	}
	else
	{
		return &(*class)->students[indices.studentId - 1];
	}

	return NULL;
}

// 注册学生(newStudentInfo为待注册学生的info参数，成绩信息不应该在此处获得)
void registerStudent(School *school, int id, Info *newStudentInfo)
{
	// 解析id并查找
	StudentIndices ind = explainStudentId(id);
	Grade **grade = getGrade(school, ind.gradeId);
	Class **class = getClass(*grade, ind.classId);

	// 处理id
	(*class)->students[ind.studentId - 1]->indices.id = id;
	(*class)->students[ind.studentId - 1]->indices.studentId = ind.studentId;
	(*class)->students[ind.studentId - 1]->indices.classId = ind.classId;
	(*class)->students[ind.studentId - 1]->indices.gradeId = ind.gradeId;

	// 处理学生信息
	strcpy((*class)->students[ind.studentId - 1]->info.name, newStudentInfo->name);
	strcpy((*class)->students[ind.studentId - 1]->info.gender, newStudentInfo->gender);
	(*class)->students[ind.studentId - 1]->info.age = newStudentInfo->age;
	strcpy((*class)->students[ind.studentId - 1]->info.schoolName, newStudentInfo->schoolName);
}

// 删除学生
void deleteStudent(School *school, int id)
{
    StudentIndices ind = explainStudentId(id);
    Grade *grade = getGrade(school, ind.gradeId);
    Class *class = getClass(grade, ind.classId);
    if (ind.studentId > class->size)
    {
        Log("Error", WARING);
    }
    else
    {
        free(class->students[ind.studentId - 1]);
        class->students[ind.studentId - 1] = NULL;
    }
    Log("Student deleted", INFO);
}

// 更新学生信息或成绩(传参同上加上成绩数组(总分重新计算))
void updateStudent(School *school, int id, Info *newStudentInfo, double score[10])
{
	Student **student = getStudent(school, id);
	if (student == NULL)
	{
		printf("Student not found\n");
		Log("Student not found", ERROR);
		return;
	}

	// 更新姓名
	if ((*student)->info.name == NULL)
	{
		(*student)->info.name = (char *)malloc(sizeof(char) * 10);
	}
	strcpy((*student)->info.name, newStudentInfo->name);

	// 更新性别
	if ((*student)->info.gender == NULL)
	{
		(*student)->info.gender = (char *)malloc(sizeof(char) * 10);
	}
	strcpy((*student)->info.gender, newStudentInfo->gender);

	// 更新年龄
	(*student)->info.age = newStudentInfo->age;

	// 更新所属学校
	if ((*student)->info.schoolName == NULL)
	{
		(*student)->info.schoolName = (char *)malloc(sizeof(char) * 10);
	}
	strcpy((*student)->info.schoolName, newStudentInfo->schoolName);

	// 更新成绩
	for (int i = 0; i < 10; i++)
	{
		(*student)->score[i] = score[i];
	}

	// 重新计算并更新总分
	int newSum = getSum(*student);
	(*student)->score[10] = newSum;

	Log("Student updated", INFO);
}

#endif // STUDENT_H
