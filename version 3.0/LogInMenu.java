package studentManageSystem;

import java.util.*;

public class LogInMenu extends Menu {
    public LogInMenu(Scanner scanner) {
        super(
                new String[] { "Log In", "Register CommonUser", "Forget Password", "Exit" },
                null,
                Type.LOGIN);
        List<Runnable> functions = new ArrayList<>();
        functions.add(() -> logIn(scanner));
        functions.add(() -> registerCommonUser(scanner));
        functions.add(() -> forgetPassword(scanner));
        functions.add(() -> goBack(scanner));
        this.functions = functions;
    }

    private void logIn(Scanner scanner) {
        ConsoleColor.println(ConsoleColor.GREEN, "Please log in:");

        ConsoleColor.print(ConsoleColor.GREEN, "Enter username: ");
        String username = scanner.nextLine();

        User user = User.getUserByUsername(SystemTest.userList, username);
        if (user == null) {
            ConsoleColor.println(ConsoleColor.RED, "User does not exist. Please register first.");
            return;
        }
        if (user.isLocked()) {
            ConsoleColor.println(ConsoleColor.RED, "User is locked. Please contact the administrator.");
            return;
        }

        ConsoleColor.print(ConsoleColor.GREEN, "Enter password: ");
        String password = scanner.nextLine();

        int attempts = 3;
        while (!user.getPassword().equals(password)) {
            if (attempts == 0) {
                ConsoleColor.println(ConsoleColor.RED, "Too many failed attempts. User is locked.");
                user.setLocked(true);
                return;
            } else if (attempts > 0) {
                ConsoleColor.print(ConsoleColor.RED,
                        "Wrong password. You have " + attempts + " attempts left. Please try again: ");
                attempts--;
                password = scanner.nextLine();
            }
        }

        StringBuilder sb = new StringBuilder();
        Random random = new Random();
        sb.append(random.nextInt(10));
        for (int i = 0; i < 4; i++) {
            char c;
            if (random.nextBoolean()) {
                c = (char) (random.nextInt(26) + 'a');
            } else {
                c = (char) (random.nextInt(26) + 'A');
            }
            sb.append(c);
        }
        for (int i = 0; i < sb.length(); i++) {
            int j = random.nextInt(sb.length());
            char temp = sb.charAt(i);
            sb.setCharAt(i, sb.charAt(j));
            sb.setCharAt(j, temp);
        }

        ConsoleColor.println(ConsoleColor.GREEN, "Your verification code: " + sb.toString());

        ConsoleColor.print(ConsoleColor.GREEN, "Enter verification code: ");
        String verificationCode = scanner.nextLine();

        while (!verificationCode.equalsIgnoreCase(sb.toString())) {
            ConsoleColor.print(ConsoleColor.RED, "Verification code is incorrect, Please enter again: ");
            verificationCode = scanner.nextLine();
        }
        currentUser = user;
        ConsoleColor.println(ConsoleColor.GREEN, "Login successful! Welcome " + user.getUsername() + "!");
        SystemTest.currentMenu = this.childrens.get(0);
    }

    private void registerCommonUser(Scanner scanner) {
        Menu.registerUser(scanner, User.Permission.COMMONUSER);
    }

    private void forgetPassword(Scanner scanner) {
        ConsoleColor.print(ConsoleColor.GREEN, "Enter username: ");
        String username = scanner.nextLine();

        User user = User.getUserByUsername(SystemTest.userList, username);
        if (user == null) {
            ConsoleColor.println(ConsoleColor.RED, "User does not exist. Please register first.");
            return;
        }

        ConsoleColor.print(ConsoleColor.GREEN, "Enter ID number: ");
        String idNumber = scanner.nextLine();

        ConsoleColor.print(ConsoleColor.GREEN, "Enter phone number: ");
        String phoneNumber = scanner.nextLine();

        if (!user.getIdNumber().equals(idNumber) || !user.getPhoneNumber().equals(phoneNumber)) {
            ConsoleColor.println(ConsoleColor.RED, "Account information does not match. Modification failed.");
            return;
        }
        ConsoleColor.print(ConsoleColor.GREEN, "Enter new password: ");
        String newPassword = scanner.nextLine();
        while (!Check.checkPassword(newPassword)) {
            ConsoleColor.print(ConsoleColor.RED, "Invalid password. Please enter a new password: ");
            newPassword = scanner.nextLine();
        }
        user.setPassword(newPassword);
        ConsoleColor.println(ConsoleColor.GREEN, "Password modified successfully!");
        ConsoleColor.println(ConsoleColor.GREEN, "Please log in again.");
    }
}