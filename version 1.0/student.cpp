#include "student.h"
#include <stdio.h>
#include <wchar.h>
#include "errorCode.cpp"

//学生数组初始化
Student students[StudentMaxNum] = { { -1 } };

//计算学生数量
//返回的是下标
int CountStudentNum() {
    int count = 0;
    while (students[count].id != -1 && count < StudentMaxNum) count++;
    return count;
}

//从文件中加载学生信息
int LoadStudentFromFile() {
    for (int i = 0; i < StudentMaxNum; i++) students[i].id = -1;
    FILE* file;
    const wchar_t* fileName = L"学生用户信息.txt";
    const wchar_t* mode = L"r,ccs=UTF-8";

    int error= _wfopen_s(&file,fileName, mode);
    //文件读写错误
    if (error!=0) {
        wprintf(L"failed to open file:%ls\n", fileName);
        //标准错误码
        return FILE_IS_NULL_CODE;

    }
   
    int count = 0;
    
    wchar_t buffer[512];
    while (count < StudentMaxNum && fgetws(buffer, 512, file)) {
        size_t len = wcslen(buffer);
        if (len > 0 && buffer[len - 1] == L'\n') buffer[--len] = L'\0';
        if (len > 0 && buffer[len - 1] == L'\r') buffer[--len] = L'\0';

        if (swscanf_s(buffer,
            L"%d,%19[^,],%19[^,],%19[^,],%19[^,],%19[^,],%19[^,],%19[^,]",
            &students[count].id,
            students[count].account, 20,
            students[count].password, 20,
            students[count].name, 20,
            students[count].gender, 20,
            students[count].age, 20,
            students[count].grade, 20,
            students[count].classNum, 20) == 8) {
            count++;
        }
    }
    if (count < StudentMaxNum) students[count].id = -1;
    fclose(file);

    return SUCCESS_LOAD_STUDENT_CODE;
}

//保存学生信息到文件
int SaveStudentToFile() {
    FILE* file;
    const wchar_t* fileName = L"学生用户信息.txt";
    const wchar_t* mode = L"r,ccs=UTF-8";

    int error = _wfopen_s(&file, fileName, mode);
    //文件读写错误
    if (error != 0) {
        wprintf(L"failed to open file:%ls\n", fileName);
        //标准错误码
        return FILE_IS_NULL_CODE;

    }
    int count = CountStudentNum();
   
    for (int i = 0; i < count; i++) {
        fwprintf(file, L"%d,%ls,%ls,%ls,%ls,%ls,%ls,%ls\n",
            students[i].id, students[i].account, students[i].password,
            students[i].name, students[i].gender, students[i].age,
            students[i].grade, students[i].classNum);
    }
    fclose(file);
    return  SUCCESS_SAVE_STUDENT_CODE;
}
