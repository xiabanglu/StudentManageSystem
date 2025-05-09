#include <stdio.h>
#include "admin.h"
#include "student.h"
#include "ui.h"

int main()
{
	// 初始化管理员和学生数组
	for (int i = 0; i < ADMINMAXNUM; i++)
		admins[i].id = -1;
	for (int i = 0; i < STUDENTMAXNUM; i++)
		students[i].id = -1;

	loadAdminFromFile();
	loadStudentFromFile();
	adminGraph();
	return 0;
}