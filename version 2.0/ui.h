#ifndef UI_H
#define UI_H

// 操作选择
typedef struct Selections
{
    int welcomeSelect;
    int loginSelect;
    int registerSelect;
    int adminSelect;
    int studentSelect;
} Selections;

// ui函数声明
void welcomeGraph();
void loginInGraph();
void registerGraph();
void registerAdminGraph();
void registerStudentGraph();
void adminGraph();
void studentGraph();

#endif // UI_H
