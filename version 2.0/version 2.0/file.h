#ifndef FILE_H
#define FILE_H

#include "common.h"
#include "search.h"

// 函数声明
void loadStudentFromFile(const char *file_path, School *school);
void save_user_to_file(const char *file_path, char *username, char *password);
void delete_user_from_file(const char *file_path, char *username, char *password);
void save_admin_to_file(const char *file_path, char *username, const char *password);
void delete_admin_from_file(const char *file_path, char *username, char *password);
void save_student_to_file(const char *file_path, int id, Student *newStudent, double *score);
void delete_student_from_file(const char *file_path, int id);
void update_student_from_file(const char *file_path, int id, Student *newStudent, double *score);
int is_account_exist(const char *file_path, const char *username, const char *password);
int is_valid_student_info(int id, const char *name, const char *gender, int age, const char *schoolName, double *score);
int is_valid_student_id(int id);

#endif