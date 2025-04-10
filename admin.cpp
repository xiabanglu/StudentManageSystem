#include "admin.h"
#include <stdio.h>
#include <wchar.h>

//管理员数组初始化
Admin admins[AdminMaxNum] = { { -1 } };

//计算管理员数量
int CountAdminNum() {
    int count = 0;
    while (admins[count].id != -1 && count < AdminMaxNum) count++;
    return count;
}

//从文件中加载管理员信息
void LoadAdminFromFile() {
    for (int i = 0; i < AdminMaxNum; i++) admins[i].id = -1;

    FILE* file;
    int count = 0;
    if (_wfopen_s(&file, L"管理员信息.txt", L"r, ccs=UTF-8") != 0) return;

    wchar_t buffer[256];
    while (count < AdminMaxNum && fgetws(buffer, 256, file)) {
        size_t len = wcslen(buffer);
        if (len > 0 && buffer[len - 1] == L'\n') buffer[--len] = L'\0';
        if (len > 0 && buffer[len - 1] == L'\r') buffer[--len] = L'\0';

        if (swscanf_s(buffer, L"%d,%19[^,],%19[^,\r\n]",
            &admins[count].id,
            admins[count].account, 20,
            admins[count].password, 20) == 3) {
            count++;
        }
    }
    if (count < AdminMaxNum) admins[count].id = -1;
    fclose(file);
}

//保存管理员信息到文件
void SaveAdminToFile() {
    FILE* file;
    int count = CountAdminNum();
    if (_wfopen_s(&file, L"管理员信息.txt", L"w, ccs=UTF-8") != 0) return;
    for (int i = 0; i < count; i++) {
        fwprintf(file, L"%d,%ls,%ls\n",
            admins[i].id, admins[i].account, admins[i].password);
    }
    fclose(file);
}


