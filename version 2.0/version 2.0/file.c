#include "file.h"

// 程序入口初始化信息
void loadStudentFromFile(const char *file_path, School *school)
{
    FILE *file = fopen(file_path, "r");
    if (file == NULL)
    {
        Log("打开student.txt失败", ERROR);
        return;
    }
    char line[512];
    while (fgets(line, sizeof(line), file))
    {
        if (line[0] == '\n')
        {
            break;
        }

        int id, age;
        char name[50], gender[10], schoolName[50];
        double scores[10];

        int parsed = sscanf(line, "%d %s %s %d %s %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf",
                            &id, name, gender, &age, schoolName,
                            &scores[0], &scores[1], &scores[2], &scores[3], &scores[4],
                            &scores[5], &scores[6], &scores[7], &scores[8], &scores[9]);

        if (parsed != 15)
        {
            Log("学生数据格式有误", ERROR);
            continue;
        }

        StudentIndices indices = explainStudentId(id);
        int grade_idx = indices.gradeId - 2024;
        int class_idx = indices.classId - 1;
        int student_idx = indices.studentId - 1;

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
            Log("无效学生", ERROR);
            continue;
        }

        Student *stu = cls->students[student_idx];
        stu->indices = indices;
        stu->indices.id = id;
        strcpy(stu->info.name, name);
        strcpy(stu->info.gender, gender);
        stu->info.age = age;
        strcpy(stu->info.schoolName, schoolName);
        memcpy(stu->score, scores, sizeof(double) * 10);
    }
    fclose(file);
    Log("学生数据加载完成", INFO);
}

// 保存user信息
void save_user_to_file(const char *file_path, char *username, char *password)
{
    FILE *file = fopen(file_path, "a");
    if (file == NULL)
    {
        Log("打开account.txt失败", ERROR);
        return;
    }

    fprintf(file, "%s %s 1\n", username, password);

    Log("注册user成功", INFO);
    fclose(file);
}

// 删除user信息
void delete_user_from_file(const char *file_path, char *username, char *password)
{
    FILE *file = fopen(file_path, "r");
    if (file == NULL)
    {
        Log("打开account.txt失败", ERROR);
        return;
    }

    FILE *temp_file = fopen("temp.txt", "w");
    if (temp_file == NULL)
    {
        Log("创建temp.txt失败", ERROR);
        fclose(file);
        return;
    }

    char line[256];
    int found = 0;
    while (fgets(line, sizeof(line), file))
    {
        char file_username[50];
        char file_password[50];
        sscanf(line, "%s %s", file_username, file_password);
        if (strcmp(file_username, username) != 0 || strcmp(file_password, password) != 0)
        {
            fputs(line, temp_file);
        }
        else
        {
            found = 1;
        }
    }

    fclose(file);
    fclose(temp_file);

    if (found)
    {
        remove(file_path);
        rename("temp.txt", file_path);
        Log("注销user成功", INFO);
    }
    else
    {
        remove("temp.txt");
        Log("未找到用户", WARNING);
    }
}

// 保存admin信息
void save_admin_to_file(const char *file_path, char *username, const char *password)
{
    FILE *file = fopen(file_path, "a");
    if (file == NULL)
    {
        Log("打开account.txt失败", ERROR);
        return;
    }

    fprintf(file, "%s %s 2\n", username, password);

    Log("注册admin成功", INFO);
    fclose(file);
}

// 删除admin信息
void delete_admin_from_file(const char *file_path, char *username, char *password)
{
    FILE *file = fopen(file_path, "r");
    if (file == NULL)
    {
        Log("打开account.txt失败", ERROR);
        return;
    }

    FILE *temp_file = fopen("temp.txt", "w");
    if (temp_file == NULL)
    {
        Log("创建temp.txt失败", ERROR);
        fclose(file);
        return;
    }

    char line[256];
    int found = 0;
    while (fgets(line, sizeof(line), file))
    {
        char file_username[50];
        char file_password[50];
        sscanf(line, "%s %s", file_username, file_password);
        if (strcmp(file_username, username) != 0 || strcmp(file_password, password) != 0)
        {
            fputs(line, temp_file);
        }
        else
        {
            found = 1;
        }
    }

    fclose(file);
    fclose(temp_file);

    if (found)
    {
        remove(file_path);
        rename("temp.txt", file_path);
        Log("注销admin成功", INFO);
    }
    else
    {
        remove("temp.txt");
        Log("未找到管理员", WARNING);
    }
}

// 保存一条学生信息
void save_student_to_file(const char *file_path, int id, Student *newStudent, double *score)
{
    FILE *file = fopen(file_path, "a");
    if (file == NULL)
    {
        Log("打开student.txt失败", ERROR);
        return;
    }

    fprintf(file, "%d %s %s %d %s %.1lf %.1lf %.1lf %.1lf %.1lf %.1lf %.1lf %.1lf %.1lf %.1lf\n",
            id, newStudent->info.name, newStudent->info.gender, newStudent->info.age, newStudent->info.schoolName,
            score[0], score[1], score[2], score[3], score[4], score[5],
            score[6], score[7], score[8], score[9]);

    Log("学生信息添加成功", INFO);
    fclose(file);
}

// 删去某条学生数据
void delete_student_from_file(const char *file_path, int id)
{
    FILE *file = fopen(file_path, "r");
    if (file == NULL)
    {
        Log("打开student.txt失败", ERROR);
        return;
    }

    FILE *temp = fopen("temp.txt", "w");
    if (temp == NULL)
    {
        Log("创建temp.txt失败", ERROR);
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
        Log("成功删除学生信息", INFO);
    }
    else
    {
        remove("temp.txt");
        Log("未找到该学生", WARNING);
    }
}

// 更新某条学生数据
void update_student_from_file(const char *file_path, int id, Student *newStudent, double *score)
{
    FILE *file = fopen(file_path, "r");
    if (file == NULL)
    {
        Log("打开student.txt失败", ERROR);
        return;
    }

    FILE *temp = fopen("temp.txt", "w");
    if (temp == NULL)
    {
        Log("创建temp.txt失败", ERROR);
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
    }
    else
    {
        remove("temp.txt");
        Log("未找到该学生", WARNING);
    }

    file = fopen(file_path, "a");
    if (file == NULL)
    {
        Log("打开student.txt失败", ERROR);
        return;
    }

    fprintf(file, "%d %s %s %d %s %.1lf %.1lf %.1lf %.1lf %.1lf %.1lf %.1lf %.1lf %.1lf %.1lf\n",
            id, newStudent->info.name, newStudent->info.gender, newStudent->info.age, newStudent->info.schoolName,
            score[0], score[1], score[2], score[3], score[4], score[5],
            score[6], score[7], score[8], score[9]);

    fclose(file);

    Log("更新学生信息成功", INFO);
}

// 检查用户名和密码是否已存在
int is_account_exist(const char *file_path, const char *username, const char *password)
{
    FILE *file = fopen(file_path, "r");
    if (file == NULL)
        return 0;
    char file_username[50], file_password[50];
    int flag;
    while (fscanf(file, "%s %s %d", file_username, file_password, &flag) == 3)
    {
        if (strcmp(file_username, username) == 0 && strcmp(file_password, password) == 0)
        {
            fclose(file);
            return 1;
        }
    }
    fclose(file);
    return 0;
}