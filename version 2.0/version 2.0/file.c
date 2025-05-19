#include "file.h"

// 程序入口初始化信息
void loadStudentFromFile(const char *file_path, School *school)
{
    FILE *file = fopen(file_path, "r");
    if (file == NULL)
    {
        // 创建空文件
        file = fopen(file_path, "w");
        if (file)
            fclose(file);
        Log("未找到学生文件，已自动创建空文件", WARING);
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), file) != NULL)
    {
        // 解析学生数据
        int id, age;
        char name[50], gender[10], schoolName[50];
        double score[10];

        int parsed = sscanf(line, "%d %s %s %d %s %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf",
                            &id, name, gender, &age, schoolName,
                            &score[0], &score[1], &score[2], &score[3], &score[4],
                            &score[5], &score[6], &score[7], &score[8], &score[9]);
        if (parsed != 15)
        {
            Log("Invalid data format in student file!(文本格式错误!)", WARING);
            continue;
        }

        // 解析学生ID结构
        StudentIndices indices = explainStudentId(id);

        // 动态获取或创建年级
        Grade **grade_ptr = getGrade(school, indices.gradeId);
        if (grade_ptr == NULL)
        {
            // 动态添加新年级
            addGradeToSchool(school, indices.gradeId);
            grade_ptr = getGrade(school, indices.gradeId);
        }

        // 动态获取或创建班级
        Class **class_ptr = getClass(*grade_ptr, indices.classId);
        if (class_ptr == NULL)
        {
            // 动态添加新班级
            addClassToGrade(*grade_ptr, indices.classId);
            class_ptr = getClass(*grade_ptr, indices.classId);
        }

        // 确保学生位置有效
        if (indices.studentId > (*class_ptr)->capacity)
        {
            // 扩容班级容量
            resizeClass(*class_ptr, indices.studentId);
        }

        // 修改后的学生对象创建逻辑
        Student *student = (*class_ptr)->students[indices.studentId - 1];
        if (student == NULL)
        {
            student = (Student *)malloc(sizeof(Student));
            // 初始化内存
            memset(student, 0, sizeof(Student));
            (*class_ptr)->students[indices.studentId - 1] = student;
        }

        // 填充数据前添加初始化
        student->indices = indices;
        strcpy(student->info.name, name);
        strcpy(student->info.gender, gender);
        student->info.age = age;
        strcpy(student->info.schoolName, schoolName);

        // 成绩赋值
        for (int i = 0; i < 10; i++)
        {
            student->score[i] = score[i];
        }
    }

    fclose(file);
    Log("Student data loaded successfully!(学生数据成功加载!)", INFO);
}

// 保存user信息
void save_user_to_file(const char *file_path, char *username, char *password)
{
    FILE *file = fopen(file_path, "a");
    if (file == NULL)
    {
        Log("File is error!(不存在该文件!)", ERROR);
        return;
    }

    fprintf(file, "%s %s 1\n", username, password);

    Log("Register user successful!(注册user成功!)", INFO);
    fclose(file);
}

// 删除user信息
void delete_user_from_file(const char *file_path, char *username, char *password)
{
    FILE *file = fopen(file_path, "r");
    if (file == NULL)
    {
        Log("File is error!(不存在该文件!)", ERROR);
        return;
    }

    FILE *temp_file = fopen("temp.txt", "w");
    if (temp_file == NULL)
    {
        Log("File is error!(创建失败!)", ERROR);
        fclose(file);
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), file))
    {
        int flag;
        char file_username[50];
        char file_password[50];
        sscanf(line, "%s %s %d", file_username, file_password, &flag);
        if (strcmp(file_username, username) != 0 && strcmp(file_password, password) != 0)
        {
            fputs(line, temp_file);
        }
        else
        {
            if (flag != 1)
            {
                Log("Your authority is insufficient!(你的权限不够！)", ERROR);
                return;
            }
        }
    }

    fclose(file);
    fclose(temp_file);

    remove(file_path);
    rename("temp.txt", file_path);
    Log("User deleted successfully!(成功注销普通用户！)", INFO);
}

// 保存admin信息
void save_admin_to_file(const char *file_path, char *username, const char *password)
{
    FILE *file = fopen(file_path, "a");
    if (file == NULL)
    {
        Log("File is error!(不存在该文件!)", ERROR);
        return;
    }

    fprintf(file, "%s %s 2\n", username, password);

    Log("Register admin successful!(注册admin成功!)", INFO);
    fclose(file);
}

// 删除admin信息
void delete_admin_from_file(const char *file_path, char *username, char *password)
{
    FILE *file = fopen(file_path, "r");
    if (file == NULL)
    {
        Log("File is error!(不存在该文件!)", ERROR);
        return;
    }

    FILE *temp_file = fopen("temp.txt", "w");
    if (temp_file == NULL)
    {
        Log("File is error!(创建失败!)", ERROR);
        fclose(file);
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), file))
    {
        int flag;
        char file_username[50];
        char file_password[50];
        sscanf(line, "%s %s %d", file_username, file_password, &flag);
        if (strcmp(file_username, username) != 0 && strcmp(file_password, password) != 0)
        {
            fputs(line, temp_file);
        }
        else
        {
            if (flag != 2)
            {
                Log("Your authority is insufficient!(你的权限不够！)", ERROR);
                return;
            }
        }
    }

    fclose(file);
    fclose(temp_file);

    remove(file_path);
    rename("temp.txt", file_path);
    Log("Admin deleted successfully!(成功注销管理员！)", INFO);
}

// 保存一条学生信息
void save_student_to_file(const char *file_path, int id, Student *newStudent, double *score)
{
    FILE *file = fopen(file_path, "a");
    if (file == NULL)
    {
        Log("File is error!(不存在该文件!)", ERROR);
        return;
    }

    fprintf(file, "%d %s %s %d %s %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf\n",
            id, newStudent->info.name, newStudent->info.gender, newStudent->info.age, newStudent->info.schoolName,
            score[0], score[1], score[2], score[3], score[4], score[5],
            score[6], score[7], score[8], score[9]);

    Log("Student registered successfully!(学生添加成功!)", INFO);
    fclose(file);
}

// 删去某条学生数据
void delete_student_from_file(const char *file_path, int id)
{
    FILE *file = fopen(file_path, "r");
    if (file == NULL)
    {
        Log("File is error!(不存在该文件!)", ERROR);
        return;
    }

    FILE *temp = fopen("temp.txt", "w");
    if (temp == NULL)
    {
        Log("File is error!(创建失败!)", ERROR);
        fclose(file);
        return;
    }

    char line[256];
    int found = 0;
    while (fgets(line, sizeof(line), file))
    {
        int current_id;
        sscanf(line, "%d", &current_id);
        if (current_id == id)
        {
            found = 1;
            continue;
        }
        fputs(line, temp);
    }

    fclose(file);
    fclose(temp);

    if (found)
    {
        remove("student.txt");
        rename("temp.txt", "student.txt");
        Log("Student file record deleted!(成功删除!)", INFO);
    }
    else
    {
        remove("temp.txt");
        Log("Student ID not found in file!(未找到该学生!)", WARING);
    }
}

// 更新某条学生数据
void update_student_from_file(const char *file_path, int id, Student *newStudent, double *score)
{
    delete_student_from_file(file_path, id);
    save_student_to_file(file_path, id, newStudent, score);
    Log("Student updated!(成功更新信息!)", INFO);
}