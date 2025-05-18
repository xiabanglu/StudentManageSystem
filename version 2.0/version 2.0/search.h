#ifndef SEARCH_H
#define SEARCH_H

#include <stdlib.h>
#include <string.h>
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
typedef struct Clazz
{
    Student **students; // 学生指针数组
    int size;           // 班级学生数量
    int capacity;       // 班级最大容量
    const char *schoolName; // 学校名称
    int gradeId;        // 年级ID
    int classId;        // 班级ID
} Clazz;

// 年级结构体
typedef struct Grade
{
    Clazz **classes; // 班级指针数组
    int size;        // 年级中班级数量
    const char *schoolName;  // 学校名称
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
void initClazz(Clazz **clazz, int studentCount);
Clazz **getClazz(Grade *grade, int classId);
void DeleteClazz(Clazz *clazz);
void traverseAllStudents(School *school);

// 创建学校
School *createSchool(const char *schoolName, int gradeCount)
{
	School *school = (School *)malloc(sizeof(School));
	school->size = gradeCount;
	school->schoolName = schoolName;

	school->grades = (Grade **)malloc(sizeof(Grade *) * gradeCount);
	for (int i = 0; i < gradeCount; i++)
	{
		school->grades[i] = (Grade *)malloc(sizeof(Grade));
		school->grades[i]->gradeId = i + 1;
	}

	return school;
}

// 删除学校
void DeleteSchool(School *school)
{
	if (school)
	{
		if (school->grades)
		{
			for (int i = 0; i < school->size; i++)
			{
				DeleteGrade(school->grades[i]);
			}
			free(school->grades);
		}
		free(school);
	}
}

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

	Clazz **clazz = getClazz(*grade, indices.classId);
	if (clazz == NULL)
	{
		printf("id is error: class is error\n");
		return NULL;
	}

	if (indices.studentId > (*clazz)->size)
	{
		printf("id is error: student is error\n");
		return NULL;
	}
	else
	{
		return &(*clazz)->students[indices.studentId - 1];
	}

	return NULL;
}

// 注册学生(newStudentInfo为待注册学生的info参数，成绩信息不应该在此处获得)
void registerStudent(School *school, int id, Info *newStudentInfo)
{
	// 解析id并查找
	StudentIndices ind = explainStudentId(id);
	Grade **grade = getGrade(school, ind.gradeId);
	Clazz **clazz = getClazz(*grade, ind.classId);

	// 处理id
	(*clazz)->students[ind.studentId - 1]->indices.id = id;
	(*clazz)->students[ind.studentId - 1]->indices.studentId = ind.studentId;
	(*clazz)->students[ind.studentId - 1]->indices.classId = ind.classId;
	(*clazz)->students[ind.studentId - 1]->indices.gradeId = ind.gradeId;

	// 处理学生信息
	strcpy((*clazz)->students[ind.studentId - 1]->info.name, newStudentInfo->name);
	strcpy((*clazz)->students[ind.studentId - 1]->info.gender, newStudentInfo->gender);
	(*clazz)->students[ind.studentId - 1]->info.age = newStudentInfo->age;
	strcpy((*clazz)->students[ind.studentId - 1]->info.schoolName, newStudentInfo->schoolName);
}

// 删除学生
void deleteStudent(School *school, int id)
{
	StudentIndices ind = explainStudentId(id);
	Grade **grade = getGrade(school, ind.gradeId);
	Clazz **clazz = getClazz(*grade, ind.classId);
	if (ind.studentId > (*clazz)->size)
	{
		Log("Error", WARING);
	}
	else
	{
		free((*clazz)->students[ind.studentId - 1]);
		(*clazz)->students[ind.studentId - 1] = NULL;
	}
	Log("Student deleted", INFO);
}

void DeleteStudent(Student *student)
{
	if (student)
	{
		free(student);
	}
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
	strcpy((*student)->info.name, newStudentInfo->name);

	// 更新性别
	strcpy((*student)->info.gender, newStudentInfo->gender);

	// 更新年龄
	(*student)->info.age = newStudentInfo->age;

	// 更新所属学校
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

// 暂规定score[11],包含十门学科成绩，第十一位存放总分
// 计算总分
int getSum(Student *student)
{
	int sum = 0;
	for (int i = 0; i < 10; i++)
	{
		sum += student->score[i];
	}
	return sum;
}

// 初始化年级
void initGrade(Grade **grade, int classCount)
{
    (*grade)->classes = (Clazz **)malloc(sizeof(Clazz *) * classCount);
    (*grade)->size = classCount;

    for (int i = 0; i < classCount; i++)
    {
        (*grade)->classes[i] = (Clazz *)malloc(sizeof(Clazz));
        (*grade)->classes[i]->classId = i + 1;
        (*grade)->classes[i]->gradeId = (*grade)->gradeId;
    }
}

// 获取年级
Grade **getGrade(School *school, int gradeId)
{
	for (int i = 0; i < school->size; i++)
	{
		if (school->grades[i]->gradeId == gradeId)
		{
			return &school->grades[i];
		}
	}

	return NULL;
}

// 删除年级
void DeleteGrade(Grade *grade)
{
	if (grade)
	{
		if (grade->classes)
		{
			for (int i = 0; i < grade->size; i++)
			{
				DeleteClazz(grade->classes[i]);
			}
			free(grade->classes);
		}
		free(grade);
	}
}

// 初始化班级
void initClazz(Clazz **clazz, int studentCount)
{
	(*clazz)->students = (Student **)malloc(sizeof(Student *) * studentCount);
	(*clazz)->size = studentCount;
	(*clazz)->capacity = studentCount;

	for (int i = 0; i < studentCount; i++)
	{
		(*clazz)->students[i] = (Student *)malloc(sizeof(Student));
		(*clazz)->students[i]->indices.classId = (*clazz)->classId;
		(*clazz)->students[i]->indices.gradeId = (*clazz)->gradeId;
		(*clazz)->students[i]->indices.id = (*clazz)->gradeId * 10000 + (*clazz)->classId * 100 + i + 1;
	}
}

// 获取班级
Clazz **getClazz(Grade *grade, int classId)
{
    for (int i = 0; i < grade->size; i++)
    {
        if (grade->classes[i]->classId == classId)
        {
            return &grade->classes[i];
        }
    }

    return NULL;
}

// 删除班级
void DeleteClazz(Clazz *clazz)
{
    if (clazz)
    {
        if (clazz->students)
        {
            for (int i = 0; i < clazz->size; i++)
            {
                DeleteStudent(clazz->students[i]);
            }
            free(clazz->students);
        }
        free(clazz);
    }
}

// 按年级、班级遍历所有学生
void traverseAllStudents(School *school) {
    for (int i = 0; i < school->size; i++) {
        Grade *grade = school->grades[i];
        for (int j = 0; j < grade->size; j++) {
            Clazz *clazz = grade->classes[j];
            for (int k = 0; k < clazz->size; k++) {
                Student *student = clazz->students[k];
                if (student != NULL) {
                    // 这里可以处理student，比如打印信息
                    // printf("%s\n", student->info.name);
                }
            }
        }
    }
}

#endif // SEARCH_H