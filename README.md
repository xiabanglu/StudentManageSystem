# studentManageSystem（接下来需求按需修改，需求修改文档可以就写在这里）

# 学生管理系统

 

## 1 系统分析

### 1.1 应用系统简介

#### 需求

为了方便管理学生的信息，拟开发一款学生管理系统，其中需要实现：

1. 登录，注册（分为管理员和学生）
2. 简洁明了的图形界面，界面间的切换，中途给出适当的弹窗提示信息指引
3. 管理员界面需要实现指定学生管理操作以及账号管理
4. 学生界面需要实现对自己信息和账号的管理
5. 在实际应用中，需要对用户（管理员和学生）数据进行持久化保存，使得程序重启后仍然能够记录信息

#### 约束

1. 由于技术和时间限制，在注册功能中暂未实现用户名密码与信息的注册分离
2. 管理员信息的查询和修改暂未实现
3. 对指定学生的修改以及删除只实现了通过用户名搜索，未实现模糊搜索
4. 信息展示表格以及窗口大小无法适配实际信息内容长度
5. 由于未使用链表以及线性表等数据结构，对新用户的录入和注册只能在数据最后一行添加，而未能从指定位置添加
6. 按钮悬停变色功能由于技术限制被砍掉，影响程序性能
7. 界面切换存在延迟，影响用户体验

### 1.2 系统需求（功能）分析

1. 主界面：登录，注册（分为管理员和学生）
2. 注册界面：选择注册用户类型
3. 管理员界面：实现对学生的增删查改以及对本账号的注销
4. 学生界面：实现查看以及修改自己的信息以及对本账号的注销
5. 学生信息总览界面：展示所有学生信息
6. 学生信息修改界面：展示一行学生信息
7. 持久化保存：对用户（管理员和学生）数据进行持久化保存，使得程序重启后仍然能够记录信息

## 2 系统设计

### 2.1 总体设计

#### 主界面（欢迎界面）：

1. 登录：输入用户名和密码，登录成功后分别跳转到管理员和学生界面
2. 注册：进入注册界面，选择并创建新的管理员和学生账号
3. 退出：退出程序

#### 注册界面：

1. 管理员：弹窗注册管理员
2. 学生：弹窗注册学生
3. 返回：返回主界面（欢迎界面）

#### 管理员界面：

1. 录入学生信息：弹窗输入新角色信息
2. 删除学生信息：弹窗输入用户名指定删除哪位学生的信息
3. 修改学生信息：弹窗输入用户名指定修改哪位学生的信息，并跳转到学生信息修改界面
4. 查看学生信息：跳转到学生信息总览界面
5. 注销我的账号：删除账号信息，并返回主界面（欢迎界面）
6. 返回：返回主界面（欢迎界面）

#### 学生界面：

1. 查看我的信息：跳转到新界面，只有一行信息表格
2. 修改我的信息：跳转到学生信息修改界面
3. 注销我的账号：删除账号信息，并返回主界面（欢迎界面）
4. 返回：返回主界面（欢迎界面）

#### 学生信息总览界面：

1. 上一页/下一页：可翻页查看，每页十条学生信息
2. 返回：返回管理员界面

#### 学生信息修改界面：

1. 列举7个学生属性值：选择想要修改的信息
2. 返回：返回学生界面

### 2.2 详细设计

#### 2.2.1 数据结构设计

一方面数据操作采用结构体数组，分两种：

```c
//管理员结构体
typedef struct Admin {
    int id;
    wchar_t account[20];
    wchar_t password[20];
} Admin;

//学生结构体
typedef struct Student {
    int id;
    wchar_t account[20];
    wchar_t password[20];
    wchar_t name[20];
    wchar_t gender[20];
    wchar_t age[20];
    wchar_t grade[20];
    wchar_t classNum[20];
} Student;
```

另一方面数据的持久化保存采用文本文件(.txt)，如:

```
//管理员信息
//id,account,password
0,xbl666,123456
1,jjc666,123456
......

//学生信息
//id,account,password,name,gender,age,grade,classNum
0,aether,111111,空,男,500岁左右,旅行者,异界
1,lumine,222222,荧,女,500岁左右,旅行者,异界
2,kaeya,555555,凯亚,男,21 - 22岁,骑兵队长,蒙德
3,lisa,666666,lisa44,女,28岁,图书管理员,蒙德
4,barbara,777777,芭芭拉,女,16 - 18岁,祈礼牧师,蒙德
5,razor,888888,雷泽,男,16岁,狼人,蒙德
6,xiangling,999999,香菱,女,14岁,厨师,璃月
7,beidou,101010,北斗,女,21 - 27岁,船长,璃月
8,xingqiu,111111,行秋,男,18 - 20岁,飞云商会二少爷,璃月
9,ningguang,121212,凝光,女,26岁,璃月七星之一,璃月
10,fischl,131313,菲谢尔,女,16岁,冒险家,蒙德
11,bennett,141414,班尼特,男,18岁,冒险家,蒙德
12,noelle,151515,诺艾尔,女,15岁,女仆,蒙德
13,zhongyun,161616,重云,男,18 - 20岁,驱邪方士,璃月
14,sucrose,171717,砂糖,女,18岁,炼金术士,蒙德
15,qin,181818,琴,女,19岁,西风骑士团团长,蒙德
16,diluc,191919,迪卢克,男,22岁,晨曦酒庄庄主,蒙德
17,venti,202020,温迪,男,3000岁左右,吟游诗人,蒙德
18,keqing,212121,刻晴,女,18 - 19岁,璃月七星之一,璃月
19,monad,222222,莫娜,女,19岁,占星术士,蒙德
20,hu tao,232323,胡桃,女,16岁,往生堂堂主,璃月
21,baizhu,242424,白术,男,？,不卜庐老板,璃月
22,qiqi,252525,七七,女,500岁左右,僵尸,璃月
23,yanfei,262626,烟绯,女,50岁,律法咨询师,璃月
24,yelan,272727,夜兰,女,？,情报官,璃月
25,aether,282828,埃洛伊,女,19岁,猎人,异界
26,chongyun,292929,重云,男,18 - 20岁,驱邪方士,璃月
27,yunjin,303030,云堇,女,18 - 20岁,戏班名角,璃月
28,gorou,313131,五郎,男,18 - 22岁,海祈军将领,稻妻
29,ayaka,323232,神里绫华,女,19 - 22岁,社奉行家主,稻妻
30,xingqiu,333333,行秋,男,18 - 20岁,飞云商会二少爷,璃月
......
```

#### 2.2.2 主要函数设计

```c
//函数调用视具体情况而定，不一一介绍
//算法就是没有算法

//计算管理员数量（学生同理）
int CountAdminNum() {
    int count = 0;
    while (admins[count].id != -1 && count < AdminMaxNum) count++;
    return count;
}
//从文件中加载管理员信息（学生同理）
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
//保存管理员信息到文件（学生同理）
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
//初始化窗口
void LoadBgk() {
    loadimage(&img, _T("bk.jpg"));
    putimage(0, 0, &img);
    setbkmode(TRANSPARENT);
    settextcolor(BLACK);
}
//设置字体
void SetHeightText(int height) {
    LOGFONT font;
    gettextstyle(&font);
    font.lfHeight = height;
    font.lfWeight = FW_MEDIUM;
    _tcscpy_s(font.lfFaceName, _T("黑体"));
    font.lfQuality = ANTIALIASED_QUALITY;
    settextstyle(&font);
}
//绘制按钮
void DrawButton(int x, int y, int width, int height, const wchar_t* text, int fontsize) {
    setfillcolor(RGB(173, 216, 230));
    solidrectangle(x, y, x + width, y + height);
    SetHeightText(fontsize);
    RECT r = { x, y, x + width, y + height };
    drawtext(text, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}
//绘制表格
void DrawTable(int x, int y, int width, int height, int rows, int cols) {
	setlinecolor(BLACK);
	for (int i = 0; i <= rows; i++) {
		line(x, y + i * height / rows, x + width, y + i * height / rows);
	}
	for (int j = 0; j <= cols; j++) {
		line(x + j * width / cols, y, x + j * width / cols, y + height);
	}
}
//判断鼠标是否在按钮上
bool IsMouseInRect(int x, int y, int width, int height) {
    MOUSEMSG msg = GetMouseMsg();
    return msg.x >= x && msg.x <= x + width && msg.y >= y && msg.y <= y + height;
}
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

//下面的界面函数过于冗杂，不一一展示

//学生界面
void StudentManageGraph();
//管理员界面
void AdminManageGraph();
//主界面（欢迎界面）
void WelcomeGraph();
//注册选择界面
void SigninChooseGraph();
//修改学生信息界面
void ModifyStudentInfoGraph();
//学生信息总览界面
void ViewStudentInfoGraph();
```

## 3 系统实现

### 3.1 系统开发环境

开发环境：Visual Studio 2022 ；配置EasyX库

### 3.2 程序编码

逐个界面，按功能模块逐步开发：

分为：

1. 头文件实现函数声明，宏定义，初始化
2. 源文件实现函数定义

```c
//程序入口
int main() {
    initgraph(WIN_WIDTH, WIN_HEIGHT);
    setlocale(LC_ALL, "");
    FreeConsole();
    LoadStudentFromFile();
    LoadAdminFromFile();
    WelcomeGraph();
    closegraph();
    return 0;
}
//函数声明总览
void LoadAdminFromFile();
void SaveAdminToFile();
int CountAdminNum();
void LoadStudentFromFile();
void SaveStudentToFile();
int CountStudentNum();
void LoadBgk();
void SetHeightText(int height);
void DrawButton(int x, int y, int width, int height, const wchar_t* text, int fontsize);
void DrawTable(int x, int y, int width, int height, int rows, int cols);
bool IsMouseInRect(int x, int y, int width, int height);
void StudentManageGraph();
void AdminManageGraph();
void WelcomeGraph();
void SigninChooseGraph();
int LoginCheck(const wchar_t* username, const wchar_t* password);
void ModifyStudentInfoGraph();
void ViewStudentInfoGraph();
```

## 4 系统测试

经测试，程序功能完好（暂略）

## 5 总结与体会

### 问题及解决方法

1. 编码问题,默认UTF-8

2. 字符串用宽字符wchar_t，以便兼容内置的弹窗函数Inputbox

3. 文件管理函数不安全问题

4. 模块实现预览不方便，程序很难跑起来

   ......

### 优点与缺点

#### 优点

   简洁明了的图形界面，界面间的切换，中途给出适当的弹窗提示信息指引

#### 缺点

1. 由于技术和时间限制，在注册功能中暂未实现用户名密码与信息的注册分离
2. 管理员信息的查询和修改暂未实现
3. 对指定学生的修改以及删除只实现了通过用户名搜索，未实现模糊搜索
4. 信息展示表格以及窗口大小无法适配实际信息内容长度
5. 由于未使用链表以及线性表等数据结构，对新用户的录入和注册只能在数据最后一行添加，而未能从指定位置添加
6. 按钮悬停变色功能由于技术限制被砍掉，影响程序性能
7. 界面切换存在延迟，影响用户体验

### 收获与体会

1. 从0开始通过查阅各种形式资料，独立开发一款程序十分有成就感
2. 修改BUG让我们乐在其中
3. 熟练了C语言语法和面向过程的特性
4. 掌握了EasyX库函数的使用，脱离了枯燥乏味的控制台黑色窗口

## **参考文献：** 3篇左右，按要求书写

[1] [EasyX 文档 - 基本说明](https://docs.easyx.cn/zh-cn/intro)

[2] [C++学生成绩管理系统，搭配Easyx拥有清晰简约，低调奢华的界面，如此详细的教学，学不会算我输~_哔哩哔哩_bilibili](https://www.bilibili.com/video/BV1uf4y1L75v/?spm_id_from=333.337.search-card.all.click&vd_source=a7561d8dca0c6c7902b5868594759d5f)

[3] 暂无
