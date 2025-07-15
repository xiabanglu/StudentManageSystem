package studentManageSystem;

import java.util.*;

public class SystemTest {
    public static ArrayList<User> userList = new ArrayList<>();
    public static ArrayList<Student> studentList = new ArrayList<>();
    public static Menu currentMenu = new Menu();

    public static void main(String[] args) {
        try (Scanner scanner = new Scanner(System.in)) {
            ConsoleColor.println(ConsoleColor.GREEN, "Welcome to the Student Management System!");
            Menu loginMenu = new LogInMenu(scanner);
            Menu functionChoiceMenu = new FunctionChoiceMenu(scanner);
            Menu studentManageMenu = new StudentManageMenu(scanner);
            Menu accountManageMenu = new AccountManageMenu(scanner);
            loginMenu.addChild(functionChoiceMenu);
            loginMenu.setParent(null);
            functionChoiceMenu.addChild(studentManageMenu);
            functionChoiceMenu.addChild(accountManageMenu);

            currentMenu = loginMenu;
            while (true) {
                currentMenu.runMenu(scanner);
            }
        }
    }
}
// 编译
// javac -d . studentManageSystem/*.java
// 运行
// java studentManageSystem.SystemTest