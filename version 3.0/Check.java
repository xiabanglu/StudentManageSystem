package studentManageSystem;

public class Check {

    public static boolean checkUsername(String username) {

        if (User.getUserByUsername(SystemTest.userList, username) != null) {
            ConsoleColor.print(ConsoleColor.RED, "Username already exists. Please enter a different username: ");
            return false;
        }

        if (username.length() < 3 || username.length() > 15) {
            ConsoleColor.print(ConsoleColor.RED,
                    "Usename must be 3~15 characters. Please enter a different username: ");
            return false;
        }

        for (char c : username.toCharArray()) {
            if (!Character.isLetterOrDigit(c)) {
                ConsoleColor.print(ConsoleColor.RED,
                        "Username can only contain letters and numbers, Please enter a different username: ");
                return false;
            }
        }

        if (username.matches("\\d+")) {
            ConsoleColor.print(ConsoleColor.RED,
                    "Username cannot be purely numeric. Please enter a different username: ");
            return false;
        }
        return true;
    }

    public static boolean checkPassword(String password) {

        if (password.length() < 6 || password.length() > 20) {
            ConsoleColor.print(ConsoleColor.RED,
                    "Password must be 6~20 characters. Please enter a different password: ");
            return false;
        }

        if (!password.matches("^(?=.*[a-z])(?=.*[A-Z])(?=.*\\d)[a-zA-Z\\d]+$")) {
            ConsoleColor.print(ConsoleColor.RED,
                    "Password must contain at least one uppercase letter, one lowercase letter, and one number. Please enter a different password: ");
            return false;
        }
        return true;
    }

    public static boolean checkIdNumber(String idNumber) {

        if (idNumber.length() != 18) {
            ConsoleColor.print(ConsoleColor.RED,
                    "ID number must be 18 characters. Please enter a different ID number: ");
            return false;
        }

        if (idNumber.charAt(0) == '0') {
            ConsoleColor.print(ConsoleColor.RED, "ID number cannot start with 0. Please enter a different ID number: ");
            return false;
        }

        for (int i = 0; i < idNumber.length() - 1; i++) {
            if (!Character.isDigit(idNumber.charAt(i))) {
                ConsoleColor.print(ConsoleColor.RED,
                        "ID number can only contain digits. Please enter a different ID number: ");
                return false;
            }
        }

        char lastChar = idNumber.charAt(idNumber.length() - 1);
        if (!Character.isDigit(lastChar) && lastChar != 'X' && lastChar != 'x') {
            ConsoleColor.print(ConsoleColor.RED,
                    "ID number can only end with a digit or 'X'. Please enter a different ID number: ");
            return false;
        }
        return true;
    }

    public static boolean checkPhoneNumber(String phoneNumber) {

        if (phoneNumber.length() != 11) {
            ConsoleColor.print(ConsoleColor.RED,
                    "Phone number must be 11 digits. Please enter a different phone number: ");
            return false;
        }
        if (phoneNumber.charAt(0) == '0') {
            ConsoleColor.print(ConsoleColor.RED,
                    "Phone number cannot start with 0. Please enter a different phone number: ");
            return false;
        }
        for (char c : phoneNumber.toCharArray()) {
            if (!Character.isDigit(c)) {
                ConsoleColor.print(ConsoleColor.RED,
                        "Phone number must contain only digits. Please enter a different phone number: ");
                return false;
            }
        }
        return true;
    }
}