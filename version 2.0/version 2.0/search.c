#include "search.h"
#include "file.h"

// 解释学生ID
StudentIndices explainStudentId(int id)
{
	StudentIndices newIndice;
	// 示例ID:20240101 → 年级2024，班级01，学生01
	newIndice.gradeId = id / 10000;		  // 前4位（2024）
	newIndice.classId = (id / 100) % 100; // 中间2位（01）
	newIndice.studentId = id % 100;		  // 后2位（01）
	newIndice.id = id;
	return newIndice;
}

// 注册学生信息和成绩
void registerStudent(School *school, int id, Student *newStudent, double *score)
{
	// 保存到文件
	save_student_to_file("student.txt", id, newStudent, score);

	// 更新内存结构
	StudentIndices indices = explainStudentId(id);
	int grade_idx = indices.gradeId - 2024;
	int class_idx = indices.classId - 1;
	int student_idx = indices.studentId - 1;

	if (grade_idx < 0 || grade_idx >= school->size)
		return;
	Grade *grade = school->grades[grade_idx];
	if (class_idx < 0 || class_idx >= grade->size)
		return;
	Class *cls = grade->classes[class_idx];
	if (student_idx < 0 || student_idx >= cls->size)
		return;

	Student *stu = cls->students[student_idx];
	stu->indices = indices;
	strcpy(stu->info.name, newStudent->info.name);
	strcpy(stu->info.gender, newStudent->info.gender);
	stu->info.age = newStudent->info.age;
	strcpy(stu->info.schoolName, newStudent->info.schoolName);
	memcpy(stu->score, score, sizeof(double) * 10);
}

// 删除学生
void deleteStudent(School *school, int id)
{
	// 从文件删除
	delete_student_from_file("student.txt", id);

	// 更新内存结构
	StudentIndices indices = explainStudentId(id);
	int grade_idx = indices.gradeId - 2024;
	int class_idx = indices.classId - 1;
	int student_idx = indices.studentId - 1;

	if (grade_idx < 0 || grade_idx >= school->size)
		return;
	Grade *grade = school->grades[grade_idx];
	if (class_idx < 0 || class_idx >= grade->size)
		return;
	Class *cls = grade->classes[class_idx];
	if (student_idx < 0 || student_idx >= cls->size)
		return;

	// 清空学生数据
	memset(cls->students[student_idx], 0, sizeof(Student));
}

// 更新学生信息和成绩
void updateStudent(School *school, int id, Student *newStudent, double *score)
{
	// 更新文件
	update_student_from_file("student.txt", id, newStudent, score);

	// 更新内存结构
	StudentIndices indices = explainStudentId(id);
	int grade_idx = indices.gradeId - 2024;
	int class_idx = indices.classId - 1;
	int student_idx = indices.studentId - 1;

	if (grade_idx < 0 || grade_idx >= school->size)
		return;
	Grade *grade = school->grades[grade_idx];
	if (class_idx < 0 || class_idx >= grade->size)
		return;
	Class *cls = grade->classes[class_idx];
	if (student_idx < 0 || student_idx >= cls->size)
		return;

	Student *stu = cls->students[student_idx];
	strcpy(stu->info.name, newStudent->info.name);
	strcpy(stu->info.gender, newStudent->info.gender);
	stu->info.age = newStudent->info.age;
	strcpy(stu->info.schoolName, newStudent->info.schoolName);
	memcpy(stu->score, score, sizeof(double) * 10);
}

// 获取学生
Student **getStudent(School *school, int id)
{
	// 遍历学校的年级
	for (int i = 0; i < school->size; i++)
	{
		Grade *grade = school->grades[i];
		// 遍历年级的班级
		for (int j = 0; j < grade->size; j++)
		{
			Class *class = grade->classes[j];
			// 遍历班级的学生
			for (int k = 0; k < class->size; k++)
			{
				Student *student = class->students[k];
				// 检查学生的ID是否匹配
				if (student->indices.id == id)
				{
					return &class->students[k]; // 返回匹配的学生指针
				}
			}
		}
	}
	return NULL; // 如果没有找到，返回NULL
}

// 初始化学校
School *initSchool(const char *schoolName, int maxGrade, int maxClass, int maxStudent)
{

	School *school = (School *)malloc(sizeof(School));
	school->schoolName = schoolName; // NUIST
	school->size = maxGrade;		 // 四个年级
	school->grades = (Grade **)malloc(school->size * sizeof(Grade *));

	// 初始化年级
	for (int i = 0; i < school->size; i++)
	{
		school->grades[i] = (Grade *)malloc(sizeof(Grade));
		school->grades[i]->gradeId = 2024 + i; // 年级ID 2024, 2025, 2026, 2027
		school->grades[i]->size = maxClass;	   // 每个年级20个班
		school->grades[i]->classes = (Class **)malloc(school->grades[i]->size * sizeof(Class *));

		// 初始化班级
		for (int j = 0; j < school->grades[i]->size; j++)
		{
			school->grades[i]->classes[j] = (Class *)malloc(sizeof(Class));
			school->grades[i]->classes[j]->classId = j + 1;	  // 班级ID 从01到20
			school->grades[i]->classes[j]->size = maxStudent; // 每个班60个学生
			school->grades[i]->classes[j]->students = (Student **)malloc(school->grades[i]->classes[j]->size * sizeof(Student *));

			// 初始化学生
			for (int k = 0; k < school->grades[i]->classes[j]->size; k++)
			{
				school->grades[i]->classes[j]->students[k] = (Student *)malloc(sizeof(Student));
				school->grades[i]->classes[j]->students[k]->indices.id = 0;
			}
		}
	}

	return school;
}

// 清除学校
void freeSchool(School *school)
{
	for (int i = 0; i < school->size; i++)
	{
		for (int j = 0; j < school->grades[i]->size; j++)
		{
			for (int k = 0; k < school->grades[i]->classes[j]->size; k++)
			{
				free(school->grades[i]->classes[j]->students[k]);
			}
			free(school->grades[i]->classes[j]->students);
			free(school->grades[i]->classes[j]);
		}
		free(school->grades[i]->classes);
		free(school->grades[i]);
	}
	free(school->grades);
	free(school);
}