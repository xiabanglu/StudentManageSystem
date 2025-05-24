#include "event.h"
#include "login.h"
#include "file.h"
#include "score.h"
#include "log.h"

void handle_login()
{
    char username[20];
    char password[20];
    printf(INPUT_PROMPT COLOR_YELLOW "Please enter as required(请按要求输入):\n\n" COLOR_RESET);
    printf(INPUT_PROMPT COLOR_YELLOW "username(用户名):\n" COLOR_RESET);
    printf(INPUT_PROMPT);
    scanf("%s", username);
    printf(INPUT_PROMPT COLOR_YELLOW "password(密码):\n" COLOR_RESET);
    printf(INPUT_PROMPT);
    scanf("%s", password);
    printf(HEADER_LINE "\n");

    rank = login("account.txt", username, password);

    if (rank == -1)
    {
        Log("登录时:打开account.txt失败", ERROR);
        rank = 0;
        return;
    }

    if (rank == 0)
    {
        Log("登录时:用户名或密码错误", ERROR);
        return;
    }

    set_username(username);

    // 成功登录提示
    char success_msg[50];
    sprintf(success_msg, "%s 登录成功，权限等级: %d", username, rank);
    Log(success_msg, INFO);
}

void handle_register_user()
{
    char username[20];
    char password[20];
    printf(INPUT_PROMPT COLOR_YELLOW "Please enter as required(请按要求输入):\n\n" COLOR_RESET);
    printf(INPUT_PROMPT COLOR_YELLOW "username(用户名):\n" COLOR_RESET);
    printf(INPUT_PROMPT);
    scanf("%s", username);
    printf(INPUT_PROMPT COLOR_YELLOW "password(密码):\n" COLOR_RESET);
    printf(INPUT_PROMPT);
    scanf("%s", password);
    printf(HEADER_LINE "\n");

    if (is_account_exist("account.txt", username, password))
    {
        Log("注册user时:用户名和密码已存在,注册失败", WARNING);
        return;
    }

    save_user_to_file("account.txt", username, password);
}

void handle_insert_record()
{
    if (rank != 2 && rank != 3)
    {
        Log("添加学生信息时:你的权限不够", ERROR);
        return;
    }

    int id;
    Student *newStudent = (Student *)malloc(sizeof(Student));
    double score[10];

    if (newStudent == NULL)
    {
        Log("添加学生信息时:内存分配失败", ERROR);
        return;
    }

    printf(INPUT_PROMPT COLOR_YELLOW "Please enter as required(请按格式输入):\n\n" COLOR_RESET);
    printf(INPUT_PROMPT COLOR_YELLOW "ID 姓名 性别 年龄 所属学校: \n" COLOR_RESET);
    printf(INPUT_PROMPT);
    scanf("%d %s %s %d %s",
          &id, newStudent->info.name, newStudent->info.gender,
          &newStudent->info.age, newStudent->info.schoolName);

    if (getStudent(school, id) != NULL)
    {
        Log("添加学生信息时:学生ID已存在,添加失败", ERROR);
        free(newStudent);
        return;
    }

    printf(INPUT_PROMPT COLOR_YELLOW "请依次录入十次成绩(空格间隔每门成绩): \n" COLOR_RESET);
    printf(INPUT_PROMPT);
    scanf("%lf %lf %lf %lf %lf %lf %lf %lf %lf %lf", &score[0], &score[1], &score[2],
          &score[3], &score[4], &score[5], &score[6], &score[7], &score[8], &score[9]);
    printf(HEADER_LINE "\n");

    if (!is_valid_student_info(id, newStudent->info.name, newStudent->info.gender, newStudent->info.age, newStudent->info.schoolName, score))
    {
        Log("添加学生信息时:输入信息不合法", ERROR);
        free(newStudent);
        return;
    }

    registerStudent(school, id, newStudent, score);

    free(newStudent);
}

void handle_delete_record()
{
    if (rank != 2 && rank != 3)
    {
        Log("删除学生信息时:你的权限不够", ERROR);
        return;
    }

    int id;
    printf(INPUT_PROMPT COLOR_YELLOW "Please enter id(请输入ID): \n" COLOR_RESET);
    printf(INPUT_PROMPT);
    scanf("%d", &id);
    printf(HEADER_LINE "\n");

    if (!is_valid_student_id(id))
    {
        Log("删除学生信息时:ID结构不合法", ERROR);
        return;
    }

    deleteStudent(school, id);
}

void handle_update_record()
{
    if (rank != 2 && rank != 3)
    {
        Log("更新学生信息时:你的权限不够", ERROR);
        return;
    }

    int id;
    Student *newStudent = (Student *)malloc(sizeof(Student));
    double score[10];

    if (newStudent == NULL)
    {
        Log("更新学生信息时:内存分配失败", ERROR);
        return;
    }

    printf(INPUT_PROMPT COLOR_YELLOW "Please enter as required(请按格式输入):\n\n" COLOR_RESET);
    printf(INPUT_PROMPT COLOR_YELLOW "ID 姓名 性别 年龄 所属学校: \n" COLOR_RESET);
    printf(INPUT_PROMPT);
    scanf("%d %s %s %d %s",
          &id, newStudent->info.name, newStudent->info.gender,
          &newStudent->info.age, newStudent->info.schoolName);

    if (getStudent(school, id) == NULL)
    {
        Log("更新学生信息时:未找到该学生，无法修改", WARNING);
        free(newStudent);
        return;
    }

    printf(INPUT_PROMPT COLOR_YELLOW "请依次录入十次成绩(空格间隔每门成绩): \n" COLOR_RESET);
    printf(INPUT_PROMPT);
    scanf("%lf %lf %lf %lf %lf %lf %lf %lf %lf %lf", &score[0], &score[1], &score[2],
          &score[3], &score[4], &score[5], &score[6], &score[7], &score[8], &score[9]);
    printf(HEADER_LINE "\n");

    if (!is_valid_student_info(id, newStudent->info.name, newStudent->info.gender, newStudent->info.age, newStudent->info.schoolName, score))
    {
        Log("更新学生信息时:输入信息不合法", ERROR);
        free(newStudent);
        return;
    }

    updateStudent(school, id, newStudent, score);
    free(newStudent);
}

void handle_show_record()
{
    if (rank != 1 && rank != 2 && rank != 3)
    {
        Log("查询学生信息时:你的权限不够", ERROR);
        return;
    }

    int id;
    printf(INPUT_PROMPT COLOR_YELLOW "Please enter id(请输入ID): \n" COLOR_RESET);
    printf(INPUT_PROMPT);
    scanf("%d", &id);
    printf(HEADER_LINE "\n");

    if (!is_valid_student_id(id))
    {
        Log("查询学生信息时:ID结构不合法", ERROR);
        return;
    }

    Student *student = getStudent(school, id);
    if (student == NULL)
    {
        Log("查询学生信息时:学生未找到", ERROR);
        return;
    }
    else
    {
        printf("该学生信息如下:\n");
    }
    printf("姓名: %s 性别: %s 年龄: %d 所属学校: %s\n", student->info.name,
           student->info.gender, student->info.age, student->info.schoolName);

    printf("语文\t数学\t英语\t物理\t历史\t化学\t生物\t政治\t地理\t体育\t总分\t\n");
    for (int i = 0; i < 10; i++)
    {
        printf("%.2lf\t", student->score[i]);
    }

    printf("%.2lf\t", getStudentSum(student));
    printf("\n");
}

void handle_show_records()
{
    if (rank != 2 && rank != 3)
    {
        Log("查询所有学生信息时:你的权限不够", ERROR);
        return;
    }

    printf("所有学生信息如下:\n");
    for (int i = 0; i < school->size; i++)
    {
        for (int j = 0; j < school->grades[i]->size; j++)
        {
            for (int k = 0; k < school->grades[i]->classes[j]->size; k++)
            {
                Student *student = school->grades[i]->classes[j]->students[k];
                // 仅显示有效ID的学生
                if (student != NULL && student->indices.id != 0)
                {
                    printf("ID: %d\t姓名: %s\t性别: %s\t年龄: %d\t所属学校:%s\n",
                           student->indices.id,
                           student->info.name,
                           student->info.gender,
                           student->info.age,
                           student->info.schoolName);
                }
            }
        }
    }
    printf("\n");
}

void handle_score_statistics() {}

void handle_register_admin()
{
    if (rank != 3)
    {
        Log("注册管理员时:你的权限不够", ERROR);
        return;
    }

    char username[20];
    char password[20];
    printf(INPUT_PROMPT COLOR_YELLOW "Please enter as required(请按要求输入):\n\n" COLOR_RESET);
    printf(INPUT_PROMPT COLOR_YELLOW "username(用户名):\n" COLOR_RESET);
    printf(INPUT_PROMPT);
    scanf("%s", username);
    printf(INPUT_PROMPT COLOR_YELLOW "password(密码):\n" COLOR_RESET);
    printf(INPUT_PROMPT);
    scanf("%s", password);
    printf(HEADER_LINE "\n");

    if (is_account_exist("account.txt", username, password))
    {
        Log("注册管理员时:用户名和密码已存在,注册失败", WARNING);
        return;
    }

    save_admin_to_file("account.txt", username, password);
}

void handle_delete_user()
{
    if (rank != 2 && rank != 3)
    {
        Log("注销user时:你的权限不够", ERROR);
        return;
    }

    char username[20];
    char password[20];
    printf(INPUT_PROMPT COLOR_YELLOW "Please enter as required(请按要求输入):\n\n" COLOR_RESET);
    printf(INPUT_PROMPT COLOR_YELLOW "username(用户名):\n" COLOR_RESET);
    printf(INPUT_PROMPT);
    scanf("%s", username);
    printf(INPUT_PROMPT COLOR_YELLOW "password(密码):\n" COLOR_RESET);
    printf(INPUT_PROMPT);
    scanf("%s", password);
    printf(HEADER_LINE "\n");

    int delrank = login("account.txt", username, password);
    if (delrank == 1)
    {
        delete_user_from_file("account.txt", username, password);
    }
    else if (delrank == 2 || delrank == 3)
    {
        Log("注销user时:你只能注销user", ERROR);
        return;
    }
    else if (delrank == 0)
    {
        Log("注销user时:未找到该user账号", ERROR);
    }
}

void handle_delete_admin()
{
    if (rank != 3)
    {
        Log("注销管理员时:你的权限不够", ERROR);
        return;
    }

    char username[20];
    char password[20];
    printf(INPUT_PROMPT COLOR_YELLOW "Please enter as required(请按要求输入):\n\n" COLOR_RESET);
    printf(INPUT_PROMPT COLOR_YELLOW "username(用户名):\n" COLOR_RESET);
    printf(INPUT_PROMPT);
    scanf("%s", username);
    printf(INPUT_PROMPT COLOR_YELLOW "password(密码):\n" COLOR_RESET);
    printf(INPUT_PROMPT);
    scanf("%s", password);
    printf(HEADER_LINE "\n");

    int delrank = login("account.txt", username, password);
    if (delrank == 2)
    {
        delete_admin_from_file("account.txt", username, password);
    }
    else if (delrank == 1 || delrank == 3)
    {
        Log("注销管理员时:你只能注销admin", ERROR);
        return;
    }
    else if (delrank == 0)
    {
        Log("注销管理员时:未找到该管理员账号", ERROR);
    }
}

void handle_quit() {}

void handle_student_score()
{

    int id;
    printf(INPUT_PROMPT COLOR_YELLOW "Please enter id(请输入学生ID): \n" COLOR_RESET);
    printf(INPUT_PROMPT);
    scanf("%d", &id);
    printf(HEADER_LINE "\n");

    if (!is_valid_student_id(id))
    {
        Log("统计某同学成绩时:ID结构不合法", ERROR);
        return;
    }

    Student *student = getStudent(school, id);
    if (student == NULL)
    {
        Log("统计某同学成绩时:学生未找到", ERROR);
        return;
    }
    else
    {
        printf("该学生成绩统计信息如下:\n");
    }

    printf("语文\t数学\t英语\t物理\t历史\t化学\t生物\t政治\t地理\t体育\t总分\t\n");

    for (int i = 0; i < 10; i++)
    {
        printf("%.2lf\t", student->score[i]);
    }

    printf("%.2lf\t", getStudentSum(student));

    printf("\n");
}

void handle_class_score()
{
    int gradeId, classId;
    printf(INPUT_PROMPT COLOR_YELLOW "请输入年级ID: \n" COLOR_RESET);
    printf(INPUT_PROMPT);
    scanf("%d", &gradeId);
    printf(INPUT_PROMPT COLOR_YELLOW "请输入班级ID: \n" COLOR_RESET);
    printf(INPUT_PROMPT);
    scanf("%d", &classId);
    printf(HEADER_LINE "\n");

    if (gradeId < 2024 || gradeId > 2027 || classId < 0 || classId > 20)
    {
        Log("统计班级成绩时:ID不合法", ERROR);
        return;
    }

    Class *cls = getClass(school, gradeId, classId);
    if (!cls)
    {
        Log("统计班级成绩时:未找到该班级", ERROR);
        return;
    }

    // 打印班级排行榜
    printf(COLOR_YELLOW "班级总分排行榜（降序）:\n" COLOR_RESET);
    printf("名次\tID\t姓名\t总分\n");
    Class *sorted = getSortedClassByTotalScore(cls);
    int rank_num = 1;
    for (int i = 0; i < sorted->size; i++)
    {
        Student *stu = sorted->students[i];
        if (stu && stu->indices.id != 0)
        {
            printf("%d\t%d\t%s\t%.2lf\n", rank_num++, stu->indices.id, stu->info.name, getStudentSum(stu));
        }
    }
    free(sorted->students);
    free(sorted);

    // 打印成绩统计表
    const char *subjects[10] = {"语文", "数学", "英语", "物理", "历史", "化学", "生物", "政治", "地理", "体育"};
    printf("\n\t");
    for (int i = 0; i < 10; i++)
        printf("%s\t", subjects[i]);
    printf("总分\n");

    // 最高分
    printf("最高分\t");
    for (int i = 0; i < 10; i++)
    {
        double max, min;
        getClassSubjectRange(cls, i, &max, &min);
        printf("%.2lf\t", max);
    }
    double maxTotal, minTotal;
    getClassTotalRange(cls, &maxTotal, &minTotal);
    printf("%.2lf\n", maxTotal);

    // 最低分
    printf("最低分\t");
    for (int i = 0; i < 10; i++)
    {
        double max, min;
        getClassSubjectRange(cls, i, &max, &min);
        printf("%.2lf\t", min);
    }
    getClassTotalRange(cls, &maxTotal, &minTotal);
    printf("%.2lf\n", minTotal);

    // 平均分
    printf("平均分\t");
    for (int i = 0; i < 10; i++)
    {
        double avg = getClassSubjectAvg(cls, i);
        printf("%.2lf\t", avg);
    }
    double avgTotal = getClassTotalAvg(cls);
    printf("%.2lf\n", avgTotal);
}