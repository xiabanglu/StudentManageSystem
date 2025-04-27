#include "ui.h"
#include "student.h"
#include "admin.h"
#include "graphics_utils.h"
#include <graphics.h>
#include <wchar.h>
#include <locale.h>

//记录以何种身份登录
int flag = 0;//1表示管理员，2表示学生

//记录当前账号
Admin currentAdmin;
Student currentStudent;

//登录检查
int LoginCheck(const wchar_t* username, const wchar_t* password) {
    //管理员
    for (int i = 0; i < AdminMaxNum && admins[i].id != -1; i++) {
        if (wcscmp(username, admins[i].account) == 0 &&
            wcscmp(password, admins[i].password) == 0) return 1;
    }
	//学生
    for (int i = 0; i < StudentMaxNum && students[i].id != -1; i++) {
        if (wcscmp(username, students[i].account) == 0 &&
            wcscmp(password, students[i].password) == 0) return 2;
    }
	//未找到
    return 0; 
}

//管理员界面
void AdminManageGraph() {
	flag = 1;
	cleardevice();
	LoadBgk();
    SetHeightText(30);
    RECT r = { 0, 0, 800, 150 };
    drawtext(L"欢迎进入学生管理系统(管理员权限)",&r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

    //绘制按钮
    const int btnWidth = 200, btnHeight = 50;
    const int btnX = 300;
    DrawButton(btnX, 130, btnWidth, btnHeight, _T("录入学生信息"),30);
    DrawButton(btnX, 200, btnWidth, btnHeight, _T("删除学生信息"),30);
    DrawButton(btnX, 270, btnWidth, btnHeight, _T("查看学生信息"),30);
    DrawButton(btnX, 340, btnWidth, btnHeight, _T("修改学生信息"),30);
    DrawButton(btnX, 410, btnWidth, btnHeight, _T("注销我的账号"),30);
	DrawButton(btnX, 480, btnWidth, btnHeight, _T("返回"), 30);

	//点击事件处理
    while (true) {
        MOUSEMSG msg = GetMouseMsg();
        if (msg.uMsg == WM_LBUTTONDOWN) {
			//录入学生信息
            if (IsMouseInRect(btnX, 130, btnWidth, btnHeight)) {
                int studentNum = CountStudentNum();

				//检查学生数量
                if (studentNum >= StudentMaxNum) {
                    MessageBox(NULL, _T("学生数量已达上限"), _T("错误"), MB_OK);
                    continue;
                }

                Student newStudent;


                //用户名
                InputBox(newStudent.account, MAX_STRING_LENGTH, _T("请输入用户名:"), _T("添加学生信息（最多6个字符）"), NULL);
                //不能为空
				if (wcslen(newStudent.account) == 0) {
					MessageBox(NULL, _T("不能为空"), _T("错误"), MB_OK);
					continue;
				}
				//不能包含逗号
				if (wcschr(newStudent.account, L',')) {
					MessageBox(NULL, _T("用户名不能包含逗号"), _T("错误"), MB_OK);
					continue;
				}
				//不能重复
				for (int i = 0; i < StudentMaxNum; i++) {
					if (wcscmp(newStudent.account, students[i].account) == 0) {
						MessageBox(NULL, _T("用户名已存在，请重新输入"), _T("错误"), MB_OK);
						continue;
					}
				}


                //密码
                InputBox(newStudent.password, MAX_STRING_LENGTH, _T("请输入密码:"), _T("添加学生信息（最多6个字符）"), NULL);
                //不能为空
                if (wcslen(newStudent.password) == 0) {
                    MessageBox(NULL, _T("不能为空"), _T("错误"), MB_OK);
                    continue;
                }
				//不能包含逗号
				if (wcschr(newStudent.password, L',')) {
					MessageBox(NULL, _T("密码不能包含逗号"), _T("错误"), MB_OK);
					continue;
				}
				//不能重复
				for (int i = 0; i < StudentMaxNum; i++) {
					if (wcscmp(newStudent.password, students[i].password) == 0) {
						MessageBox(NULL, _T("密码已存在，请重新输入"), _T("错误"), MB_OK);
						continue;
					}
				}


				//姓名
                InputBox(newStudent.name, MAX_STRING_LENGTH, _T("请输入姓名:"), _T("添加学生信息（最多6个字符）"), NULL);
                //不能为空
                if (wcslen(newStudent.name) == 0) {
                    MessageBox(NULL, _T("不能为空"), _T("错误"), MB_OK);
                    continue;
                }
				//不能包含逗号
				if (wcschr(newStudent.name, L',')) {
					MessageBox(NULL, _T("姓名不能包含逗号"), _T("错误"), MB_OK);
					continue;
				}


				//性别
                InputBox(newStudent.gender, MAX_STRING_LENGTH, _T("请输入性别:"), _T("添加学生信息（最多6个字符）"), NULL);
                //不能为空
                if (wcslen(newStudent.gender) == 0) {
                    MessageBox(NULL, _T("不能为空"), _T("错误"), MB_OK);
                    continue;
                }
                //不能包含逗号
                if (wcschr(newStudent.gender, L',')) {
                    MessageBox(NULL, _T("性别不能包含逗号"), _T("错误"), MB_OK);
                    continue;
                }


				//年龄
                InputBox(newStudent.age, MAX_STRING_LENGTH, _T("请输入年龄:"), _T("添加学生信息（最多6个字符）"), NULL);
                //不能为空
                if (wcslen(newStudent.age) == 0) {
                    MessageBox(NULL, _T("不能为空"), _T("错误"), MB_OK);
                    continue;
                }
				//不能包含逗号
				if (wcschr(newStudent.age, L',')) {
					MessageBox(NULL, _T("年龄不能包含逗号"), _T("错误"), MB_OK);
					continue;
				}


				//年级
                InputBox(newStudent.grade, MAX_STRING_LENGTH, _T("请输入年级:"), _T("添加学生信息（最多6个字符）"), NULL);
                //不能为空
                if (wcslen(newStudent.grade) == 0) {
                    MessageBox(NULL, _T("不能为空"), _T("错误"), MB_OK);
                    continue;
                }
				//不能包含逗号
				if (wcschr(newStudent.grade, L',')) {
					MessageBox(NULL, _T("年级不能包含逗号"), _T("错误"), MB_OK);
					continue;
				}


				//班级
                InputBox(newStudent.classNum, MAX_STRING_LENGTH, _T("请输入班级:"), _T("添加学生信息（最多6个字符）"), NULL);
                //不能为空
                if (wcslen(newStudent.classNum) == 0) {
                    MessageBox(NULL, _T("不能为空"), _T("错误"), MB_OK);
                    continue;
                }
				//不能包含逗号
				if (wcschr(newStudent.classNum, L',')) {
					MessageBox(NULL, _T("班级不能包含逗号"), _T("错误"), MB_OK);
					continue;
				}


                newStudent.id = studentNum;

                students[studentNum] = newStudent;

                // 重新分配学生ID
                for (int i = 0; i <= studentNum; i++) {
                    students[i].id = i;
                }

                SaveStudentToFile();
                MessageBox(NULL, _T("录入成功"), _T("提示"), MB_OK);
            }
            //删除学生信息
            else if (IsMouseInRect(btnX, 200, btnWidth, btnHeight)) {
				int studentNum = CountStudentNum();

				//检查学生数量
                if (studentNum == 0) {
                    MessageBox(NULL, _T("没有学生信息可删除"), _T("错误"), MB_OK);
                    continue;
                }

				//按照用户名删除学生信息
                wchar_t DelStudentAccount[MAX_STRING_LENGTH];

                InputBox(DelStudentAccount, MAX_STRING_LENGTH, _T("请输入要删除的学生的用户名:"), _T("删除学生信息（最多6个字符）"), NULL);
                //不能为空
                if (wcslen(DelStudentAccount) == 0) {
                    MessageBox(NULL, _T("不能为空"), _T("错误"), MB_OK);
                    continue;
                }
				//不能包含逗号
				if (wcschr(DelStudentAccount, L',')) {
					MessageBox(NULL, _T("用户名不能包含逗号"), _T("错误"), MB_OK);
					continue;
				}

                bool studentFound = false;
                for (int i = 0; i < StudentMaxNum && students[i].id != -1; i++) {
                    if (wcscmp(DelStudentAccount, students[i].account) == 0) {
                        studentFound = true;
                        
                        for (int j = i; j < StudentMaxNum - 1; j++) {
                            students[j] = students[j + 1];
                        }
                        students[--studentNum].id = -1;

                        // 重新分配学生ID
                        for (int i = 0; i < studentNum; i++) {
                            students[i].id = i;
                        }

                        SaveStudentToFile();
                        MessageBox(NULL, _T("删除成功"), _T("提示"), MB_OK);
                        break;
                    }
                }

                if (!studentFound) {
                    MessageBox(NULL, _T("未找到该学生账号"), _T("错误"), MB_OK);
                }
            }
            //查看学生信息
            else if (IsMouseInRect(btnX, 270, btnWidth, btnHeight)) {
				ViewStudentInfoGraph();
                return;
            }
			//修改学生信息
            else if (IsMouseInRect(btnX, 340, btnWidth, btnHeight)) {

				bool studentFound = false;
				InputBox(currentStudent.account, MAX_STRING_LENGTH, _T("请输入要修改的学生的用户名:"), _T("修改学生信息（最多6个字符）"), NULL);
				//不能为空
                if (wcslen(currentStudent.account) == 0) {
                    MessageBox(NULL, _T("不能为空"), _T("错误"), MB_OK);
                    continue;
                }
				//不能包含逗号
                if (wcschr(currentStudent.account, L',')) {
                    MessageBox(NULL, _T("用户名不能包含逗号"), _T("错误"), MB_OK);
                    continue;
                }

                for (int i = 0;i < StudentMaxNum && students[i].id != -1;i++) {
                    if (wcscmp(currentStudent.account, students[i].account) == 0) {
                        studentFound = true;
                        currentStudent = students[i];
                        ModifyStudentInfoGraph();
                        return;
                    }
                }
				if (!studentFound) {
					MessageBox(NULL, _T("未找到该学生账号"), _T("错误"), MB_OK);
					continue;
				}
            }
			//注销我的账号
			else if (IsMouseInRect(btnX, 410, btnWidth, btnHeight)) {
				int adminNum = CountAdminNum();

				for (int i = 0; i < AdminMaxNum; i++) {
					if (wcscmp(admins[i].account, currentAdmin.account) == 0 && wcscmp(admins[i].password, currentAdmin.password) == 0) {
						for (int j = i; j < AdminMaxNum - 1; j++) {
							admins[j] = admins[j + 1];
						}
						admins[--adminNum].id = -1;

						// 重新分配管理员ID
						for (int i = 0; i < adminNum; i++) {
							admins[i].id = i;
						}

						SaveAdminToFile();
						MessageBox(NULL, _T("注销成功"), _T("提示"), MB_OK);
						WelcomeGraph();
						return;
					}
				}
			}
			//返回
            else if (IsMouseInRect(btnX, 480, btnWidth, btnHeight)) {
                WelcomeGraph();
                return;
            }
        }
    }
}

//学生界面
void StudentManageGraph() {
    flag = 2;
	cleardevice();
	LoadBgk();
    SetHeightText(30);
    RECT r = { 0, 0, 800, 150 };
    drawtext(L"欢迎进入学生管理系统(学生权限)", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

    const int btnWidth = 200, btnHeight = 50;
    const int btnX = 300;
    DrawButton(btnX, 200, btnWidth, btnHeight, _T("查看我的信息"),30);
    DrawButton(btnX, 270, btnWidth, btnHeight, _T("修改我的信息"),30);
    DrawButton(btnX, 340, btnWidth, btnHeight, _T("注销我的账号"),30);
	DrawButton(btnX, 410, btnWidth, btnHeight, _T("返回"),30);

    while (true) {
        MOUSEMSG msg = GetMouseMsg();
        if (msg.uMsg == WM_LBUTTONDOWN) {
			//查看我的信息
            if (IsMouseInRect(btnX, 200, btnWidth, btnHeight)) {
                cleardevice();
                LoadBgk();

                SetHeightText(25);
                settextcolor(BLACK);

                // 表头定义
                const TCHAR* headers[] = { _T("ID"), _T("账号"), _T("密码"), _T("姓名"), _T("性别"), _T("年龄"), _T("年级"), _T("班级") };
                const int numCols = sizeof(headers) / sizeof(headers[0]);

                // 计算表格位置（居中显示）
                const int tableX = 0;
                const int tableY = 200;
                const int cellWidth = 100;
                const int cellHeight = 40;
                const int tableWidth = cellWidth * numCols;
                const int tableHeight = cellHeight * 2; // 2行

                // 绘制表头（带背景色）
                setfillcolor(RGB(200, 230, 255));
                for (int col = 0; col < numCols; col++) {
                    RECT rHeader = {
                        tableX + col * cellWidth,
                        tableY,
                        tableX + (col + 1) * cellWidth,
                        tableY + cellHeight
                    };
                    fillrectangle(rHeader.left, rHeader.top, rHeader.right, rHeader.bottom);
                    drawtext(headers[col], &rHeader, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
                }

                // 绘制表格线
                setlinecolor(BLACK);
                for (int row = 0; row <= 2; row++) {
                    line(
                        tableX,
                        tableY + row * cellHeight,
                        tableX + tableWidth,
                        tableY + row * cellHeight
                    );
                }
                for (int col = 0; col <= numCols; col++) {
                    line(
                        tableX + col * cellWidth,
                        tableY,
                        tableX + col * cellWidth,
                        tableY + tableHeight
                    );
                }

                // 填充数据（居中显示）
                wchar_t idStr[20];
                swprintf_s(idStr, L"%d", currentStudent.id);

                const wchar_t* fields[] = {
                    idStr,
                    currentStudent.account,
                    currentStudent.password,
                    currentStudent.name,
                    currentStudent.gender,
                    currentStudent.age,
                    currentStudent.grade,
                    currentStudent.classNum
                };

                // 绘制每列数据（居中）
                for (int col = 0; col < numCols; col++) {
                    RECT rCell = {
                        tableX + col * cellWidth,
                        tableY + cellHeight,
                        tableX + (col + 1) * cellWidth,
                        tableY + 2 * cellHeight
                    };
                    drawtext(fields[col], &rCell, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
                }

                // 返回按钮（右上角）
                DrawButton(tableX + tableWidth - btnWidth, 500, btnWidth, btnHeight, _T("返回"), 30);

                // 事件处理
                while (true) {
                    MOUSEMSG msg = GetMouseMsg();
                    if (msg.uMsg == WM_LBUTTONDOWN) {
                        if (IsMouseInRect(tableX + tableWidth - btnWidth, 500, btnWidth, btnHeight)) {
                            StudentManageGraph();
                            return;
                        }
                    }
                }
            }
			//修改我的信息
            else if (IsMouseInRect(btnX, 270, btnWidth, btnHeight)) {
				ModifyStudentInfoGraph();
				return;
            }
			//注销我的账号
			else if (IsMouseInRect(btnX, 340, btnWidth, btnHeight)) {
				int studentNum = CountStudentNum();

				for (int i = 0; i < StudentMaxNum; i++) {
					if (wcscmp(students[i].account, currentStudent.account) == 0 && wcscmp(students[i].password, currentStudent.password) == 0) {
						for (int j = i; j < StudentMaxNum - 1; j++) {
							students[j] = students[j + 1];
						}
						students[--studentNum].id = -1;

						// 重新分配学生ID
						for (int i = 0; i < studentNum; i++) {
							students[i].id = i;
						}

						SaveStudentToFile();
						MessageBox(NULL, _T("注销成功"), _T("提示"), MB_OK);
						WelcomeGraph();
						return;
					}
				}
			}
            //返回
            else if (IsMouseInRect(btnX, 410, btnWidth, btnHeight)) {
                WelcomeGraph();
                return;
            }
        }
    }
}

//选择注册方式界面
void SigninChooseGraph() {
	cleardevice();
	LoadBgk();
    SetHeightText(30);
    RECT r = { 0, 0, 800, 150 };
    drawtext(_T("请选择注册方式"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	//绘制按钮
    DrawButton(300, 200, 200, 50, _T("管理员"),30);
    DrawButton(300, 300, 200, 50, _T("学生"),30);
	DrawButton(300, 400, 200, 50, _T("返回"),30);

	//点击事件处理
    while (true) {
        MOUSEMSG msg = GetMouseMsg();
        if (msg.uMsg == WM_LBUTTONDOWN) {
			//管理员
            if (IsMouseInRect(300, 200, 200, 50)) {
                int adminNum = CountAdminNum();

				//检查管理员数量
                if (adminNum >= AdminMaxNum) {
                    MessageBox(NULL, _T("管理员数量已达上限"), _T("错误"), MB_OK);
                    continue;
                }

                Admin newAdmin;


				//用户名
                InputBox(newAdmin.account, MAX_STRING_LENGTH, _T("请输入用户名:"), _T("注册（最多6个字符）"), NULL);
				//不能为空
				if (wcslen(newAdmin.account) == 0) {
					MessageBox(NULL, _T("不能为空"), _T("错误"), MB_OK);
					continue;
				}
				//不能包含逗号
				if (wcschr(newAdmin.account, L',')) {
					MessageBox(NULL, _T("用户名不能包含逗号"), _T("错误"), MB_OK);
					continue;
				}
				//不能重复
                for (int i = 0; i < AdminMaxNum; i++) {
                    if (wcscmp(newAdmin.account, admins[i].account) == 0) {
                        MessageBox(NULL, _T("用户名已存在，请重新输入"), _T("错误"), MB_OK);
                        continue;
                    }
                }


				//密码
                InputBox(newAdmin.password, MAX_STRING_LENGTH, _T("请输入密码:"), _T("注册（最多6个字符）"), NULL);
				//不能为空
				if (wcslen(newAdmin.password) == 0) {
					MessageBox(NULL, _T("不能为空"), _T("错误"), MB_OK);
					continue;
				}
				//不能包含逗号
				if (wcschr(newAdmin.password, L',')) {
					MessageBox(NULL, _T("密码不能包含逗号"), _T("错误"), MB_OK);
					continue;
				}
				//不能重复
				for (int i = 0; i < AdminMaxNum; i++) {
					if (wcscmp(newAdmin.password, admins[i].password) == 0) {
						MessageBox(NULL, _T("密码已存在，请重新输入"), _T("错误"), MB_OK);
						continue;
					}
				}

                newAdmin.id = adminNum;

                admins[adminNum] = newAdmin;

                SaveAdminToFile();
                MessageBox(NULL, _T("注册成功"), _T("提示"), MB_OK);
            }
			//学生
            else if (IsMouseInRect(300, 300, 200, 50)) {
                int studentNum = CountStudentNum();

                //检查学生数量
                if (studentNum >= StudentMaxNum) {
                    MessageBox(NULL, _T("学生数量已达上限"), _T("错误"), MB_OK);
                    continue;
                }

                Student newStudent;


				//用户名
                InputBox(newStudent.account, MAX_STRING_LENGTH, _T("请输入用户名:"), _T("注册（最多6个字符）"), NULL);
                //不能为空
                if (wcslen(newStudent.account) == 0) {
                    MessageBox(NULL, _T("不能为空"), _T("错误"), MB_OK);
                    continue;
                }
				//不能包含逗号
				if (wcschr(newStudent.account, L',')) {
					MessageBox(NULL, _T("用户名不能包含逗号"), _T("错误"), MB_OK);
					continue;
				}
				//不能重复
				for (int i = 0; i < StudentMaxNum; i++) {
					if (wcscmp(newStudent.account, students[i].account) == 0) {
						MessageBox(NULL, _T("用户名已存在，请重新输入"), _T("错误"), MB_OK);
						continue;
					}
				}


				//密码
                InputBox(newStudent.password, MAX_STRING_LENGTH, _T("请输入密码:"), _T("注册（最多6个字符）"), NULL);
                //不能为空
                if (wcslen(newStudent.password) == 0) {
                    MessageBox(NULL, _T("不能为空"), _T("错误"), MB_OK);
                    continue;
                }
				//不能包含逗号
                if (wcschr(newStudent.password, L',')) {
                    MessageBox(NULL, _T("密码不能包含逗号"), _T("错误"), MB_OK);
                    continue;
                }
				//不能重复
				for (int i = 0; i < StudentMaxNum; i++) {
					if (wcscmp(newStudent.password, students[i].password) == 0) {
						MessageBox(NULL, _T("密码已存在，请重新输入"), _T("错误"), MB_OK);
						continue;
					}
				}


				//姓名
                InputBox(newStudent.name, MAX_STRING_LENGTH, _T("请输入姓名:"), _T("注册（最多6个字符）"), NULL);
                //不能为空
                if (wcslen(newStudent.name) == 0) {
                    MessageBox(NULL, _T("不能为空"), _T("错误"), MB_OK);
                    continue;
                }
				//不能包含逗号
				if (wcschr(newStudent.name, L',')) {
					MessageBox(NULL, _T("姓名不能包含逗号"), _T("错误"), MB_OK);
					continue;
				}


				//性别
                InputBox(newStudent.gender, MAX_STRING_LENGTH, _T("请输入性别:"), _T("注册（最多6个字符）"), NULL);
                //不能为空
                if (wcslen(newStudent.gender) == 0) {
                    MessageBox(NULL, _T("不能为空"), _T("错误"), MB_OK);
                    continue;
                }
                //不能包含逗号
                if (wcschr(newStudent.gender, L',')) {
                    MessageBox(NULL, _T("性别不能包含逗号"), _T("错误"), MB_OK);
                    continue;
                }


				////年龄
                InputBox(newStudent.age, MAX_STRING_LENGTH, _T("请输入年龄:"), _T("注册（最多6个字符）"), NULL);
                //不能为空
                if (wcslen(newStudent.age) == 0) {
                    MessageBox(NULL, _T("不能为空"), _T("错误"), MB_OK);
                    continue;
                }
				//不能包含逗号
				if (wcschr(newStudent.age, L',')) {
					MessageBox(NULL, _T("年龄不能包含逗号"), _T("错误"), MB_OK);
					continue;
				}


				//年级
                InputBox(newStudent.grade, MAX_STRING_LENGTH, _T("请输入年级:"), _T("注册（最多6个字符）"), NULL);
                //不能为空
                if (wcslen(newStudent.grade) == 0) {
                    MessageBox(NULL, _T("不能为空"), _T("错误"), MB_OK);
                    continue;
                }
				//不能包含逗号
				if (wcschr(newStudent.grade, L',')) {
					MessageBox(NULL, _T("年级不能包含逗号"), _T("错误"), MB_OK);
					continue;
				}


				//班级
                InputBox(newStudent.classNum, MAX_STRING_LENGTH, _T("请输入班级:"), _T("注册（最多6个字符）"), NULL);
                //不能为空
                if (wcslen(newStudent.classNum) == 0) {
                    MessageBox(NULL, _T("不能为空"), _T("错误"), MB_OK);
                    continue;
                }
				//不能包含逗号
				if (wcschr(newStudent.classNum, L',')) {
					MessageBox(NULL, _T("班级不能包含逗号"), _T("错误"), MB_OK);
					continue;
				}

                newStudent.id = studentNum;

                students[studentNum] = newStudent;

                SaveStudentToFile();
                MessageBox(NULL, _T("注册成功"), _T("提示"), MB_OK);
            }
			//返回
            else if (IsMouseInRect(300, 400, 200, 50)) {
                WelcomeGraph();
                return;
            }
        }
    }
}

//查看学生信息界面
void ViewStudentInfoGraph() {
    static int page = 1;
    cleardevice();
    LoadBgk();

    SetHeightText(25);
    settextcolor(BLACK);

    // 表头定义
    const TCHAR* headers[] = { _T("ID"), _T("账号"), _T("密码"), _T("姓名"), _T("性别"), _T("年龄"), _T("年级"), _T("班级") };
    const int numCols = sizeof(headers) / sizeof(headers[0]);

    // 计算表格位置（居中显示）
    const int tableX = 0;
    const int tableY = 75;
    const int cellWidth = 100;
    const int cellHeight = 40;
    const int tableWidth = cellWidth * numCols;
    const int tableHeight = cellHeight * (TABLE_ROWS + 1);

    // 绘制表头（带背景色）
    setfillcolor(RGB(200, 230, 255));
    for (int col = 0; col < numCols; col++) {
        RECT rHeader = {
            tableX + col * cellWidth,
            tableY,
            tableX + (col + 1) * cellWidth,
            tableY + cellHeight
        };
        fillrectangle(rHeader.left, rHeader.top, rHeader.right, rHeader.bottom);
        drawtext(headers[col], &rHeader, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    }

    // 绘制表格线
    setlinecolor(BLACK);
    for (int row = 0; row <= TABLE_ROWS + 1; row++) {
        line(
            tableX,
            tableY + row * cellHeight,
            tableX + tableWidth,
            tableY + row * cellHeight
        );
    }
    for (int col = 0; col <= numCols; col++) {
        line(
            tableX + col * cellWidth,
            tableY,
            tableX + col * cellWidth,
            tableY + tableHeight
        );
    }

    // 填充数据（居中显示）
    int studentCount = CountStudentNum();
    int totalPages = (studentCount + TABLE_ROWS - 1) / TABLE_ROWS;
    if (totalPages == 0) totalPages = 1;
    if (page > totalPages) page = totalPages;

    int startIdx = (page - 1) * TABLE_ROWS;
    int endIdx = min(startIdx + TABLE_ROWS, studentCount);

    for (int i = startIdx; i < endIdx; i++) {
        int row = (i - startIdx) + 1;
        wchar_t idStr[20];
        swprintf_s(idStr, L"%d", students[i].id);

        const wchar_t* fields[] = {
            idStr,
            students[i].account,
            students[i].password,
            students[i].name,
            students[i].gender,
            students[i].age,
            students[i].grade,
            students[i].classNum
        };

        // 绘制每列数据（居中）
        for (int col = 0; col < numCols; col++) {
            RECT rCell = {
                tableX + col * cellWidth,
                tableY + row * cellHeight,
                tableX + (col + 1) * cellWidth,
                tableY + (row + 1) * cellHeight
            };
            drawtext(fields[col], &rCell, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
        }
    }

    // 页码信息（底部居中）
    wchar_t pageInfo[50];
    swprintf_s(pageInfo, L"第 %d 页/共 %d 页", page, totalPages);
    RECT rPage = { tableX, tableY + tableHeight + 20, tableX + tableWidth, tableY + tableHeight + 50 };
    drawtext(pageInfo, &rPage, DT_CENTER | DT_VCENTER);

    // 翻页按钮（动态显示）
    const int btnWidth = 80;
    const int btnHeight = 30;
    const int btnY = tableY + tableHeight + 20;

    if (page > 1) {
        DrawButton(tableX, btnY, btnWidth, btnHeight, _T("上一页"), 20);
    }
    if (page < totalPages) {
        DrawButton(tableX + tableWidth - btnWidth, btnY, btnWidth, btnHeight, _T("下一页"), 20);
    }

    // 返回按钮（右上角）
    DrawButton(tableX + tableWidth - btnWidth, tableY - 50, btnWidth, btnHeight, _T("返回"), 20);

    // 事件处理
    while (true) {
        MOUSEMSG msg = GetMouseMsg();
        if (msg.uMsg == WM_LBUTTONDOWN) {
            if (IsMouseInRect(tableX + tableWidth - btnWidth, tableY - 50, btnWidth, btnHeight)) {
                page = 1;
                AdminManageGraph();
                return;
            }
            else if (page > 1 && IsMouseInRect(tableX, btnY, btnWidth, btnHeight)) {
                page--;
                ViewStudentInfoGraph();
                return;
            }
            else if (page < totalPages && IsMouseInRect(tableX + tableWidth - btnWidth, btnY, btnWidth, btnHeight)) {
                page++;
                ViewStudentInfoGraph();
                return;
            }
        }
    }
}

//修改学生信息界面
void ModifyStudentInfoGraph() {
    cleardevice();
    LoadBgk();
    SetHeightText(30);
    RECT r = { 0, 0, 800, 150 };
    drawtext(_T("请选择你要修改的信息："), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

    //绘制按钮
    const int btnWidth = 150, btnHeight = 40;
    const int btnX = 300;
    DrawButton(btnX, 130, btnWidth, btnHeight, _T("用户名"), 30);
    DrawButton(btnX, 180, btnWidth, btnHeight, _T("密码"), 30);
    DrawButton(btnX, 230, btnWidth, btnHeight, _T("姓名"), 30);
    DrawButton(btnX, 280, btnWidth, btnHeight, _T("年龄"), 30);
    DrawButton(btnX, 330, btnWidth, btnHeight, _T("性别"), 30);
    DrawButton(btnX, 380, btnWidth, btnHeight, _T("年级"), 30);
    DrawButton(btnX, 430, btnWidth, btnHeight, _T("班级"), 30);
    DrawButton(btnX, 480, btnWidth, btnHeight, _T("返回"), 30);

    //点击事件处理
    while (true) {
        MOUSEMSG msg = GetMouseMsg();
        if (msg.uMsg == WM_LBUTTONDOWN) {
            //修改用户名
            if (IsMouseInRect(btnX, 130, btnWidth, btnHeight)) {
                for (int i = 0; i < StudentMaxNum; i++) {
                    if (wcscmp(students[i].account, currentStudent.account) == 0 && wcscmp(students[i].password, currentStudent.password) == 0) {
                        wchar_t newAccount[MAX_STRING_LENGTH];
                        InputBox(newAccount, MAX_STRING_LENGTH, _T("请输入新的用户名:"), _T("修改用户名"), NULL);
                        //不能为空
                        if (wcslen(newAccount) == 0) {
                            MessageBox(NULL, _T("不能为空"), _T("错误"), MB_OK);
                            continue;
                        }
                        //不能包含逗号
                        if (wcschr(newAccount, L',')) {
                            MessageBox(NULL, _T("用户名不能包含逗号"), _T("错误"), MB_OK);
                            continue;
                        }
                        //不能与原用户名相同
                        if (wcscmp(newAccount, currentStudent.account) == 0) {
                            MessageBox(NULL, _T("用户名不能与原用户名相同"), _T("错误"), MB_OK);
                            continue;
                        }
                        //已经被注册
                        bool isDuplicate = false;
                        for (int j = 0; j < StudentMaxNum; j++) {
                            if (wcscmp(newAccount, students[j].account) == 0) {
                                isDuplicate = true;
                                break;
                            }
                        }
                        if (isDuplicate) {
                            MessageBox(NULL, _T("该用户名已被使用，请重新输入"), _T("错误"), MB_OK);
                            continue;
                        }

                        wcscpy_s(students[i].account, newAccount);
                        MessageBox(NULL, _T("修改成功"), _T("提示"), MB_OK);
                        SaveStudentToFile();
                        //更新当前学生信息
                        currentStudent = students[i];
                        break;
                    }
                }
            }
            //修改密码
            else if (IsMouseInRect(btnX, 180, btnWidth, btnHeight)) {
                for (int i = 0; i < StudentMaxNum; i++) {
                    if (wcscmp(students[i].account, currentStudent.account) == 0 && wcscmp(students[i].password, currentStudent.password) == 0) {
                        wchar_t newPassword[MAX_STRING_LENGTH];
                        InputBox(newPassword, MAX_STRING_LENGTH, _T("请输入新的密码:"), _T("修改密码"), NULL);
                        //不能为空
                        if (wcslen(newPassword) == 0) {
                            MessageBox(NULL, _T("不能为空"), _T("错误"), MB_OK);
                            continue;
                        }
                        //不能包含逗号
                        if (wcschr(newPassword, L',')) {
                            MessageBox(NULL, _T("密码不能包含逗号"), _T("错误"), MB_OK);
                            continue;
                        }
                        //不能与原密码相同
                        if (wcscmp(newPassword, currentStudent.password) == 0) {
                            MessageBox(NULL, _T("密码不能与原密码相同"), _T("错误"), MB_OK);
                            continue;
                        }
						//已经被注册
						bool isDuplicate = false;
						for (int j = 0; j < StudentMaxNum; j++) {
							if (wcscmp(newPassword, students[j].password) == 0) {
								isDuplicate = true;
								break;
							}
						}
						if (isDuplicate) {
							MessageBox(NULL, _T("该密码已被使用，请重新输入"), _T("错误"), MB_OK);
							continue;
						}

                        wcscpy_s(students[i].password, newPassword);
                        MessageBox(NULL, _T("修改成功"), _T("提示"), MB_OK);
                        SaveStudentToFile();
                        //更新当前学生信息
                        currentStudent = students[i];
                        break;
                    }
                }
            }
            //修改姓名
            else if (IsMouseInRect(btnX, 230, btnWidth, btnHeight)) {
                for (int i = 0; i < StudentMaxNum; i++) {
                    if (wcscmp(students[i].account, currentStudent.account) == 0 && wcscmp(students[i].password, currentStudent.password) == 0) {
                        wchar_t newName[MAX_STRING_LENGTH];
                        InputBox(newName, MAX_STRING_LENGTH, _T("请输入新的姓名:"), _T("修改姓名"), NULL);
                        //不能为空
                        if (wcslen(newName) == 0) {
                            MessageBox(NULL, _T("不能为空"), _T("错误"), MB_OK);
                            continue;
                        }
                        //不能包含逗号
                        if (wcschr(newName, L',')) {
                            MessageBox(NULL, _T("姓名不能包含逗号"), _T("错误"), MB_OK);
                            continue;
                        }
                        //不能与原姓名相同
                        if (wcscmp(newName, currentStudent.name) == 0) {
                            MessageBox(NULL, _T("姓名不能与原姓名相同"), _T("错误"), MB_OK);
                            continue;
                        }

                        wcscpy_s(students[i].name, newName);
                        MessageBox(NULL, _T("修改成功"), _T("提示"), MB_OK);
                        SaveStudentToFile();
                        //更新当前学生信息
                        currentStudent = students[i];
                        break;
                    }
                }
            }
            //修改年龄
            else if (IsMouseInRect(btnX, 280, btnWidth, btnHeight)) {
                for (int i = 0; i < StudentMaxNum; i++) {
                    if (wcscmp(students[i].account, currentStudent.account) == 0 && wcscmp(students[i].password, currentStudent.password) == 0) {
                        wchar_t newAge[MAX_STRING_LENGTH];
                        InputBox(newAge, MAX_STRING_LENGTH, _T("请输入新的年龄:"), _T("修改年龄"), NULL);
                        //不能为空
                        if (wcslen(newAge) == 0) {
                            MessageBox(NULL, _T("不能为空"), _T("错误"), MB_OK);
                            continue;
                        }
                        //不能包含逗号
                        if (wcschr(newAge, L',')) {
                            MessageBox(NULL, _T("年龄不能包含逗号"), _T("错误"), MB_OK);
                            continue;
                        }
                        //不能与原年龄相同
                        if (wcscmp(newAge, currentStudent.age) == 0) {
                            MessageBox(NULL, _T("年龄不能与原年龄相同"), _T("错误"), MB_OK);
                            continue;
                        }

                        wcscpy_s(students[i].age, newAge);
                        MessageBox(NULL, _T("修改成功"), _T("提示"), MB_OK);
                        SaveStudentToFile();
                        //更新当前学生信息
                        currentStudent = students[i];
                        break;
                    }
                }
            }
            //修改性别
            else if (IsMouseInRect(btnX, 330, btnWidth, btnHeight)) {
                for (int i = 0; i < StudentMaxNum; i++) {
                    if (wcscmp(students[i].account, currentStudent.account) == 0 && wcscmp(students[i].password, currentStudent.password) == 0) {
                        wchar_t newGender[MAX_STRING_LENGTH];
                        InputBox(newGender, MAX_STRING_LENGTH, _T("请输入新的性别:"), _T("修改性别"), NULL);
                        //不能为空
                        if (wcslen(newGender) == 0) {
                            MessageBox(NULL, _T("不能为空"), _T("错误"), MB_OK);
                            continue;
                        }
                        //不能包含逗号
                        if (wcschr(newGender, L',')) {
                            MessageBox(NULL, _T("性别不能包含逗号"), _T("错误"), MB_OK);
                            continue;
                        }
                        //不能与原性别相同
                        if (wcscmp(newGender, currentStudent.gender) == 0) {
                            MessageBox(NULL, _T("性别不能与原性别相同"), _T("错误"), MB_OK);
                            continue;
                        }

                        wcscpy_s(students[i].gender, newGender);
                        MessageBox(NULL, _T("修改成功"), _T("提示"), MB_OK);
                        SaveStudentToFile();
                        //更新当前学生信息
                        currentStudent = students[i];
                        break;
                    }
                }
            }
            //修改年级
            else if (IsMouseInRect(btnX, 380, btnWidth, btnHeight)) {
                for (int i = 0; i < StudentMaxNum; i++) {
                    if (wcscmp(students[i].account, currentStudent.account) == 0 && wcscmp(students[i].password, currentStudent.password) == 0) {
                        wchar_t newGrade[MAX_STRING_LENGTH];
                        InputBox(newGrade, MAX_STRING_LENGTH, _T("请输入新的年级:"), _T("修改年级"), NULL);
                        //不能为空
                        if (wcslen(newGrade) == 0) {
                            MessageBox(NULL, _T("不能为空"), _T("错误"), MB_OK);
                            continue;
                        }
                        //不能包含逗号
                        if (wcschr(newGrade, L',')) {
                            MessageBox(NULL, _T("年级不能包含逗号"), _T("错误"), MB_OK);
                            continue;
                        }
                        //不能与原年级相同
                        if (wcscmp(newGrade, currentStudent.grade) == 0) {
                            MessageBox(NULL, _T("年级不能与原年级相同"), _T("错误"), MB_OK);
                            continue;
                        }

                        wcscpy_s(students[i].grade, newGrade);
                        MessageBox(NULL, _T("修改成功"), _T("提示"), MB_OK);
                        SaveStudentToFile();
                        //更新当前学生信息
                        currentStudent = students[i];
                        break;
                    }
                }
            }
            //修改班级
            else if (IsMouseInRect(btnX, 430, btnWidth, btnHeight)) {
                for (int i = 0; i < StudentMaxNum; i++) {
                    if (wcscmp(students[i].account, currentStudent.account) == 0 && wcscmp(students[i].password, currentStudent.password) == 0) {
                        wchar_t newClassNum[MAX_STRING_LENGTH];
                        InputBox(newClassNum, MAX_STRING_LENGTH, _T("请输入新的班级:"), _T("修改班级"), NULL);
                        //不能为空
                        if (wcslen(newClassNum) == 0) {
                            MessageBox(NULL, _T("不能为空"), _T("错误"), MB_OK);
                            continue;
                        }
                        //不能包含逗号
                        if (wcschr(newClassNum, L',')) {
                            MessageBox(NULL, _T("班级不能包含逗号"), _T("错误"), MB_OK);
                            continue;
                        }
                        //不能与原班级相同
                        if (wcscmp(newClassNum, currentStudent.classNum) == 0) {
                            MessageBox(NULL, _T("班级不能与原班级相同"), _T("错误"), MB_OK);
                            continue;
                        }

                        wcscpy_s(students[i].classNum, newClassNum);
                        MessageBox(NULL, _T("修改成功"), _T("提示"), MB_OK);
                        SaveStudentToFile();
                        //更新当前学生信息
                        currentStudent = students[i];
                        break;
                    }
                }
            }
            //返回
            else if (IsMouseInRect(btnX, 480, btnWidth, btnHeight)) {
				if (flag == 1) {
					AdminManageGraph();
                    return;
				}
                else if (flag == 2) {
                    StudentManageGraph();
                    return;
                }
            }
        }
    }
}

//欢迎界面
void WelcomeGraph() {
    cleardevice();
    LoadBgk();
    SetHeightText(30);
    RECT r = { 0, 0, 800, 150 };
    drawtext(_T("欢迎使用学生管理系统!"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	//绘制按钮
    const int btnWidth = 200, btnHeight = 50;
    const int btnX = 300;
    DrawButton(btnX, 290, btnWidth, btnHeight, _T("登录"), 30);
    DrawButton(btnX, 360, btnWidth, btnHeight, _T("注册"), 30);
    DrawButton(btnX, 430, btnWidth, btnHeight, _T("退出"), 30);

	//点击事件处理
    while (true) {
        MOUSEMSG msg = GetMouseMsg();
        if (msg.uMsg == WM_LBUTTONDOWN) {
            //登录
            if (IsMouseInRect(btnX, 290, btnWidth, btnHeight)) {

                wchar_t username[MAX_STRING_LENGTH], password[MAX_STRING_LENGTH];

                InputBox(username, MAX_STRING_LENGTH, _T("请输入用户名:"), _T("登录"), NULL);
				//不能为空
				if (wcslen(username) == 0) {
					MessageBox(NULL, _T("不能为空"), _T("错误"), MB_OK);
					continue;
				}

                InputBox(password, MAX_STRING_LENGTH, _T("请输入密码:"), _T("登录"), NULL);
				//不能为空
                if (wcslen(password) == 0) {
                    MessageBox(NULL, _T("不能为空"), _T("错误"), MB_OK);
                    continue;
                }

                switch (LoginCheck(username, password)) {
                case 1:
                    MessageBox(NULL, _T("管理员登录成功"), _T("提示"), MB_OK);
					//记录当前管理员账号
					for (int i = 0; i < AdminMaxNum; i++) {
						if (wcscmp(admins[i].account, username) == 0 && wcscmp(admins[i].password, password) == 0) {
							currentAdmin = admins[i];
							break;
						}
					}
                    AdminManageGraph();
                    return;
                case 2:
                    MessageBox(NULL, _T("学生登录成功"), _T("提示"), MB_OK);
					//记录当前学生账号
					for (int i = 0; i < StudentMaxNum; i++) {
						if (wcscmp(students[i].account, username) == 0 && wcscmp(students[i].password, password) == 0) {
							currentStudent = students[i];
							break;
						}
					}
                    StudentManageGraph();
                    return;
                case 0:
                    MessageBox(NULL, _T("用户名或密码错误"), _T("错误"), MB_OK);
                }
            }
            //注册
            else if (IsMouseInRect(btnX, 360, btnWidth, btnHeight)) {
                SigninChooseGraph();
                return;
            }
            //退出
            else if (IsMouseInRect(btnX, 430, btnWidth, btnHeight)) {
                exit(0);
            }
        }
    }
}
