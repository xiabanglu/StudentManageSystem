#include "student.h"
#include <stdio.h>
#include <wchar.h>

//学生数组初始化
Student students[StudentMaxNum] = { { -1 } };

//计算学生数量
int CountStudentNum() {
    int count = 0;
    while (students[count].id != -1 && count < StudentMaxNum) count++;
    return count;
}

//从文件中加载学生信息
void LoadStudentFromFile() {
    for (int i = 0; i < StudentMaxNum; i++) students[i].id = -1;

    FILE* file;
    int count = 0;
    if (_wfopen_s(&file, L"学生用户信息.txt", L"r, ccs=UTF-8") != 0) return;

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
}

//保存学生信息到文件
void SaveStudentToFile() {
    FILE* file;
    int count = CountStudentNum();
    if (_wfopen_s(&file, L"学生用户信息.txt", L"w, ccs=UTF-8") != 0) return;
    for (int i = 0; i < count; i++) {
        fwprintf(file, L"%d,%ls,%ls,%ls,%ls,%ls,%ls,%ls\n",
            students[i].id, students[i].account, students[i].password,
            students[i].name, students[i].gender, students[i].age,
            students[i].grade, students[i].classNum);
    }
    fclose(file);
}
