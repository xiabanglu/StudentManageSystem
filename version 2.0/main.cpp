#include <stdio.h>
#include "admin.h"
#include "student.h"
#include "ui.h"

int main()
{
	loadAdminFromFile();
	loadStudentFromFile();
	adminGraph();
    return 0;
}