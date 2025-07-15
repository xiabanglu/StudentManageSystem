package studentManageSystem;

public class Student {
    public enum Gender {
        MALE, FEMALE, OTHER
    }

    private int id;
    private String name;
    private Gender gender;
    private int age;
    private static String schoolName = "NUIST";

    public Student() {
        this.id = 0;
        this.name = "";
        this.gender = null;
        this.age = 0;
    }

    public Student(int id, String name, Gender gender, int age) {
        this.id = id;
        this.name = name;
        this.gender = gender;
        this.age = age;
    }

    public void setId(int id) {
        this.id = id;
    }

    public void setName(String name) {
        this.name = name;
    }

    public void setGender(Gender gender) {
        this.gender = gender;
    }

    public void setAge(int age) {
        this.age = age;
    }

    public void setSchoolName(String schoolName) {
        Student.schoolName = schoolName;
    }

    public int getId() {
        return id;
    }

    public String getName() {
        return name;
    }

    public Gender getGender() {
        return gender;
    }

    public int getAge() {
        return age;
    }

    public static String getSchoolName() {
        return schoolName;
    }
}