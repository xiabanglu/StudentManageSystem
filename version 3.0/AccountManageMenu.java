package studentManageSystem;

import java.util.*;

public class AccountManageMenu extends Menu {
    public AccountManageMenu(Scanner scanner) {
        super(
                new String[] { "Register Account", "Delete Account", "View Account", "Update Account", "Back" }, null,
                Menu.Type.ACCOUNTMANAGE);
        List<Runnable> functions = new ArrayList<>();
        functions.add(() -> registerAccount(scanner));
        functions.add(() -> deleteAccount(scanner));
        functions.add(() -> viewAccount(scanner));
        functions.add(() -> updateAccount(scanner));
        functions.add(() -> goBack(scanner));
        this.functions = functions;
    }

    private void registerAccount(Scanner scanner) {
        ConsoleColor.println(ConsoleColor.GREEN, "What level of user do you want to register?");
        ConsoleColor.println(ConsoleColor.YELLOW, "1. Common User");
        ConsoleColor.println(ConsoleColor.YELLOW, "2. Admin User");
        ConsoleColor.println(ConsoleColor.YELLOW, "3. Developer User");
        ConsoleColor.print(ConsoleColor.GREEN, "Please enter your choice (1 or 2 or 3): ");
        int choice = scanner.nextInt();
        scanner.nextLine();

        User.Permission[] permissions = { User.Permission.COMMONUSER, User.Permission.ADMIN,
                User.Permission.DEVELOPER };

        if (choice < 1 || choice > permissions.length) {
            ConsoleColor.println(ConsoleColor.RED, "Invalid choice. Please try again.");
            return;
        }
        User.Permission permission = permissions[choice - 1];
        Menu.registerUser(scanner, permission);
    }

    private void deleteAccount(Scanner scanner) {
        ConsoleColor.println(ConsoleColor.GREEN, "Please enter the username of the account you want to delete:");
        String username = scanner.nextLine();
        User user = User.getUserByUsername(SystemTest.userList, username);
        if (user == null) {
            ConsoleColor.println(ConsoleColor.RED, "User does not exist. Please try again.");
            return;
        }
        ConsoleColor.println(ConsoleColor.GREEN, "Are you sure you want to delete this account? (Y/N)");
        String confirm = scanner.nextLine();
        if (confirm.equalsIgnoreCase("Y")) {
            SystemTest.userList.remove(user);
            ConsoleColor.println(ConsoleColor.GREEN, "Account deleted successfully!");
        } else {
            ConsoleColor.println(ConsoleColor.GREEN, "Deletion cancelled.");
        }
    }

    private void viewAccount(Scanner scanner) {
        ConsoleColor.println(ConsoleColor.GREEN, "Please enter the username of the account you want to view:");
        String username = scanner.nextLine();
        User user = User.getUserByUsername(SystemTest.userList, username);
        if (user == null) {
            ConsoleColor.println(ConsoleColor.RED, "User does not exist. Please try again.");
            return;
        }
        ConsoleColor.println(ConsoleColor.GREEN, "Username: " + user.getUsername());
        ConsoleColor.println(ConsoleColor.GREEN, "ID Number: " + user.getIdNumber());
        ConsoleColor.println(ConsoleColor.GREEN, "Phone Number: " + user.getPhoneNumber());
        ConsoleColor.println(ConsoleColor.GREEN, "Permission: " + user.getPermission());
        ConsoleColor.println(ConsoleColor.GREEN, "Locked: " + user.isLocked());
    }

    private void updateAccount(Scanner scanner) {
        ConsoleColor.println(ConsoleColor.GREEN, "Please enter the username of the account you want to update:");
        String username = scanner.nextLine();
        User user = User.getUserByUsername(SystemTest.userList, username);
        if (user == null) {
            ConsoleColor.println(ConsoleColor.RED, "User does not exist. Please try again.");
            return;
        }
        ConsoleColor.println(ConsoleColor.GREEN, "What information do you want to update?");
        ConsoleColor.println(ConsoleColor.YELLOW, "1. Password");
        ConsoleColor.println(ConsoleColor.YELLOW, "2. ID Number");
        ConsoleColor.println(ConsoleColor.YELLOW, "3. Phone Number");
        ConsoleColor.println(ConsoleColor.YELLOW, "4. Permission");
        ConsoleColor.print(ConsoleColor.GREEN, "Please enter your choice (1 - 4): ");
        int choice = scanner.nextInt();
        scanner.nextLine();

        switch (choice) {
            case 1:
                ConsoleColor.print(ConsoleColor.GREEN, "Enter new password: ");
                String newPassword = scanner.nextLine();
                while (!Check.checkPassword(newPassword)) {
                    ConsoleColor.print(ConsoleColor.RED, "Invalid password. Please enter a new password: ");
                    newPassword = scanner.nextLine();
                }
                user.setPassword(newPassword);
                ConsoleColor.println(ConsoleColor.GREEN, "Password updated successfully!");
                break;
            case 2:
                ConsoleColor.print(ConsoleColor.GREEN, "Enter new ID number: ");
                String newIdNumber = scanner.nextLine();
                while (!Check.checkIdNumber(newIdNumber)) {
                    newIdNumber = scanner.nextLine();
                }
                user.setIdNumber(newIdNumber);
                ConsoleColor.println(ConsoleColor.GREEN, "ID number updated successfully!");
                break;
            case 3:
                ConsoleColor.print(ConsoleColor.GREEN, "Enter new phone number: ");
                String newPhoneNumber = scanner.nextLine();
                while (!Check.checkPhoneNumber(newPhoneNumber)) {
                    newPhoneNumber = scanner.nextLine();
                }
                user.setPhoneNumber(newPhoneNumber);
                ConsoleColor.println(ConsoleColor.GREEN, "Phone number updated successfully!");
                break;
            case 4:
                ConsoleColor.println(ConsoleColor.GREEN, "What level of user do you want to set?");
                ConsoleColor.println(ConsoleColor.YELLOW, "1. Common User");
                ConsoleColor.println(ConsoleColor.YELLOW, "2. Admin User");
                ConsoleColor.println(ConsoleColor.YELLOW, "3. Developer User");
                ConsoleColor.print(ConsoleColor.GREEN, "Please enter your choice (1 or 2 or 3): ");
                int permissionChoice = scanner.nextInt();
                scanner.nextLine();
                User.Permission[] permissions = { User.Permission.COMMONUSER, User.Permission.ADMIN,
                        User.Permission.DEVELOPER };
                if (permissionChoice < 1 || permissionChoice > permissions.length) {
                    ConsoleColor.println(ConsoleColor.RED, "Invalid choice. Please try again.");
                    return;
                }
                User.Permission newPermission = permissions[permissionChoice - 1];
                user.setPermission(newPermission);
                ConsoleColor.println(ConsoleColor.GREEN, "Permission updated successfully!");
                break;
            default:
                ConsoleColor.println(ConsoleColor.RED, "Invalid choice. Please try again.");
        }
    }
}