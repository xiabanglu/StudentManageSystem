#include "admin.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "errorcode.h"

#define _CRT_SECURE_NO_WARNINGS

// 管理员数组初始化
Admin admins[ADMINMAXNUM] = { { -1 } };

// 计算管理员数量
int countAdminNum() {
    int count = 0;
    while (admins[count].id != -1 && count < ADMINMAXNUM) count++;
    return count;
}

// 从文件中加载管理员信息
int loadAdminFromFile() {
    // 初始化缓存
    for (int i = 0; i < ADMINMAXNUM; i++) admins[i].id = -1;

    FILE* file;
    const char* fileName = "adminInfo.txt";
    const char* mode = "r";

    int error = fopen_s(&file, fileName, mode);
    // 文件读写错误
    if (error != 0) {
        printf("failed to open file: %s\n", fileName);
        // 标准错误码
        return FILE_IS_NULL_CODE;
    }

	//加载管理员信息
    int count = 0;
    char buffer[256];
    while (count < ADMINMAXNUM && fgets(buffer, 256, file)) {
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') buffer[--len] = '\0';
        if (len > 0 && buffer[len - 1] == '\r') buffer[--len] = '\0';

        if (sscanf_s(buffer, "%d,%19[^,],%19[^,\r\n]",
            &admins[count].id,
            admins[count].account, (unsigned)_countof(admins[count].account),
            admins[count].password, (unsigned)_countof(admins[count].password)) == 3) {
            count++;
        }
    }
    if (count < ADMINMAXNUM) admins[count].id = -1;
    fclose(file);
    return SUCCESS_LOAD_ADMIN_FILE_CODE;
}

// 保存管理员信息到文件
int saveAdminToFile() {
    FILE* file;
    int count = countAdminNum();

    const char* fileName = "adminInfo.txt";
    const char* mode = "w";
    int error = fopen_s(&file, fileName, mode);
    // 文件读写错误
    if (error != 0) {
        printf("failed to open file: %s\n", fileName);
        // 标准错误码
        return FILE_IS_NULL_CODE;
    }

    for (int i = 0; i < count; i++) {
        fprintf(file, "%d,%s,%s\n",
            admins[i].id, admins[i].account, admins[i].password);
    }
    if (file != 0)
        fclose(file);

    return SUCCESS_SAVE_ADMIN_CODE;
}
