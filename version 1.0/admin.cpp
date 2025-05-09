#define _CRT_SECURE_NO_WARNINGS
#include "admin.h"
#include <stdio.h>
#include <wchar.h>
#include "errorCode.cpp"
//管理员数组初始化
Admin admins[AdminMaxNum] = { { -1 } };


//计算管理员数量
//最终返回下标
int CountAdminNum() {
    int count = 0;
    while (admins[count].id != -1 && count < AdminMaxNum) count++;
    return count;
}

//从文件中加载管理员信息
//返回值是函数是否初始化
int LoadAdminFromFile() {
    
    //初始化缓存
    for (int i = 0; i < AdminMaxNum; i++) admins[i].id = -1;

    FILE *file;
    const wchar_t *fileName = L"管理员信息.txt";
    const wchar_t *mode = L"r,ccs=UTF-8";

    int error= _wfopen_s(&file,fileName, mode);
    //文件读写错误
    if (file !=0) {
        wprintf(L"failed to open file:%ls\n", fileName);
        //标准错误码
        return FILE_IS_NULL_CODE;

    }
    int count = 0;
   
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
    return SUCCESS_LOAD_ADMIN_FILE_CODE;
}

//保存管理员信息到文件
int SaveAdminToFile() {
    FILE* file;
    int count = CountAdminNum();

    FILE* file;
    const wchar_t* fileName = L"管理员信息.txt";
    const wchar_t* mode = L"r,ccs=UTF-8";
    int error = _wfopen_s(&file, fileName, mode);
    //文件读写错误
    if (error != 0) {
        wprintf(L"failed to open file:%ls\n", fileName);
        //标准错误码
        return FILE_IS_NULL_CODE;

    }
   
    for (int i = 0; i < count; i++) {
        fwprintf(file, L"%d,%ls,%ls\n",
            admins[i].id, admins[i].account, admins[i].password);
    }
    if(file!=0)
    fclose(file);

    return SUCCESS_SAVE_ADMIN_CODE;


}


