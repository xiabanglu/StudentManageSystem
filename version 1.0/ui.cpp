#include "ui.h"
#include "student.h"
#include "admin.h"
#include "graphics_utils.h"
#include <graphics.h>
#include <wchar.h>
#include <locale.h>

//��¼�Ժ�����ݵ�¼
int flag = 0;//1��ʾ����Ա��2��ʾѧ��

//��¼��ǰ�˺�
Admin currentAdmin;
Student currentStudent;

//��¼���
int LoginCheck(const wchar_t* username, const wchar_t* password) {
	//����Ա
	for (int i = 0; i < AdminMaxNum && admins[i].id != -1; i++) {
		if (wcscmp(username, admins[i].account) == 0 &&
			wcscmp(password, admins[i].password) == 0) return 1;
	}
	//ѧ��
	for (int i = 0; i < StudentMaxNum && students[i].id != -1; i++) {
		if (wcscmp(username, students[i].account) == 0 &&
			wcscmp(password, students[i].password) == 0) return 2;
	}
	//δ�ҵ�
	return 0;
}

//����Ա����
void AdminManageGraph() {
	flag = 1;
	cleardevice();
	LoadBgk();
	SetHeightText(30);
	RECT r = { 0, 0, 800, 150 };
	drawtext(L"��ӭ����ѧ������ϵͳ(����ԱȨ��)", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	HWND hnd_AdminManageGraph = GetHWnd();
	SetWindowText(hnd_AdminManageGraph, _T("����ԱȨ��"));

	//���ư�ť
	const int btnWidth = 200, btnHeight = 50;
	const int btnX = 300;
	DrawButton(btnX, 130, btnWidth, btnHeight, _T("¼��ѧ����Ϣ"), 30);
	DrawButton(btnX, 200, btnWidth, btnHeight, _T("ɾ��ѧ����Ϣ"), 30);
	DrawButton(btnX, 270, btnWidth, btnHeight, _T("�鿴ѧ����Ϣ"), 30);
	DrawButton(btnX, 340, btnWidth, btnHeight, _T("�޸�ѧ����Ϣ"), 30);
	DrawButton(btnX, 410, btnWidth, btnHeight, _T("ע���ҵ��˺�"), 30);
	DrawButton(btnX, 480, btnWidth, btnHeight, _T("����"), 30);

	//����¼�����
	while (true) {
		MOUSEMSG msg = GetMouseMsg();
		if (msg.uMsg == WM_LBUTTONDOWN) {
			//¼��ѧ����Ϣ
			if (IsMouseInRect(btnX, 130, btnWidth, btnHeight)) {
				int studentNum = CountStudentNum();

				//���ѧ������
				if (studentNum >= StudentMaxNum) {
					MessageBox(hnd_AdminManageGraph, _T("ѧ�������Ѵ�����"), _T("����"), MB_OK);
					continue;
				}

				Student newStudent;


				//�û���
				InputBox(newStudent.account, MAX_STRING_LENGTH, _T("�������û���:"), _T("���ѧ����Ϣ�����6���ַ���"), NULL);
				//����Ϊ��
				if (wcslen(newStudent.account) == 0) {
					MessageBox(hnd_AdminManageGraph, _T("����Ϊ��"), _T("����"), MB_OK);
					continue;
				}
				//���ܰ�������
				if (wcschr(newStudent.account, L',')) {
					MessageBox(hnd_AdminManageGraph, _T("�û������ܰ�������"), _T("����"), MB_OK);
					continue;
				}
				//�����ظ�
				for (int i = 0; i < StudentMaxNum; i++) {
					if (wcscmp(newStudent.account, students[i].account) == 0) {
						MessageBox(hnd_AdminManageGraph, _T("�û����Ѵ��ڣ�����������"), _T("����"), MB_OK);
						continue;
					}
				}


				//����
				InputBox(newStudent.password, MAX_STRING_LENGTH, _T("����������:"), _T("���ѧ����Ϣ�����6���ַ���"), NULL);
				//����Ϊ��
				if (wcslen(newStudent.password) == 0) {
					MessageBox(hnd_AdminManageGraph, _T("����Ϊ��"), _T("����"), MB_OK);
					continue;
				}
				//���ܰ�������
				if (wcschr(newStudent.password, L',')) {
					MessageBox(hnd_AdminManageGraph, _T("���벻�ܰ�������"), _T("����"), MB_OK);
					continue;
				}
				//�����ظ�
				for (int i = 0; i < StudentMaxNum; i++) {
					if (wcscmp(newStudent.password, students[i].password) == 0) {
						MessageBox(hnd_AdminManageGraph, _T("�����Ѵ��ڣ�����������"), _T("����"), MB_OK);
						continue;
					}
				}


				//����
				InputBox(newStudent.name, MAX_STRING_LENGTH, _T("����������:"), _T("���ѧ����Ϣ�����6���ַ���"), NULL);
				//����Ϊ��
				if (wcslen(newStudent.name) == 0) {
					MessageBox(hnd_AdminManageGraph, _T("����Ϊ��"), _T("����"), MB_OK);
					continue;
				}
				//���ܰ�������
				if (wcschr(newStudent.name, L',')) {
					MessageBox(hnd_AdminManageGraph, _T("�������ܰ�������"), _T("����"), MB_OK);
					continue;
				}


				//�Ա�
				InputBox(newStudent.gender, MAX_STRING_LENGTH, _T("�������Ա�:"), _T("���ѧ����Ϣ�����6���ַ���"), NULL);
				//����Ϊ��
				if (wcslen(newStudent.gender) == 0) {
					MessageBox(hnd_AdminManageGraph, _T("����Ϊ��"), _T("����"), MB_OK);
					continue;
				}
				//���ܰ�������
				if (wcschr(newStudent.gender, L',')) {
					MessageBox(hnd_AdminManageGraph, _T("�Ա��ܰ�������"), _T("����"), MB_OK);
					continue;
				}


				//����
				InputBox(newStudent.age, MAX_STRING_LENGTH, _T("����������:"), _T("���ѧ����Ϣ�����6���ַ���"), NULL);
				//����Ϊ��
				if (wcslen(newStudent.age) == 0) {
					MessageBox(hnd_AdminManageGraph, _T("����Ϊ��"), _T("����"), MB_OK);
					continue;
				}
				//���ܰ�������
				if (wcschr(newStudent.age, L',')) {
					MessageBox(hnd_AdminManageGraph, _T("���䲻�ܰ�������"), _T("����"), MB_OK);
					continue;
				}


				//�꼶
				InputBox(newStudent.grade, MAX_STRING_LENGTH, _T("�������꼶:"), _T("���ѧ����Ϣ�����6���ַ���"), NULL);
				//����Ϊ��
				if (wcslen(newStudent.grade) == 0) {
					MessageBox(hnd_AdminManageGraph, _T("����Ϊ��"), _T("����"), MB_OK);
					continue;
				}
				//���ܰ�������
				if (wcschr(newStudent.grade, L',')) {
					MessageBox(hnd_AdminManageGraph, _T("�꼶���ܰ�������"), _T("����"), MB_OK);
					continue;
				}


				//�༶
				InputBox(newStudent.classNum, MAX_STRING_LENGTH, _T("������༶:"), _T("���ѧ����Ϣ�����6���ַ���"), NULL);
				//����Ϊ��
				if (wcslen(newStudent.classNum) == 0) {
					MessageBox(hnd_AdminManageGraph, _T("����Ϊ��"), _T("����"), MB_OK);
					continue;
				}
				//���ܰ�������
				if (wcschr(newStudent.classNum, L',')) {
					MessageBox(hnd_AdminManageGraph, _T("�༶���ܰ�������"), _T("����"), MB_OK);
					continue;
				}


				newStudent.id = studentNum;

				students[studentNum] = newStudent;

				// ���·���ѧ��ID
				for (int i = 0; i <= studentNum; i++) {
					students[i].id = i;
				}

				SaveStudentToFile();
				MessageBox(hnd_AdminManageGraph, _T("¼��ɹ�"), _T("��ʾ"), MB_OK);
			}
			//ɾ��ѧ����Ϣ
			else if (IsMouseInRect(btnX, 200, btnWidth, btnHeight)) {
				int studentNum = CountStudentNum();

				//���ѧ������
				if (studentNum == 0) {
					MessageBox(hnd_AdminManageGraph, _T("û��ѧ����Ϣ��ɾ��"), _T("����"), MB_OK);
					continue;
				}

				//�����û���ɾ��ѧ����Ϣ
				wchar_t DelStudentAccount[MAX_STRING_LENGTH];

				InputBox(DelStudentAccount, MAX_STRING_LENGTH, _T("������Ҫɾ����ѧ�����û���:"), _T("ɾ��ѧ����Ϣ�����6���ַ���"), NULL);
				//����Ϊ��
				if (wcslen(DelStudentAccount) == 0) {
					MessageBox(hnd_AdminManageGraph, _T("����Ϊ��"), _T("����"), MB_OK);
					continue;
				}
				//���ܰ�������
				if (wcschr(DelStudentAccount, L',')) {
					MessageBox(hnd_AdminManageGraph, _T("�û������ܰ�������"), _T("����"), MB_OK);
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

						// ���·���ѧ��ID
						for (int i = 0; i < studentNum; i++) {
							students[i].id = i;
						}

						SaveStudentToFile();
						MessageBox(hnd_AdminManageGraph, _T("ɾ���ɹ�"), _T("��ʾ"), MB_OK);
						break;
					}
				}

				if (!studentFound) {
					MessageBox(hnd_AdminManageGraph, _T("δ�ҵ���ѧ���˺�"), _T("����"), MB_OK);
				}
			}
			//�鿴ѧ����Ϣ
			else if (IsMouseInRect(btnX, 270, btnWidth, btnHeight)) {
				ViewStudentInfoGraph();
				return;
			}
			//�޸�ѧ����Ϣ
			else if (IsMouseInRect(btnX, 340, btnWidth, btnHeight)) {

				bool studentFound = false;
				InputBox(currentStudent.account, MAX_STRING_LENGTH, _T("������Ҫ�޸ĵ�ѧ�����û���:"), _T("�޸�ѧ����Ϣ�����6���ַ���"), NULL);
				//����Ϊ��
				if (wcslen(currentStudent.account) == 0) {
					MessageBox(hnd_AdminManageGraph, _T("����Ϊ��"), _T("����"), MB_OK);
					continue;
				}
				//���ܰ�������
				if (wcschr(currentStudent.account, L',')) {
					MessageBox(hnd_AdminManageGraph, _T("�û������ܰ�������"), _T("����"), MB_OK);
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
					MessageBox(hnd_AdminManageGraph, _T("δ�ҵ���ѧ���˺�"), _T("����"), MB_OK);
					continue;
				}
			}
			//ע���ҵ��˺�
			else if (IsMouseInRect(btnX, 410, btnWidth, btnHeight)) {
				int adminNum = CountAdminNum();

				for (int i = 0; i < AdminMaxNum; i++) {
					if (wcscmp(admins[i].account, currentAdmin.account) == 0 && wcscmp(admins[i].password, currentAdmin.password) == 0) {
						for (int j = i; j < AdminMaxNum - 1; j++) {
							admins[j] = admins[j + 1];
						}
						admins[--adminNum].id = -1;

						// ���·������ԱID
						for (int i = 0; i < adminNum; i++) {
							admins[i].id = i;
						}

						SaveAdminToFile();
						MessageBox(hnd_AdminManageGraph, _T("ע���ɹ�"), _T("��ʾ"), MB_OK);
						WelcomeGraph();
						return;
					}
				}
			}
			//����
			else if (IsMouseInRect(btnX, 480, btnWidth, btnHeight)) {
				WelcomeGraph();
				return;
			}
		}
	}
}

//ѧ������
void StudentManageGraph() {
	flag = 2;
	cleardevice();
	LoadBgk();
	SetHeightText(30);
	RECT r = { 0, 0, 800, 150 };
	drawtext(L"��ӭ����ѧ������ϵͳ(ѧ��Ȩ��)", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	HWND hnd_StudentManageGraph = GetHWnd();
	SetWindowText(hnd_StudentManageGraph, _T("ѧ��Ȩ��"));

	const int btnWidth = 200, btnHeight = 50;
	const int btnX = 300;
	DrawButton(btnX, 200, btnWidth, btnHeight, _T("�鿴�ҵ���Ϣ"), 30);
	DrawButton(btnX, 270, btnWidth, btnHeight, _T("�޸��ҵ���Ϣ"), 30);
	DrawButton(btnX, 340, btnWidth, btnHeight, _T("ע���ҵ��˺�"), 30);
	DrawButton(btnX, 410, btnWidth, btnHeight, _T("����"), 30);

	while (true) {
		MOUSEMSG msg = GetMouseMsg();
		if (msg.uMsg == WM_LBUTTONDOWN) {
			//�鿴�ҵ���Ϣ
			if (IsMouseInRect(btnX, 200, btnWidth, btnHeight)) {
				cleardevice();
				LoadBgk();

				SetHeightText(25);
				settextcolor(BLACK);

				// ��ͷ����
				const TCHAR* headers[] = { _T("ID"), _T("�˺�"), _T("����"), _T("����"), _T("�Ա�"), _T("����"), _T("�꼶"), _T("�༶") };
				const int numCols = sizeof(headers) / sizeof(headers[0]);

				// ������λ�ã�������ʾ��
				const int tableX = 0;
				const int tableY = 200;
				const int cellWidth = 100;
				const int cellHeight = 40;
				const int tableWidth = cellWidth * numCols;
				const int tableHeight = cellHeight * 2; // 2��

				// ���Ʊ�ͷ��������ɫ��
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

				// ���Ʊ����
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

				// ������ݣ�������ʾ��
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

				// ����ÿ�����ݣ����У�
				for (int col = 0; col < numCols; col++) {
					RECT rCell = {
						tableX + col * cellWidth,
						tableY + cellHeight,
						tableX + (col + 1) * cellWidth,
						tableY + 2 * cellHeight
					};
					drawtext(fields[col], &rCell, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				}

				// ���ذ�ť�����Ͻǣ�
				DrawButton(tableX + tableWidth - btnWidth, 500, btnWidth, btnHeight, _T("����"), 30);

				// �¼�����
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
			//�޸��ҵ���Ϣ
			else if (IsMouseInRect(btnX, 270, btnWidth, btnHeight)) {
				ModifyStudentInfoGraph();
				return;
			}
			//ע���ҵ��˺�
			else if (IsMouseInRect(btnX, 340, btnWidth, btnHeight)) {
				int studentNum = CountStudentNum();

				for (int i = 0; i < StudentMaxNum; i++) {
					if (wcscmp(students[i].account, currentStudent.account) == 0 && wcscmp(students[i].password, currentStudent.password) == 0) {
						for (int j = i; j < StudentMaxNum - 1; j++) {
							students[j] = students[j + 1];
						}
						students[--studentNum].id = -1;

						// ���·���ѧ��ID
						for (int i = 0; i < studentNum; i++) {
							students[i].id = i;
						}

						SaveStudentToFile();
						MessageBox(hnd_StudentManageGraph, _T("ע���ɹ�"), _T("��ʾ"), MB_OK);
						WelcomeGraph();
						return;
					}
				}
			}
			//����
			else if (IsMouseInRect(btnX, 410, btnWidth, btnHeight)) {
				WelcomeGraph();
				return;
			}
		}
	}
}

//ѡ��ע�᷽ʽ����
void SigninChooseGraph() {
	cleardevice();
	LoadBgk();
	SetHeightText(30);
	RECT r = { 0, 0, 800, 150 };
	drawtext(_T("��ѡ��ע�᷽ʽ"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	HWND hnd_SigninChooseGraph = GetHWnd();
	SetWindowText(hnd_SigninChooseGraph, _T("ע�᷽ʽѡ��"));

	//���ư�ť
	DrawButton(300, 200, 200, 50, _T("����Ա"), 30);
	DrawButton(300, 300, 200, 50, _T("ѧ��"), 30);
	DrawButton(300, 400, 200, 50, _T("����"), 30);

	//����¼�����
	while (true) {
		MOUSEMSG msg = GetMouseMsg();
		if (msg.uMsg == WM_LBUTTONDOWN) {
			//����Ա
			if (IsMouseInRect(300, 200, 200, 50)) {
				int adminNum = CountAdminNum();

				//������Ա����
				if (adminNum >= AdminMaxNum) {
					MessageBox(hnd_SigninChooseGraph, _T("����Ա�����Ѵ�����"), _T("����"), MB_OK);
					continue;
				}

				Admin newAdmin;


				//�û���
				InputBox(newAdmin.account, MAX_STRING_LENGTH, _T("�������û���:"), _T("ע�ᣨ���6���ַ���"), NULL);
				//����Ϊ��
				if (wcslen(newAdmin.account) == 0) {
					MessageBox(hnd_SigninChooseGraph, _T("����Ϊ��"), _T("����"), MB_OK);
					continue;
				}
				//���ܰ�������
				if (wcschr(newAdmin.account, L',')) {
					MessageBox(hnd_SigninChooseGraph, _T("�û������ܰ�������"), _T("����"), MB_OK);
					continue;
				}
				//�����ظ�
				for (int i = 0; i < AdminMaxNum; i++) {
					if (wcscmp(newAdmin.account, admins[i].account) == 0) {
						MessageBox(hnd_SigninChooseGraph, _T("�û����Ѵ��ڣ�����������"), _T("����"), MB_OK);
						continue;
					}
				}


				//����
				InputBox(newAdmin.password, MAX_STRING_LENGTH, _T("����������:"), _T("ע�ᣨ���6���ַ���"), NULL);
				//����Ϊ��
				if (wcslen(newAdmin.password) == 0) {
					MessageBox(hnd_SigninChooseGraph, _T("����Ϊ��"), _T("����"), MB_OK);
					continue;
				}
				//���ܰ�������
				if (wcschr(newAdmin.password, L',')) {
					MessageBox(hnd_SigninChooseGraph, _T("���벻�ܰ�������"), _T("����"), MB_OK);
					continue;
				}
				//�����ظ�
				for (int i = 0; i < AdminMaxNum; i++) {
					if (wcscmp(newAdmin.password, admins[i].password) == 0) {
						MessageBox(hnd_SigninChooseGraph, _T("�����Ѵ��ڣ�����������"), _T("����"), MB_OK);
						continue;
					}
				}

				newAdmin.id = adminNum;

				admins[adminNum] = newAdmin;

				SaveAdminToFile();
				MessageBox(hnd_SigninChooseGraph, _T("ע��ɹ�"), _T("��ʾ"), MB_OK);
			}
			//ѧ��
			else if (IsMouseInRect(300, 300, 200, 50)) {
				int studentNum = CountStudentNum();

				//���ѧ������
				if (studentNum >= StudentMaxNum) {
					MessageBox(hnd_SigninChooseGraph, _T("ѧ�������Ѵ�����"), _T("����"), MB_OK);
					continue;
				}

				Student newStudent;


				//�û���
				InputBox(newStudent.account, MAX_STRING_LENGTH, _T("�������û���:"), _T("ע�ᣨ���6���ַ���"), NULL);
				//����Ϊ��
				if (wcslen(newStudent.account) == 0) {
					MessageBox(hnd_SigninChooseGraph, _T("����Ϊ��"), _T("����"), MB_OK);
					continue;
				}
				//���ܰ�������
				if (wcschr(newStudent.account, L',')) {
					MessageBox(hnd_SigninChooseGraph, _T("�û������ܰ�������"), _T("����"), MB_OK);
					continue;
				}
				//�����ظ�
				for (int i = 0; i < StudentMaxNum; i++) {
					if (wcscmp(newStudent.account, students[i].account) == 0) {
						MessageBox(hnd_SigninChooseGraph, _T("�û����Ѵ��ڣ�����������"), _T("����"), MB_OK);
						continue;
					}
				}


				//����
				InputBox(newStudent.password, MAX_STRING_LENGTH, _T("����������:"), _T("ע�ᣨ���6���ַ���"), NULL);
				//����Ϊ��
				if (wcslen(newStudent.password) == 0) {
					MessageBox(hnd_SigninChooseGraph, _T("����Ϊ��"), _T("����"), MB_OK);
					continue;
				}
				//���ܰ�������
				if (wcschr(newStudent.password, L',')) {
					MessageBox(hnd_SigninChooseGraph, _T("���벻�ܰ�������"), _T("����"), MB_OK);
					continue;
				}
				//�����ظ�
				for (int i = 0; i < StudentMaxNum; i++) {
					if (wcscmp(newStudent.password, students[i].password) == 0) {
						MessageBox(hnd_SigninChooseGraph, _T("�����Ѵ��ڣ�����������"), _T("����"), MB_OK);
						continue;
					}
				}


				//����
				InputBox(newStudent.name, MAX_STRING_LENGTH, _T("����������:"), _T("ע�ᣨ���6���ַ���"), NULL);
				//����Ϊ��
				if (wcslen(newStudent.name) == 0) {
					MessageBox(hnd_SigninChooseGraph, _T("����Ϊ��"), _T("����"), MB_OK);
					continue;
				}
				//���ܰ�������
				if (wcschr(newStudent.name, L',')) {
					MessageBox(hnd_SigninChooseGraph, _T("�������ܰ�������"), _T("����"), MB_OK);
					continue;
				}


				//�Ա�
				InputBox(newStudent.gender, MAX_STRING_LENGTH, _T("�������Ա�:"), _T("ע�ᣨ���6���ַ���"), NULL);
				//����Ϊ��
				if (wcslen(newStudent.gender) == 0) {
					MessageBox(hnd_SigninChooseGraph, _T("����Ϊ��"), _T("����"), MB_OK);
					continue;
				}
				//���ܰ�������
				if (wcschr(newStudent.gender, L',')) {
					MessageBox(hnd_SigninChooseGraph, _T("�Ա��ܰ�������"), _T("����"), MB_OK);
					continue;
				}


				////����
				InputBox(newStudent.age, MAX_STRING_LENGTH, _T("����������:"), _T("ע�ᣨ���6���ַ���"), NULL);
				//����Ϊ��
				if (wcslen(newStudent.age) == 0) {
					MessageBox(hnd_SigninChooseGraph, _T("����Ϊ��"), _T("����"), MB_OK);
					continue;
				}
				//���ܰ�������
				if (wcschr(newStudent.age, L',')) {
					MessageBox(hnd_SigninChooseGraph, _T("���䲻�ܰ�������"), _T("����"), MB_OK);
					continue;
				}


				//�꼶
				InputBox(newStudent.grade, MAX_STRING_LENGTH, _T("�������꼶:"), _T("ע�ᣨ���6���ַ���"), NULL);
				//����Ϊ��
				if (wcslen(newStudent.grade) == 0) {
					MessageBox(hnd_SigninChooseGraph, _T("����Ϊ��"), _T("����"), MB_OK);
					continue;
				}
				//���ܰ�������
				if (wcschr(newStudent.grade, L',')) {
					MessageBox(hnd_SigninChooseGraph, _T("�꼶���ܰ�������"), _T("����"), MB_OK);
					continue;
				}


				//�༶
				InputBox(newStudent.classNum, MAX_STRING_LENGTH, _T("������༶:"), _T("ע�ᣨ���6���ַ���"), NULL);
				//����Ϊ��
				if (wcslen(newStudent.classNum) == 0) {
					MessageBox(hnd_SigninChooseGraph, _T("����Ϊ��"), _T("����"), MB_OK);
					continue;
				}
				//���ܰ�������
				if (wcschr(newStudent.classNum, L',')) {
					MessageBox(hnd_SigninChooseGraph, _T("�༶���ܰ�������"), _T("����"), MB_OK);
					continue;
				}

				newStudent.id = studentNum;

				students[studentNum] = newStudent;

				SaveStudentToFile();
				MessageBox(hnd_SigninChooseGraph, _T("ע��ɹ�"), _T("��ʾ"), MB_OK);
			}
			//����
			else if (IsMouseInRect(300, 400, 200, 50)) {
				WelcomeGraph();
				return;
			}
		}
	}
}

//�鿴ѧ����Ϣ����
void ViewStudentInfoGraph() {
	static int page = 1;
	cleardevice();
	LoadBgk();

	SetHeightText(25);
	settextcolor(BLACK);

	// ��ͷ����
	const TCHAR* headers[] = { _T("ID"), _T("�˺�"), _T("����"), _T("����"), _T("�Ա�"), _T("����"), _T("�꼶"), _T("�༶") };
	const int numCols = sizeof(headers) / sizeof(headers[0]);

	// ������λ�ã�������ʾ��
	const int tableX = 0;
	const int tableY = 75;
	const int cellWidth = 100;
	const int cellHeight = 40;
	const int tableWidth = cellWidth * numCols;
	const int tableHeight = cellHeight * (TABLE_ROWS + 1);

	// ���Ʊ�ͷ��������ɫ��
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

	// ���Ʊ����
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

	// ������ݣ�������ʾ��
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

		// ����ÿ�����ݣ����У�
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

	// ҳ����Ϣ���ײ����У�
	wchar_t pageInfo[50];
	swprintf_s(pageInfo, L"�� %d ҳ/�� %d ҳ", page, totalPages);
	RECT rPage = { tableX, tableY + tableHeight + 20, tableX + tableWidth, tableY + tableHeight + 50 };
	drawtext(pageInfo, &rPage, DT_CENTER | DT_VCENTER);

	// ��ҳ��ť����̬��ʾ��
	const int btnWidth = 80;
	const int btnHeight = 30;
	const int btnY = tableY + tableHeight + 20;

	if (page > 1) {
		DrawButton(tableX, btnY, btnWidth, btnHeight, _T("��һҳ"), 20);
	}
	if (page < totalPages) {
		DrawButton(tableX + tableWidth - btnWidth, btnY, btnWidth, btnHeight, _T("��һҳ"), 20);
	}

	// ���ذ�ť�����Ͻǣ�
	DrawButton(tableX + tableWidth - btnWidth, tableY - 50, btnWidth, btnHeight, _T("����"), 20);

	// �¼�����
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

//�޸�ѧ����Ϣ����
void ModifyStudentInfoGraph() {
	cleardevice();
	LoadBgk();
	SetHeightText(30);
	RECT r = { 0, 0, 800, 150 };
	drawtext(_T("��ѡ����Ҫ�޸ĵ���Ϣ��"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	HWND hnd_ModifyStudentInfoGraph = GetHWnd();
	SetWindowText(hnd_ModifyStudentInfoGraph, _T("ѧ����Ϣ�޸�"));

	//���ư�ť
	const int btnWidth = 150, btnHeight = 40;
	const int btnX = 300;
	DrawButton(btnX, 130, btnWidth, btnHeight, _T("�û���"), 30);
	DrawButton(btnX, 180, btnWidth, btnHeight, _T("����"), 30);
	DrawButton(btnX, 230, btnWidth, btnHeight, _T("����"), 30);
	DrawButton(btnX, 280, btnWidth, btnHeight, _T("����"), 30);
	DrawButton(btnX, 330, btnWidth, btnHeight, _T("�Ա�"), 30);
	DrawButton(btnX, 380, btnWidth, btnHeight, _T("�꼶"), 30);
	DrawButton(btnX, 430, btnWidth, btnHeight, _T("�༶"), 30);
	DrawButton(btnX, 480, btnWidth, btnHeight, _T("����"), 30);

	//����¼�����
	while (true) {
		MOUSEMSG msg = GetMouseMsg();
		if (msg.uMsg == WM_LBUTTONDOWN) {
			//�޸��û���
			if (IsMouseInRect(btnX, 130, btnWidth, btnHeight)) {
				for (int i = 0; i < StudentMaxNum; i++) {
					if (wcscmp(students[i].account, currentStudent.account) == 0 && wcscmp(students[i].password, currentStudent.password) == 0) {
						wchar_t newAccount[MAX_STRING_LENGTH];
						InputBox(newAccount, MAX_STRING_LENGTH, _T("�������µ��û���:"), _T("�޸��û���"), NULL);
						//����Ϊ��
						if (wcslen(newAccount) == 0) {
							MessageBox(hnd_ModifyStudentInfoGraph, _T("����Ϊ��"), _T("����"), MB_OK);
							continue;
						}
						//���ܰ�������
						if (wcschr(newAccount, L',')) {
							MessageBox(hnd_ModifyStudentInfoGraph, _T("�û������ܰ�������"), _T("����"), MB_OK);
							continue;
						}
						//������ԭ�û�����ͬ
						if (wcscmp(newAccount, currentStudent.account) == 0) {
							MessageBox(hnd_ModifyStudentInfoGraph, _T("�û���������ԭ�û�����ͬ"), _T("����"), MB_OK);
							continue;
						}
						//�Ѿ���ע��
						bool isDuplicate = false;
						for (int j = 0; j < StudentMaxNum; j++) {
							if (wcscmp(newAccount, students[j].account) == 0) {
								isDuplicate = true;
								break;
							}
						}
						if (isDuplicate) {
							MessageBox(hnd_ModifyStudentInfoGraph, _T("���û����ѱ�ʹ�ã�����������"), _T("����"), MB_OK);
							continue;
						}

						wcscpy_s(students[i].account, newAccount);
						MessageBox(hnd_ModifyStudentInfoGraph, _T("�޸ĳɹ�"), _T("��ʾ"), MB_OK);
						SaveStudentToFile();
						//���µ�ǰѧ����Ϣ
						currentStudent = students[i];
						break;
					}
				}
			}
			//�޸�����
			else if (IsMouseInRect(btnX, 180, btnWidth, btnHeight)) {
				for (int i = 0; i < StudentMaxNum; i++) {
					if (wcscmp(students[i].account, currentStudent.account) == 0 && wcscmp(students[i].password, currentStudent.password) == 0) {
						wchar_t newPassword[MAX_STRING_LENGTH];
						InputBox(newPassword, MAX_STRING_LENGTH, _T("�������µ�����:"), _T("�޸�����"), NULL);
						//����Ϊ��
						if (wcslen(newPassword) == 0) {
							MessageBox(hnd_ModifyStudentInfoGraph, _T("����Ϊ��"), _T("����"), MB_OK);
							continue;
						}
						//���ܰ�������
						if (wcschr(newPassword, L',')) {
							MessageBox(hnd_ModifyStudentInfoGraph, _T("���벻�ܰ�������"), _T("����"), MB_OK);
							continue;
						}
						//������ԭ������ͬ
						if (wcscmp(newPassword, currentStudent.password) == 0) {
							MessageBox(hnd_ModifyStudentInfoGraph, _T("���벻����ԭ������ͬ"), _T("����"), MB_OK);
							continue;
						}
						//�Ѿ���ע��
						bool isDuplicate = false;
						for (int j = 0; j < StudentMaxNum; j++) {
							if (wcscmp(newPassword, students[j].password) == 0) {
								isDuplicate = true;
								break;
							}
						}
						if (isDuplicate) {
							MessageBox(hnd_ModifyStudentInfoGraph, _T("�������ѱ�ʹ�ã�����������"), _T("����"), MB_OK);
							continue;
						}

						wcscpy_s(students[i].password, newPassword);
						MessageBox(hnd_ModifyStudentInfoGraph, _T("�޸ĳɹ�"), _T("��ʾ"), MB_OK);
						SaveStudentToFile();
						//���µ�ǰѧ����Ϣ
						currentStudent = students[i];
						break;
					}
				}
			}
			//�޸�����
			else if (IsMouseInRect(btnX, 230, btnWidth, btnHeight)) {
				for (int i = 0; i < StudentMaxNum; i++) {
					if (wcscmp(students[i].account, currentStudent.account) == 0 && wcscmp(students[i].password, currentStudent.password) == 0) {
						wchar_t newName[MAX_STRING_LENGTH];
						InputBox(newName, MAX_STRING_LENGTH, _T("�������µ�����:"), _T("�޸�����"), NULL);
						//����Ϊ��
						if (wcslen(newName) == 0) {
							MessageBox(hnd_ModifyStudentInfoGraph, _T("����Ϊ��"), _T("����"), MB_OK);
							continue;
						}
						//���ܰ�������
						if (wcschr(newName, L',')) {
							MessageBox(hnd_ModifyStudentInfoGraph, _T("�������ܰ�������"), _T("����"), MB_OK);
							continue;
						}
						//������ԭ������ͬ
						if (wcscmp(newName, currentStudent.name) == 0) {
							MessageBox(hnd_ModifyStudentInfoGraph, _T("����������ԭ������ͬ"), _T("����"), MB_OK);
							continue;
						}

						wcscpy_s(students[i].name, newName);
						MessageBox(hnd_ModifyStudentInfoGraph, _T("�޸ĳɹ�"), _T("��ʾ"), MB_OK);
						SaveStudentToFile();
						//���µ�ǰѧ����Ϣ
						currentStudent = students[i];
						break;
					}
				}
			}
			//�޸�����
			else if (IsMouseInRect(btnX, 280, btnWidth, btnHeight)) {
				for (int i = 0; i < StudentMaxNum; i++) {
					if (wcscmp(students[i].account, currentStudent.account) == 0 && wcscmp(students[i].password, currentStudent.password) == 0) {
						wchar_t newAge[MAX_STRING_LENGTH];
						InputBox(newAge, MAX_STRING_LENGTH, _T("�������µ�����:"), _T("�޸�����"), NULL);
						//����Ϊ��
						if (wcslen(newAge) == 0) {
							MessageBox(hnd_ModifyStudentInfoGraph, _T("����Ϊ��"), _T("����"), MB_OK);
							continue;
						}
						//���ܰ�������
						if (wcschr(newAge, L',')) {
							MessageBox(hnd_ModifyStudentInfoGraph, _T("���䲻�ܰ�������"), _T("����"), MB_OK);
							continue;
						}
						//������ԭ������ͬ
						if (wcscmp(newAge, currentStudent.age) == 0) {
							MessageBox(hnd_ModifyStudentInfoGraph, _T("���䲻����ԭ������ͬ"), _T("����"), MB_OK);
							continue;
						}

						wcscpy_s(students[i].age, newAge);
						MessageBox(hnd_ModifyStudentInfoGraph, _T("�޸ĳɹ�"), _T("��ʾ"), MB_OK);
						SaveStudentToFile();
						//���µ�ǰѧ����Ϣ
						currentStudent = students[i];
						break;
					}
				}
			}
			//�޸��Ա�
			else if (IsMouseInRect(btnX, 330, btnWidth, btnHeight)) {
				for (int i = 0; i < StudentMaxNum; i++) {
					if (wcscmp(students[i].account, currentStudent.account) == 0 && wcscmp(students[i].password, currentStudent.password) == 0) {
						wchar_t newGender[MAX_STRING_LENGTH];
						InputBox(newGender, MAX_STRING_LENGTH, _T("�������µ��Ա�:"), _T("�޸��Ա�"), NULL);
						//����Ϊ��
						if (wcslen(newGender) == 0) {
							MessageBox(hnd_ModifyStudentInfoGraph, _T("����Ϊ��"), _T("����"), MB_OK);
							continue;
						}
						//���ܰ�������
						if (wcschr(newGender, L',')) {
							MessageBox(hnd_ModifyStudentInfoGraph, _T("�Ա��ܰ�������"), _T("����"), MB_OK);
							continue;
						}
						//������ԭ�Ա���ͬ
						if (wcscmp(newGender, currentStudent.gender) == 0) {
							MessageBox(hnd_ModifyStudentInfoGraph, _T("�Ա�����ԭ�Ա���ͬ"), _T("����"), MB_OK);
							continue;
						}

						wcscpy_s(students[i].gender, newGender);
						MessageBox(hnd_ModifyStudentInfoGraph, _T("�޸ĳɹ�"), _T("��ʾ"), MB_OK);
						SaveStudentToFile();
						//���µ�ǰѧ����Ϣ
						currentStudent = students[i];
						break;
					}
				}
			}
			//�޸��꼶
			else if (IsMouseInRect(btnX, 380, btnWidth, btnHeight)) {
				for (int i = 0; i < StudentMaxNum; i++) {
					if (wcscmp(students[i].account, currentStudent.account) == 0 && wcscmp(students[i].password, currentStudent.password) == 0) {
						wchar_t newGrade[MAX_STRING_LENGTH];
						InputBox(newGrade, MAX_STRING_LENGTH, _T("�������µ��꼶:"), _T("�޸��꼶"), NULL);
						//����Ϊ��
						if (wcslen(newGrade) == 0) {
							MessageBox(hnd_ModifyStudentInfoGraph, _T("����Ϊ��"), _T("����"), MB_OK);
							continue;
						}
						//���ܰ�������
						if (wcschr(newGrade, L',')) {
							MessageBox(hnd_ModifyStudentInfoGraph, _T("�꼶���ܰ�������"), _T("����"), MB_OK);
							continue;
						}
						//������ԭ�꼶��ͬ
						if (wcscmp(newGrade, currentStudent.grade) == 0) {
							MessageBox(hnd_ModifyStudentInfoGraph, _T("�꼶������ԭ�꼶��ͬ"), _T("����"), MB_OK);
							continue;
						}

						wcscpy_s(students[i].grade, newGrade);
						MessageBox(hnd_ModifyStudentInfoGraph, _T("�޸ĳɹ�"), _T("��ʾ"), MB_OK);
						SaveStudentToFile();
						//���µ�ǰѧ����Ϣ
						currentStudent = students[i];
						break;
					}
				}
			}
			//�޸İ༶
			else if (IsMouseInRect(btnX, 430, btnWidth, btnHeight)) {
				for (int i = 0; i < StudentMaxNum; i++) {
					if (wcscmp(students[i].account, currentStudent.account) == 0 && wcscmp(students[i].password, currentStudent.password) == 0) {
						wchar_t newClassNum[MAX_STRING_LENGTH];
						InputBox(newClassNum, MAX_STRING_LENGTH, _T("�������µİ༶:"), _T("�޸İ༶"), NULL);
						//����Ϊ��
						if (wcslen(newClassNum) == 0) {
							MessageBox(hnd_ModifyStudentInfoGraph, _T("����Ϊ��"), _T("����"), MB_OK);
							continue;
						}
						//���ܰ�������
						if (wcschr(newClassNum, L',')) {
							MessageBox(hnd_ModifyStudentInfoGraph, _T("�༶���ܰ�������"), _T("����"), MB_OK);
							continue;
						}
						//������ԭ�༶��ͬ
						if (wcscmp(newClassNum, currentStudent.classNum) == 0) {
							MessageBox(hnd_ModifyStudentInfoGraph, _T("�༶������ԭ�༶��ͬ"), _T("����"), MB_OK);
							continue;
						}

						wcscpy_s(students[i].classNum, newClassNum);
						MessageBox(hnd_ModifyStudentInfoGraph, _T("�޸ĳɹ�"), _T("��ʾ"), MB_OK);
						SaveStudentToFile();
						//���µ�ǰѧ����Ϣ
						currentStudent = students[i];
						break;
					}
				}
			}
			//����
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

//��ӭ����
void WelcomeGraph() {
	cleardevice();
	LoadBgk();
	SetHeightText(30);
	RECT r = { 0, 0, 800, 150 };
	drawtext(_T("��ӭʹ��ѧ������ϵͳ!"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	HWND hnd_WelcomeGraph = GetHWnd();
	SetWindowText(hnd_WelcomeGraph, _T("��ӭʹ��ѧ������ϵͳ!"));

	//���ư�ť
	const int btnWidth = 200, btnHeight = 50;
	const int btnX = 300;
	DrawButton(btnX, 290, btnWidth, btnHeight, _T("��¼"), 30);
	DrawButton(btnX, 360, btnWidth, btnHeight, _T("ע��"), 30);
	DrawButton(btnX, 430, btnWidth, btnHeight, _T("�˳�"), 30);

	//����¼�����
	while (true) {
		MOUSEMSG msg = GetMouseMsg();
		if (msg.uMsg == WM_LBUTTONDOWN) {
			//��¼
			if (IsMouseInRect(btnX, 290, btnWidth, btnHeight)) {

				wchar_t username[MAX_STRING_LENGTH], password[MAX_STRING_LENGTH];

				InputBox(username, MAX_STRING_LENGTH, _T("�������û���:"), _T("��¼"), NULL);
				//����Ϊ��
				if (wcslen(username) == 0) {
					MessageBox(hnd_WelcomeGraph, _T("����Ϊ��"), _T("����"), MB_OK);
					continue;
				}

				InputBox(password, MAX_STRING_LENGTH, _T("����������:"), _T("��¼"), NULL);
				//����Ϊ��
				if (wcslen(password) == 0) {
					MessageBox(hnd_WelcomeGraph, _T("����Ϊ��"), _T("����"), MB_OK);
					continue;
				}

				switch (LoginCheck(username, password)) {
				case 1:
					MessageBox(hnd_WelcomeGraph, _T("����Ա��¼�ɹ�"), _T("��ʾ"), MB_OK);
					//��¼��ǰ����Ա�˺�
					for (int i = 0; i < AdminMaxNum; i++) {
						if (wcscmp(admins[i].account, username) == 0 && wcscmp(admins[i].password, password) == 0) {
							currentAdmin = admins[i];
							break;
						}
					}
					AdminManageGraph();
					return;
				case 2:
					MessageBox(hnd_WelcomeGraph, _T("ѧ����¼�ɹ�"), _T("��ʾ"), MB_OK);
					//��¼��ǰѧ���˺�
					for (int i = 0; i < StudentMaxNum; i++) {
						if (wcscmp(students[i].account, username) == 0 && wcscmp(students[i].password, password) == 0) {
							currentStudent = students[i];
							break;
						}
					}
					StudentManageGraph();
					return;
				case 0:
					MessageBox(hnd_WelcomeGraph, _T("�û������������"), _T("����"), MB_OK);
				}
			}
			//ע��
			else if (IsMouseInRect(btnX, 360, btnWidth, btnHeight)) {
				SigninChooseGraph();
				return;
			}
			//�˳�
			else if (IsMouseInRect(btnX, 430, btnWidth, btnHeight)) {
				exit(0);
			}
		}
	}
}
