### version 1.0:

开发环境 Visual Studio 2022 + EasyX

该版主要从图形化界面着手,练习了图形库方法的调用,避免了相对枯燥的Terminal

双击编译好的main.exe(Release文件下)

------

### version 2.0：

开发环境：VScode + Windows + GCC

该版在第一版的基础上,拓展了功能(在终端运行),并尝试面向对象的思想对Menu进行封装,但出现事件循环的处理堆积和Menu的统一化处理很差

编译方法：打开本项目文件夹，右击空白处打开powershell，输入该命令行指令：gcc main.c event.c file.c login.c menu.c search.c log.c score.c -o main.exe 并回车，即可生成 main.exe

双击运行 main.exe 即可 (Tips: account.txt, student.txt, logInfo.txt 必须同属一个文件夹下!)

------

### version 3.0

开发环境: VScode + JDK.24.0.1

该版充分从Java独到的oop特性入手,加强对Menu的封装,大道至简,并进一步运用继承,多态,重写,重载等oop特点,使得代码的通用性和延展性更佳

使用方法:定位到package所在文件夹,即student-manage-system\studentManageSystem\version 3.0

右击打开powershell,输入以下命令:

编译(生成class文件): javac -d . studentManageSystem/*.java

运行: java studentManageSystem.SystemTest