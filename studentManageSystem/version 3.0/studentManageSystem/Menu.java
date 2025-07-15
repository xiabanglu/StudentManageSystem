package studentManageSystem;

import java.util.*;

public class Menu {
    public enum Type {
        LOGIN, FUNCTIONCHOICE, STUDENTMANAGE, ACCOUNTMANAGE
    }

    public String[] descriptions;
    public char[] options;
    public List<Runnable> functions;
    public int choiceCount;
    public Type menuType;
    public User currentUser;

    public Menu parent;
    public List<Menu> childrens;

    public Menu() {
        this.descriptions = new String[0];
        this.options = new char[0];
        this.functions = new ArrayList<>();
        this.choiceCount = 0;
        this.menuType = null;
        this.currentUser = null;
        this.parent = null;
        this.childrens = new ArrayList<>();
    }

    public Menu(String[] descriptions, List<Runnable> functions, Type menuType) {
        this.descriptions = descriptions;
        this.choiceCount = descriptions.length;
        this.options = new char[choiceCount];
        for (int i = 0; i < choiceCount; i++) {
            options[i] = Character.toLowerCase(descriptions[i].charAt(0));
        }
        this.functions = functions;
        this.menuType = menuType;
        this.currentUser = null;
        this.parent = null;
        this.childrens = new ArrayList<>();
    }

    public void runMenu(Scanner scanner) {
        displayMenu();
        getChoice(scanner);
    }

    public void displayMenu() {
        ConsoleColor.println(ConsoleColor.YELLOW, "-------------------------------------------");
        ConsoleColor.println(ConsoleColor.YELLOW,
                "Welcome to the " + this.menuType.toString().toLowerCase() + " Menu!");
        for (int i = 0; i < descriptions.length; i++) {
            ConsoleColor.println(ConsoleColor.YELLOW, options[i] + ": " + descriptions[i]);
        }
        ConsoleColor.println(ConsoleColor.YELLOW, "-------------------------------------------");
    }

    public void getChoice(Scanner scanner) {
        char choice;
        ConsoleColor.print(ConsoleColor.GREEN, "Please enter your choice: ");
        choice = scanner.next().charAt(0);
        scanner.nextLine();
        for (int i = 0; i < choiceCount; i++) {
            if (choice == options[i]) {
                functions.get(i).run();
                return;
            }
        }
        ConsoleColor.println(ConsoleColor.RED, "Invalid choice, please try again.");
    }

    public void goBack(Scanner scanner) {
        if (this.getParent() == null) {
            ConsoleColor.println(ConsoleColor.GREEN, "Exiting the system. Goodbye!");
            System.exit(0);
        } else {
            if (this.getParent().getMenuType() == Type.LOGIN) {
                resetCurrentUser();
            }
            SystemTest.currentMenu = this.getParent();
            ConsoleColor.println(ConsoleColor.GREEN,
                    "Come back to " + SystemTest.currentMenu.getMenuType().toString().toLowerCase() + " menu...");
        }
    }

    public static void registerUser(Scanner scanner, User.Permission permission) {
        ConsoleColor.println(ConsoleColor.GREEN, "Please register:");

        ConsoleColor.print(ConsoleColor.GREEN, "Enter username: ");
        String username = scanner.nextLine();
        while (!Check.checkUsername(username)) {
            username = scanner.nextLine();
        }

        ConsoleColor.print(ConsoleColor.GREEN, "Enter password: ");
        String password = scanner.nextLine();
        while (!Check.checkPassword(password)) {
            password = scanner.nextLine();
        }

        ConsoleColor.print(ConsoleColor.GREEN, "Re-enter password: ");
        String confirmPassword = scanner.nextLine();

        while (!confirmPassword.equals(password)) {
            ConsoleColor.print(ConsoleColor.RED, "Passwords do not match. Please re-enter password: ");
            confirmPassword = scanner.nextLine();
        }

        ConsoleColor.print(ConsoleColor.GREEN, "Enter ID number: ");
        String idNumber = scanner.nextLine();
        while (!Check.checkIdNumber(idNumber)) {
            idNumber = scanner.nextLine();
        }

        ConsoleColor.print(ConsoleColor.GREEN, "Enter phone number: ");
        String phoneNumber = scanner.nextLine();
        while (!Check.checkPhoneNumber(phoneNumber)) {
            phoneNumber = scanner.nextLine();
        }

        User newUser = new User(username, password, idNumber, phoneNumber, permission,
                false);
        SystemTest.userList.add(newUser);
        ConsoleColor.println(ConsoleColor.GREEN, "Registration successful! You can now log in.");
    }

    public String[] getDescriptions() {
        return descriptions;
    }

    public char[] getOptions() {
        return options;
    }

    public int getChoiceCount() {
        return choiceCount;
    }

    public Type getMenuType() {
        return menuType;
    }

    public void setCurrentUser(User user) {
        this.currentUser = user;
    }

    public void resetCurrentUser() {
        this.currentUser = null;
    }

    public User getCurrentUser() {
        return currentUser;
    }

    public void setParent(Menu parent) {
        this.parent = parent;
    }

    public void addChild(Menu child) {
        child.setParent(this);
        this.childrens.add(child);
    }

    public Menu getParent() {
        return parent;
    }

    public List<Menu> getChildren() {
        return childrens;
    }
}