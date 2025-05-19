#include "file.h"

// 程序入口初始化信息
void loadStudentFromFile(const char *file_path, School *school)
{
    FILE *file = fopen(file_path, "r");
    if (file == NULL)
    {
        Log("无法加载学生文件!", ERROR);
        return;
    }

    char line[512];
    while (fgets(line, sizeof(line), file))
    {
        int id, age;
        char name[50], gender[10], schoolName[50];
        double scores[10];

        // 解析学生数据
        int parsed = sscanf(line, "%d %s %s %d %s %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf",
                            &id, name, gender, &age, schoolName,
                            &scores[0], &scores[1], &scores[2], &scores[3], &scores[4],
                            &scores[5], &scores[6], &scores[7], &scores[8], &scores[9]);

        if (parsed != 15)
        {
            Log("学生数据格式错误!", ERROR);
            continue;
        }

        // 解释ID获取索引
        StudentIndices indices = explainStudentId(id);
        int grade_idx = indices.gradeId - 2024;  // 年级索引
        int class_idx = indices.classId - 1;     // 班级索引
        int student_idx = indices.studentId - 1; // 学生索引

        // 检查索引有效性
        if (grade_idx < 0 || grade_idx >= school->size)
        {
            Log("无效年级!", ERROR);
            continue;
        }
        Grade *grade = school->grades[grade_idx];
        if (class_idx < 0 || class_idx >= grade->size)
        {
            Log("无效班级!", ERROR);
            continue;
        }
        Class *cls = grade->classes[class_idx];
        if (student_idx < 0 || student_idx >= cls->size)
        {
            Log("无效学生位置!", ERROR);
            continue;
        }

        // 填充内存数据
        Student *stu = cls->students[student_idx];
        stu->indices = indices;
        strcpy(stu->info.name, name);
        strcpy(stu->info.gender, gender);
        stu->info.age = age;
        strcpy(stu->info.schoolName, schoolName);
        memcpy(stu->score, scores, sizeof(double) * 10);
    }
    fclose(file);
    Log("学生数据加载完成!", INFO);
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