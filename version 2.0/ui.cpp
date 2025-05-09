#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ui.h"
#include "admin.h"
#include "student.h"
#include "errorCode.h"

// 记录选择
Selections select;

// 登录检查
int LoginCheck(const char *username, const char *password)
{
    // 管理员
    for (int i = 0; i < ADMINMAXNUM && admins[i].id != -1; i++)
    {
        if (strcmp(username, admins[i].account.username) == 0 &&
            strcmp(password, admins[i].account.password) == 0)
            return 1;
    }
    // 学生
    for (int i = 0; i < STUDENTMAXNUM && students[i].id != -1; i++)
    {
        if (strcmp(username, students[i].account.username) == 0 &&
            strcmp(password, students[i].account.password) == 0)
            return 2;
    }
    // 未找到
    return 0;
}

// 欢迎主界面
void welcomeGraph()
{
    system("cls"); // 清屏
    printf(
        "欢迎使用学生成绩管理系统！\n\n"
        "请选择你的操作：\n\n"
        "+--------------+\n"
        "|              |\n"
        "|    1.登录    |\n"
        "|    2.注册    |\n"
        "|    3.退出    |\n"
        "|              |\n"
        "+--------------+\n\n");

    scanf_s("%d", &select.welcomeSelect);
    // 清除输入缓冲区的换行符
    int ch = getchar();
    (void)ch;

    switch (select.welcomeSelect)
    {
    case 1:
        loginInGraph();
        break;
    case 2:
        registerGraph();
        break;
    case 3:
        return;
    }
}

// 登录界面
void loginInGraph()
{
    // 当前登录信息
    char signInUsername[20];
    char signInPassword[20];

    system("cls"); // 清屏
    printf("请登录：\n");
    printf("请输入你的账号：\n");
    fgets(signInUsername, sizeof(signInUsername), stdin);
    printf("请输入你的密码：\n");
    fgets(signInPassword, sizeof(signInPassword), stdin);

    // 去掉换行符
    signInUsername[strcspn(signInUsername, "\n")] = '\0';
    signInPassword[strcspn(signInPassword, "\n")] = '\0';

    switch (LoginCheck(signInUsername, signInPassword))
    {
    case 1:
        adminGraph();
        break;
    case 2:
        studentGraph();
        break;
    case 0:
        printf("登录失败，请检查账号密码是否正确！\n");
    }
}

// 注册选择界面
void registerGraph()
{
    system("cls"); // 清屏
    printf(
        "你想要注册何种类型账号：\n\n"
        "请选择你的操作：\n\n"
        "+---------------+\n"
        "|               |\n"
        "|    1.管理员   |\n"
        "|    2.学生     |\n"
        "|    3.返回     |\n"
        "|               |\n"
        "+---------------+\n\n");
    scanf_s("%d", &select.registerSelect);

    // 清除输入缓冲区的换行符
    int ch = getchar();
    (void)ch;

    switch (select.registerSelect)
    {
    case 1:
        registerAdminGraph();
        break;
    case 2:
        registerStudentGraph();
        break;
    case 3:
        welcomeGraph();
        break;
    }
}

// 注册管理员界面
void registerAdminGraph()
{
    char registerAdminUsername[20];
    char registerAdminPassword[20];

    system("cls"); // 清屏
    printf("注册管理员账号：\n\n");
    printf("请输入你的账号：\n");
    fgets(registerAdminUsername, sizeof(registerAdminUsername), stdin);
    printf("请输入你的密码：\n");
    fgets(registerAdminPassword, sizeof(registerAdminPassword), stdin);
    // 去掉换行符
    registerAdminUsername[strcspn(registerAdminUsername, "\n")] = '\0';
    registerAdminPassword[strcspn(registerAdminPassword, "\n")] = '\0';

    // 尚未完成
    // test
    printf("test: 你输入的账号密码：%s %s\n", registerAdminUsername, registerAdminPassword);

    printf("注册成功！\n");
    printf("按任意键返回主界面...\n");
    int ch = getchar();
    (void)ch;
    welcomeGraph();
}

// 注册学生界面
void registerStudentGraph()
{
    char registerStudentUsername[20];
    char registerStudentPassword[20];

    system("cls"); // 清屏
    printf("注册学生账号：\n\n");
    printf("请输入你的账号：\n");
    fgets(registerStudentUsername, sizeof(registerStudentUsername), stdin);
    printf("请输入你的密码：\n");
    fgets(registerStudentPassword, sizeof(registerStudentPassword), stdin);
    // 去掉换行符
    registerStudentUsername[strcspn(registerStudentUsername, "\n")] = '\0';
    registerStudentPassword[strcspn(registerStudentPassword, "\n")] = '\0';

    // 尚未完成
    // test
    printf("test: 你输入的账号密码：%s %s\n", registerStudentUsername, registerStudentPassword);

    printf("注册成功！\n");
    printf("按任意键返回主界面...\n");
    int ch = getchar();
    (void)ch;
    welcomeGraph();
}

// 管理员操作界面
void adminGraph()
{
    system("cls"); // 清屏
    printf("欢迎管理员！\n\n");
    printf(
        "请选择你的操作：\n\n"
        "+-----------------------+\n"
        "|                       |\n"
        "|    1.录入学生成绩     |\n"
        "|    2.删除学生成绩     |\n"
        "|    3.修改学生成绩     |\n"
        "|    4.查看学生信息     |\n"
        "|    5.统计学生成绩     |\n"
        "|    6.修改我的信息     |\n"
        "|    7.注销我的账号     |\n"
        "|    8.返回             |\n"
        "|                       |\n"
        "+-----------------------+\n\n");
    scanf_s("%d", &select.adminSelect);

    // 清除输入缓冲区的换行符
    int ch = getchar();
    (void)ch;

    switch (select.adminSelect)
    {
    case 1:
        // 录入学生成绩
        printf("录入学生成绩功能尚未完成！\n");
        printf("按任意键返回主界面...\n");
        getchar();
        welcomeGraph();
        break;
    case 2:
        // 删除学生成绩
        printf("删除学生成绩功能尚未完成！\n");
        printf("按任意键返回主界面...\n");
        getchar();
        welcomeGraph();
        break;
    case 3:
        // 修改学生成绩
        printf("修改学生成绩功能尚未完成！\n");
        printf("按任意键返回主界面...\n");
        getchar();
        welcomeGraph();
        break;
    case 4:
        // 查看学生信息
        system("cls"); // 清屏
        printf("学生信息如下：\n\n");

        // 打印表头
        printf("ID\t姓名\t性别\t年龄\t年级\t班级\t学号\n");

        // 打印学生信息
        for (int i = 0; i < STUDENTMAXNUM; i++)
        {
            if (students[i].id == -1)
                break;
            printf("%d\t%s\t%s\t%s\t%s\t%s\t%s\n",
                   students[i].id,
                   students[i].info.name,
                   students[i].info.gender,
                   students[i].info.age,
                   students[i].info.grade,
                   students[i].info.classNum,
                   students[i].info.stuNum);
        }

        printf("按任意键返回主界面...\n");
        getchar();
        welcomeGraph();
        break;

    case 5:
        // 统计学生成绩
        system("cls"); // 清屏
        printf("学生成绩如下：\n\n");

        // 打印表头
        printf("ID\t姓名\t高数\t线代\t程设\t概率论\t离散\t数据库\t计网\t操系\t计组\t算法\n");

        // 打印学生信息
        for (int i = 0; i < STUDENTMAXNUM; i++)
        {
            if (students[i].id == -1)
                break;
            printf("%d\t%s\t%.1f\t%.1f\t%.1f\t%.1f\t%.1f\t%.1f\t%.1f\t%.1f\t%.1f\t%.1f\n",
                   students[i].id,
                   students[i].info.name,
                   students[i].score.advancedMath,
                   students[i].score.linearAlgebra,
                   students[i].score.programming,
                   students[i].score.probability,
                   students[i].score.discreteMath,
                   students[i].score.database,
                   students[i].score.computerNetwork,
                   students[i].score.operatingSystem,
                   students[i].score.computerOrganization,
                   students[i].score.dataStructureAndAlgorithm);
        }
        printf("按任意键返回主界面...\n");
        getchar();
        welcomeGraph();
        break;
    case 6:
        // 修改我的信息
        printf("修改我的信息功能尚未完成！\n");
        printf("按任意键返回主界面...\n");
        getchar();
        welcomeGraph();
        break;
    case 7:
        // 注销我的账号
        printf("注销我的账号功能尚未完成！\n");
        printf("按任意键返回主界面...\n");
        getchar();
        welcomeGraph();
        break;
    case 8:
        welcomeGraph();
        break;
    }
}

// 学生操作界面
void studentGraph()
{
    system("cls"); // 清屏
    printf("欢迎学生！\n\n");
    printf(
        "请选择你的操作：\n\n"
        "+-----------------------+\n"
        "|                       |\n"
        "|    1.查看我的成绩     |\n"
        "|    2.修改我的信息     |\n"
        "|    3.注销我的账号     |\n"
        "|    4.返回             |\n"
        "|                       |\n"
        "+-----------------------+\n\n");
    scanf_s("%d", &select.studentSelect);

    // 清除输入缓冲区的换行符
    int ch = getchar();
    (void)ch;

    switch (select.studentSelect)
    {
    case 1:
        // 查看我的成绩
        printf("查看我的成绩功能尚未完成！\n");
        printf("按任意键返回主界面...\n");
        getchar();
        welcomeGraph();
        break;
    case 2:
        // 修改我的信息
        printf("修改我的信息功能尚未完成！\n");
        printf("按任意键返回主界面...\n");
        getchar();
        welcomeGraph();
        break;
    case 3:
        // 注销我的账号
        printf("注销我的账号功能尚未完成！\n");
        printf("按任意键返回主界面...\n");
        getchar();
        welcomeGraph();
        break;
    case 4:
        welcomeGraph();
        break;
    }
}
