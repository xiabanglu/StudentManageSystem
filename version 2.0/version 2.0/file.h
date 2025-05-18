#include <string.h>
#include <stdio.h>

#include "search.h"

// 程序入口初始化信息
void loadStudentFromFile(const char *file_path, School *school)
{
    FILE *file = fopen(file_path, "r");
    if (file == NULL)
    {
        Log("Failed to open student file!(打开文件失败!)", ERROR);
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), file))
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
        
        // 加强ID格式验证
        if (indices.gradeId < 2024 || indices.gradeId > 2030 || // 假设年级范围2024-2030
            indices.classId <= 0 || indices.classId > _MAX_CLASS_NUM_PER_GRADE_ ||
            indices.studentId <= 0 || indices.studentId > _MAX_STUDENT_NUM_PER_CLASS_) 
        {
            char warn_msg[100];
            sprintf(warn_msg, "无效ID格式! 原始数据:%s", line);
            Log(warn_msg, WARING);
            continue;
        }

        // 定位年级和班级
        Grade **grade_ptr = getGrade(school, indices.gradeId);
        if (grade_ptr == NULL)
        {
            Log("Grade not found!(未找到年级!)", ERROR);
            continue;
        }
        Class **class_ptr = getClass(*grade_ptr, indices.classId);
        if (class_ptr == NULL)
        {
            Log("Class not found!(未找到班级!)", ERROR);
            continue;
        }

        // 创建学生对象并填充数据
        Student *student = (*class_ptr)->students[indices.studentId - 1];
        student->indices = indices;
        strcpy(student->info.name, name);
        strcpy(student->info.gender, gender);
        student->info.age = age;
        strcpy(student->info.schoolName, schoolName);
        for (int i = 0; i < 10; i++)
        {
            student->score[i] = score[i];
        }
    }

    fclose(file);
    Log("Student data loaded successfully!(学生数据成功加载!)", INFO);
}

// 保存注册user信息
void save_register_user_to_file(const char *file_path, char *username, char *password)
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

// 保存注册admin信息
void save_register_admin_to_file(const char *file_path, char *username, const char *password)
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

// 保存学生信息
void save_register_student_to_file(const char *file_path, int id, Student *newStudent, double *score)
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

// 删去文件中某条学生数据
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


// 更新文件中某条学生数据
void update_student_from_file(const char *file_path, int id, Student *newStudent, double *score)
{
    delete_student_from_file("student.txt", id);
    save_register_student_to_file("student.txt", id, newStudent, score);
    Log("Student updated!(成功更新信息!)", INFO);
}