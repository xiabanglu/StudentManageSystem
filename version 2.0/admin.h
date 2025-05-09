#ifndef ADMIN_H
#define ADMIN_H

// 管理员最大数量
#define ADMINMAXNUM 50

// 管理员结构体
typedef struct Admin
{
    int id;
    char account[20];
    char password[20];
} Admin;

// 管理员数组
extern Admin admins[ADMINMAXNUM];

//函数声明
int countAdminNum();
int loadAdminFromFile();
int saveAdminToFile();

#endif // ADMIN_H
