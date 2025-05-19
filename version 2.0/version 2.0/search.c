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

	save_student_to_file("student.txt", id, newStudent, score);
}

// 删除学生
void deleteStudent(School *school, int id)
{
	StudentIndices ind = explainStudentId(id);
	Grade **grade = getGrade(school, ind.gradeId);
	Class **class = getClass(*grade, ind.classId);

	if (ind.studentId > (*class)->size)
	{
		Log("Error find!(未找到该学生!)", WARING);
	}
	else
	{
		free((*class)->students[ind.studentId - 1]);
		(*class)->students[ind.studentId - 1] = NULL;
	}

	delete_student_from_file("student.txt", id);
}

// 更新学生信息或成绩
void updateStudent(School *school, int id, Student *newStudent, double *score)
{
	Student **student = getStudent(school, id);
	if (student == NULL)
	{
		Log("Student not found!(未找到该学生!)", ERROR);
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

	update_student_from_file("student.txt", id, newStudent, score);
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

// 动态添加年级到学校
void addGradeToSchool(School *school, int gradeId)
{
	school->grades = realloc(school->grades, (school->size + 1) * sizeof(Grade *));
	school->grades[school->size] = createGrade(gradeId);
	school->size++;
}

// 创建年级
Grade *createGrade(int gradeId)
{
	Grade *grade = (Grade *)malloc(sizeof(Grade));
	grade->gradeId = gradeId;
	grade->classes = NULL;
	grade->size = 0;
	return grade;
}

// 动态添加班级到年级
void addClassToGrade(Grade *grade, int classId)
{
	grade->classes = realloc(grade->classes, (grade->size + 1) * sizeof(Class *));
	grade->classes[grade->size] = createClass(classId);
	grade->size++;
}

// 创建班级
Class *createClass(int classId)
{
	Class *cls = (Class *)malloc(sizeof(Class));
	cls->classId = classId;
	cls->students = NULL;
	cls->size = 0;
	cls->capacity = 0;
	return cls;
}

// 扩容班级容量
void resizeClass(Class *cls, int new_size)
{
	cls->students = realloc(cls->students, new_size * sizeof(Student *));
	for (int i = cls->capacity; i < new_size; i++)
	{
		cls->students[i] = NULL;
	}
	cls->capacity = new_size;
}