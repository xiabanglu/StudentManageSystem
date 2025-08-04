package studentManageSystem;

import java.util.*;

public class StudentManageMenu extends Menu {
    public StudentManageMenu(Scanner scanner) {
        super(
                new String[] { "Add Student", "Delete Student", "View Students", "Update Student", "Back" },
                null,
                Menu.Type.STUDENTMANAGE);
        List<Runnable> functions = new ArrayList<>();
        functions.add(() -> addStudent(scanner));
        functions.add(() -> deleteStudent(scanner));
        functions.add(() -> viewStudents(scanner));
        functions.add(() -> updateStudent(scanner));
        functions.add(() -> goBack(scanner));
        this.functions = functions;
    }

    private void addStudent(Scanner scanner) {
        ConsoleColor.println(ConsoleColor.GREEN, "Please enter student information:");
        ConsoleColor.print(ConsoleColor.GREEN, "Enter student ID: ");
        int id = scanner.nextInt();
        scanner.nextLine();
        ConsoleColor.print(ConsoleColor.GREEN, "Enter student name: ");
        String name = scanner.nextLine();
        ConsoleColor.println(ConsoleColor.GREEN, "Select student gender:");
        ConsoleColor.println(ConsoleColor.YELLOW, "1. Male");
        ConsoleColor.println(ConsoleColor.YELLOW, "2. Female");
        ConsoleColor.println(ConsoleColor.YELLOW, "3. Other");
        ConsoleColor.print(ConsoleColor.GREEN, "Please enter your choice (1 - 3): ");
        int genderChoice = scanner.nextInt();
        scanner.nextLine();
        Student.Gender gender;
        switch (genderChoice) {
            case 1:
                gender = Student.Gender.MALE;
                break;
            case 2:
                gender = Student.Gender.FEMALE;
                break;
            case 3:
                gender = Student.Gender.OTHER;
                break;
            default:
                ConsoleColor.println(ConsoleColor.RED, "Invalid choice. Please try again.");
                return;
        }
        ConsoleColor.print(ConsoleColor.GREEN, "Enter student age: ");
        int age = scanner.nextInt();
        scanner.nextLine();
        Student newStudent = new Student(id, name, gender, age);
        SystemTest.studentList.add(newStudent);
        ConsoleColor.println(ConsoleColor.GREEN, "Student added successfully!");
    }

    private void deleteStudent(Scanner scanner) {
        ConsoleColor.println(ConsoleColor.GREEN, "Please enter the ID of the student you want to delete:");
        int id = scanner.nextInt();
        scanner.nextLine();
        for (Student student : SystemTest.studentList) {
            if (student.getId() == id) {
                SystemTest.studentList.remove(student);
                ConsoleColor.println(ConsoleColor.GREEN, "Student deleted successfully!");
                return;
            }
        }
        ConsoleColor.println(ConsoleColor.RED, "Student with this ID does not exist. Please try again.");
    }

    private void viewStudents(Scanner scanner) {
        if (SystemTest.studentList.isEmpty()) {
            ConsoleColor.println(ConsoleColor.GREEN, "No students found.");
            return;
        }
        for (Student student : SystemTest.studentList) {
            ConsoleColor.println(ConsoleColor.GREEN, "ID: " + student.getId());
            ConsoleColor.println(ConsoleColor.GREEN, "Name: " + student.getName());
            ConsoleColor.println(ConsoleColor.GREEN, "Gender: " + student.getGender());
            ConsoleColor.println(ConsoleColor.GREEN, "Age: " + student.getAge());
            ConsoleColor.println(ConsoleColor.GREEN, "-------------------");
        }
    }

    private void updateStudent(Scanner scanner) {
        ConsoleColor.println(ConsoleColor.GREEN, "Please enter the ID of the student you want to update:");
        int id = scanner.nextInt();
        scanner.nextLine();
        for (Student student : SystemTest.studentList) {
            if (student.getId() == id) {
                ConsoleColor.println(ConsoleColor.GREEN, "What information do you want to update?");
                ConsoleColor.println(ConsoleColor.YELLOW, "1. Name");
                ConsoleColor.println(ConsoleColor.YELLOW, "2. Gender");
                ConsoleColor.println(ConsoleColor.YELLOW, "3. Age");
                ConsoleColor.print(ConsoleColor.GREEN, "Please enter your choice (1 - 3): ");
                int choice = scanner.nextInt();
                scanner.nextLine();
                switch (choice) {
                    case 1:
                        ConsoleColor.print(ConsoleColor.GREEN, "Enter new name: ");
                        String newName = scanner.nextLine();
                        student.setName(newName);
                        ConsoleColor.println(ConsoleColor.GREEN, "Name updated successfully!");
                        break;
                    case 2:
                        ConsoleColor.println(ConsoleColor.GREEN, "Select new gender:");
                        ConsoleColor.println(ConsoleColor.YELLOW, "1. Male");
                        ConsoleColor.println(ConsoleColor.YELLOW, "2. Female");
                        ConsoleColor.println(ConsoleColor.YELLOW, "3. Other");
                        ConsoleColor.print(ConsoleColor.GREEN, "Please enter your choice (1 - 3): ");
                        int genderChoice = scanner.nextInt();
                        scanner.nextLine();
                        Student.Gender newGender;
                        switch (genderChoice) {
                            case 1:
                                newGender = Student.Gender.MALE;
                                break;
                            case 2:
                                newGender = Student.Gender.FEMALE;
                                break;
                            case 3:
                                newGender = Student.Gender.OTHER;
                                break;
                            default:
                                ConsoleColor.println(ConsoleColor.RED, "Invalid choice. Please try again.");
                                return;
                        }
                        student.setGender(newGender);
                        ConsoleColor.println(ConsoleColor.GREEN, "Gender updated successfully!");
                        break;
                    case 3:
                        ConsoleColor.print(ConsoleColor.GREEN, "Enter new age: ");
                        int newAge = scanner.nextInt();
                        scanner.nextLine();
                        student.setAge(newAge);
                        ConsoleColor.println(ConsoleColor.GREEN, "Age updated successfully!");
                        break;
                    default:
                        ConsoleColor.println(ConsoleColor.RED, "Invalid choice. Please try again.");
                }
                return;
            }
        }
        ConsoleColor.println(ConsoleColor.RED, "Student with this ID does not exist. Please try again.");
    }
}
