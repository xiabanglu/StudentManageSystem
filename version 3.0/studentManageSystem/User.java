package studentManageSystem;

import java.util.*;

public class User {
    public enum Permission {
        COMMONUSER,
        ADMIN,
        DEVELOPER
    }

    private String username;
    private String password;
    private String idNumber;
    private String phoneNumber;
    private Permission permission;
    private boolean isLocked;

    public User() {
        this.username = "";
        this.password = "";
        this.idNumber = "";
        this.phoneNumber = "";
        this.permission = null;
        this.isLocked = false;
    }

    public User(String username, String password) {
        this.username = username;
        this.password = password;
    }

    public User(String username, String password, String idNumber, String phoneNumber, Permission permission,
            boolean isLocked) {
        this.username = username;
        this.password = password;
        this.idNumber = idNumber;
        this.phoneNumber = phoneNumber;
        this.permission = permission;
        this.isLocked = isLocked;
    }

    public void setUsername(String username) {
        this.username = username;
    }

    public void setPassword(String password) {
        this.password = password;
    }

    public void setPermission(Permission permission) {
        this.permission = permission;
    }

    public void setIdNumber(String idNumber) {
        this.idNumber = idNumber;
    }

    public void setPhoneNumber(String phoneNumber) {
        this.phoneNumber = phoneNumber;
    }

    public void setLocked(boolean locked) {
        isLocked = locked;
    }

    public String getUsername() {
        return username;
    }

    public String getPassword() {
        return password;
    }

    public Permission getPermission() {
        return permission;
    }

    public String getIdNumber() {
        return idNumber;
    }

    public String getPhoneNumber() {
        return phoneNumber;
    }

    public boolean isLocked() {
        return isLocked;
    }

    public static User getUserByUsername(ArrayList<User> userList, String username) {
        for (User user : userList) {
            if (user.getUsername().equals(username)) {
                return user;
            }
        }
        return null;
    }

    public static User getUserByPassword(ArrayList<User> userList, String password) {
        for (User user : userList) {
            if (user.getPassword().equals(password)) {
                return user;
            }
        }
        return null;
    }

    public static User getUserByIdNumber(ArrayList<User> userList, String idNumber) {
        for (User user : userList) {
            if (user.getIdNumber().equals(idNumber)) {
                return user;
            }
        }
        return null;
    }

    public static User getUserByPhoneNumber(ArrayList<User> userList, String phoneNumber) {
        for (User user : userList) {
            if (user.getPhoneNumber().equals(phoneNumber)) {
                return user;
            }
        }
        return null;
    }
}