#ifndef __MENU_H__
#define __MENU_H__

int flag = 0; // 用户标志

#include "event.h"
#include "search.h"
#include <stdio.h>
#include <stdlib.h>

School *school = NULL; // 学校实例

// 菜单类型的枚举
typedef enum MenuType
{
    MENU_LOGIN, // 登录菜单
    MENU_SHOW, // 显示菜单
} MenuType;

// 菜单结构体
typedef struct Menu
{
    const char *show; // 菜单显示内容
    Event *event; // 菜单事件
    MenuType type; // 菜单类型
} Menu;

// 显示菜单选项
const char *show_menu[] = {
    "i - insert new record", // 插入新记录
    "d - delete record", // 删除记录
    "u - update record", // 更新记录
    "f - find record", // 查找记录
    "q - quit", // 退出
    NULL};

// 登录菜单选项
const char *login_menu[] = {
    "l - student login", // 学生登录
    "r - register", // 注册
    "k - delete user", // 删除用户
    NULL};

// 创建显示菜单的函数
Menu *create_show_menu()
{
    Menu *menu = (Menu *)malloc(sizeof(Menu)); // 分配菜单内存
    menu->show = "Show Menu"; // 设置菜单显示内容
    menu->event = (Event *)malloc(sizeof(Event) * 3); // 分配事件内存
    menu->event[0].event_type = EVENT_REGISTER_STUDENT; // 注册学生事件
    menu->event[1].event_type = EVENT_DELETE_STUDENT; // 删除学生事件
    menu->event[2].event_type = EVENT_UPDATE_STUDENT; // 更新学生事件

    for (int i = 0; i < 3; i++)
    {
        registerEvent(&menu->event[i], menu->event[i].event_type); // 注册事件
    }
    menu->type = MENU_SHOW; // 设置菜单类型
    return menu; // 返回菜单
}

// 创建登录菜单的函数
Menu *create_login_menu()
{
    Menu *menu = (Menu *)malloc(sizeof(Menu)); // 分配菜单内存
    menu->show = "Login Menu"; // 设置菜单显示内容
    menu->event = (Event *)malloc(sizeof(Event) * 3); // 分配事件内存

    menu->event[0].event_type = EVENT_LOGIN_USER; // 登录用户事件
    menu->event[1].event_type = EVENT_REGISTER_USER; // 注册用户事件
    menu->event[2].event_type = EVENT_DELETE_USER; // 删除用户事件

    for (int i = 0; i < 3; i++)
    {
        registerEvent(&menu->event[i], menu->event[i].event_type); // 注册事件
    }

    menu->type = MENU_LOGIN; // 设置菜单类型
    return menu; // 返回菜单
}

// 获取用户选择的函数
char getchoice(const char *greet, const char *choices[])
{
    short chosen = 0; // 选择标志
    char selected; // 用户选择
    const char **option;
    do
    {
        printf("\033[1;32m-------------------------\033[0m\n");
        printf("Menu: %s\n", greet); // 打印菜单标题
        option = choices;

        while (*option) // 打印菜单选项
        {
            printf("%s\n", *option);
            option++;
        }

        selected = getchar(); // 获取用户输入
        while (selected == '\n') // 处理换行符
        {
            selected = getchar();
        }
        while (getchar() != '\n')
            ; // 清空输入缓冲区

        option = choices;
        while (*option) // 检查用户选择是否有效
        {
            if (selected == *option[0])
            {
                chosen = 1; // 标记选择有效
                break;
            }
            option++;
        }
        if (!chosen) // 如果选择无效，提示用户
        {
            printf("Incorrect choice, select again\n");
        }
    } while (!chosen); // 直到选择有效为止
    return selected; // 返回用户选择
}

// 事件循环处理函数
void event_loop(Menu *menu, int *is_quit)
{
    int selected; // 用户选择
    int id; // 学生ID
    char name[10]; // 学生姓名
    int age; // 学生年龄
    float score[7]; // 学生成绩
    char password[20]; // 用户密码
    do
    {
        switch (menu->type) // 根据菜单类型处理事件
        {
        case MENU_LOGIN:
            selected = getchoice("Login Menu", login_menu); // 获取登录菜单选择
            break;
        case MENU_SHOW:
            selected = getchoice("Show Menu", show_menu); // 获取显示菜单选择
            break;
        default:
            printf("Invalid menu type\n"); // 无效菜单类型
            return;
        }
        printf("\033[1;32m-------------------------\033[0m\n");
        switch (selected) // 根据用户选择执行相应操作
        {
        case 'l': // 登录
            printf("User login\n");
            printf("Enter ID and password:\n");
            scanf("%d", &id); // 输入用户ID
            scanf("%s", password); // 输入用户密码
            flag = menu->event[0].callback.login("user.txt", id, password); // 调用登录回调
            if (flag) // 登录成功
            {
                printf("Login successful! %d\n", flag);
                *is_quit = 1; // 设置退出标志
                return;
            }
            else // 登录失败
            {
                printf("Login failed!\n");
            }
            break;
        case 'r': // 注册
            printf("Register\n");
            printf("Enter ID and password:\n");
            scanf("%d", &id); // 输入用户ID
            scanf("%s", password); // 输入用户密码
            menu->event[1].callback.registerUser("user.txt", id, password); // 调用注册回调
            break;
        case 'k': // 删除用户
            printf("Delete user\n");
            printf("Enter ID:\n");
            scanf("%d", &id); // 输入用户ID
            menu->event[2].callback.deleteUser("user.txt", id); // 调用删除用户回调
            break;
        case 'i': // 插入新记录
        {
            if (flag == 1) // 检查用户是否为管理员
            {
                printf("\033[31mYou are not logged in as admin\033[0m\n");
                break;
            }
            printf("Insert new record\n");
            printf("Enter student ID, name, age and scores(7):\n");
            scanf("%d", &id); // 输入学生ID
            scanf("%s", name); // 输入学生姓名
            scanf("%d", &age); // 输入学生年龄

            for (int i = 0; i < 7; i++) // 输入学生成绩
            {
                scanf("%f", &score[i]);
            }
            menu->event[0].callback.registerStudent(school, id, name, age, score); // 调用注册学生回调
            break;
        }
        case 'd': // 删除记录
        {
            if (flag == 1) // 检查用户是否为管理员
            {
                printf("\033[31mYou are not logged in as admin\033[0m\n");
                break;
            }
            printf("Delete record\n");
            printf("Enter student ID:\n");
            scanf("%d", &id); // 输入学生ID
            menu->event[1].callback.deleteStudent(school, id); // 调用删除学生回调
            break;
        }
        case 'u': // 更新记录
        {
            if (flag == 1) // 检查用户是否为管理员
            {
                printf("\033[31mYou are not logged in as admin\033[0m\n");
                break;
            }
            printf("Update record\n");
            printf("Enter student ID, name, age and scores(7):\n");

            scanf("%d", &id); // 输入学生ID
            scanf("%s", name); // 输入学生姓名
            scanf("%d", &age); // 输入学生年龄
            for (int i = 0; i < 7; i++) // 输入学生成绩
            {
                scanf("%f", &score[i]);
            }
            menu->event[2].callback.updateStudent(school, id, name, age, score); // 调用更新学生回调
            break;
        }
        case 'q': // 退出
            printf("Quit\n");
            *is_quit = 1; // 设置退出标志
            break;
        case 'f': // 查找学生
        {
            printf("Find student\n");
            printf("Enter student ID:\n");
            scanf("%d", &id); // 输入学生ID
            Student **student = getStudent(school, id); // 获取学生信息
            if (student != NULL) // 如果找到学生
            {
                printf("Student found: %s, %d\n", (*student)->name, (*student)->age); // 打印学生信息
            }
            else // 如果未找到学生
            {
                printf("\033[31mStudent not found\033[0m\n");
            }
            break;
        }
        default: // 无效选择
            printf("Invalid choice\n");
            break;
        }
        printf("\033[1;32m-------------------------\033[0m\n");
    } while (selected != 'q'); // 直到选择退出为止
}

#endif // __MENU_H__