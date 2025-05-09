#ifndef ADMIN_H
#define ADMIN_H

//管理员最大数量
#define AdminMaxNum 20

//管理员结构体
typedef struct Admin {
    int id;
    wchar_t account[20];
    wchar_t password[20];
} Admin;

//管理员数组
extern Admin admins[AdminMaxNum];

//管理员函数声明
int LoadAdminFromFile();
int SaveAdminToFile();
int CountAdminNum();

#endif // ADMIN_H
