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
	Info info;				// 学生信息
	double score[11];		// 成绩信息
} Student;

// 班级结构体
typedef struct Class
{
	Student **students;		// 学生指针数组
	int size;				// 班级学生数量
	int capacity;			// 班级最大容量
	const char *schoolName; // 所属学校名称
	int gradeId;			// 年级ID
	int classId;			// 班级ID
} Class;

// 年级结构体
typedef struct Grade
{
	Class **classes;		// 班级指针数组
	int size;				// 年级中班级数量
	const char *schoolName; // 所属学校名称
	int gradeId;			// 年级ID
} Grade;

// 学校结构体
typedef struct School
{
	Grade **grades;			// 年级指针数组
	int size;				// 学校年级数量
	const char *schoolName; // 所属学校名称
} School;

// 函数声明
StudentIndices explainStudentId(int id);
void registerStudent(School *school, int id, Student *newStudent, double *score);
void deleteStudent(School *school, int id);
void updateStudent(School *school, int id, Student *newStudent, double *score);

Grade **getGrade(School *school, int gradeId);
Class **getClass(Grade *grade, int classId);
Student **getStudent(School *school, int id);

void initGrade(Grade **grade, int classCount);
void initClass(Class **class, int studentCount);

School *createSchool(const char *schoolName, int gradeCount);
void FreeSchool(School *school);
void FreeGrade(Grade *grade);
void FreeClass(Class *class);
void FreeStudent(Student *student);

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

// 注册学生
void registerStudent(School *school, int id, Student *newStudent, double *score)
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
	strcpy((*class)->students[ind.studentId - 1]->info.name, newStudent->info.name);
	strcpy((*class)->students[ind.studentId - 1]->info.gender, newStudent->info.gender);
	(*class)->students[ind.studentId - 1]->info.age = newStudent->info.age;
	strcpy((*class)->students[ind.studentId - 1]->info.schoolName, newStudent->info.schoolName);

	for (int i = 0; i < 10; i++)
	{
		(*class)->students[ind.studentId - 1]->score[i] = score[i];
	}

	// save_register_student_to_file("student.txt", id, newStudent, score);
}

// 删除学生
void deleteStudent(School *school, int id)
{
	StudentIndices ind = explainStudentId(id);
	Grade **grade = getGrade(school, ind.gradeId);
	Class **class = getClass(*grade, ind.classId);
	if (ind.studentId > (*class)->size)
	{
		Log("Error", WARING);
	}
	else
	{
		free((*class)->students[ind.studentId - 1]);
		(*class)->students[ind.studentId - 1] = NULL;
	}
	Log("Student deleted", INFO);

	// delete_student_from_file();
}

// 更新学生信息或成绩
void updateStudent(School *school, int id, Student *newStudent, double *score)
{
	Student **student = getStudent(school, id);
	if (student == NULL)
	{
		printf("Student not found\n");
		Log("Student not found", ERROR);
		return;
	}

	// 更新姓名
	strcpy((*student)->info.name, newStudent->info.name);

	// 更新性别
	strcpy((*student)->info.gender, newStudent->info.gender);

	// 更新年龄
	(*student)->info.age = newStudent->info.age;

	// 更新所属学校
	strcpy((*student)->info.schoolName, newStudent->info.schoolName);

	// 更新成绩
	for (int i = 0; i < 10; i++)
	{
		(*student)->score[i] = score[i];
	}

	Log("Student updated", INFO);

	// update_student_from_file();
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

// 获取班级
Class **getClass(Grade *grade, int classId)
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

// 获取学生
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

// 初始化年级
void initGrade(Grade **grade, int classCount)
{
	(*grade)->classes = (Class **)malloc(sizeof(Class *) * classCount);
	(*grade)->size = classCount;

	for (int i = 0; i < classCount; i++)
	{
		(*grade)->classes[i] = (Class *)malloc(sizeof(Class));
		(*grade)->classes[i]->classId = i + 1;
		(*grade)->classes[i]->gradeId = (*grade)->gradeId;
	}
}

// 初始化班级
void initClass(Class **class, int studentCount)
{
	(*class)->students = (Student **)malloc(sizeof(Student *) * studentCount);
	(*class)->size = studentCount;
	(*class)->capacity = studentCount;

	for (int i = 0; i < studentCount; i++)
	{
		(*class)->students[i] = (Student *)malloc(sizeof(Student));
		(*class)->students[i]->indices.classId = (*class)->classId;
		(*class)->students[i]->indices.gradeId = (*class)->gradeId;
		(*class)->students[i]->indices.id = (*class)->gradeId * 10000 + (*class)->classId * 100 + i + 1;
	}
}

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

// 删除学校内存
void FreeSchool(School *school)
{
	if (school)
	{
		if (school->grades)
		{
			for (int i = 0; i < school->size; i++)
			{
				FreeGrade(school->grades[i]);
			}
			free(school->grades);
		}
		free(school);
	}
}

// 删除年级内存
void FreeGrade(Grade *grade)
{
	if (grade)
	{
		if (grade->classes)
		{
			for (int i = 0; i < grade->size; i++)
			{
				FreeClass(grade->classes[i]);
			}
			free(grade->classes);
		}
		free(grade);
	}
}

// 删除班级内存
void FreeClass(Class *class)
{
	if (class)
	{
		if (class->students)
		{
			for (int i = 0; i < class->size; i++)
			{
				FreeStudent(class->students[i]);
			}
			free(class->students);
		}
		free(class);
	}
}

// 删除学生内存
void FreeStudent(Student *student)
{
	if (student)
	{
		free(student);
	}
}

#endif // SEARCH_H