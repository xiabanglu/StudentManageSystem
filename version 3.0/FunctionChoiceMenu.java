package studentManageSystem;

import java.util.*;

public class FunctionChoiceMenu extends Menu {
    public FunctionChoiceMenu(Scanner scanner) {
        super(
                new String[] { "Student Management", "Account Management", "Back" }, null,
                Menu.Type.FUNCTIONCHOICE);
        List<Runnable> functions = new ArrayList<>();
        functions.add(() -> studentManagement(scanner));
        functions.add(() -> accountManagement(scanner));
        functions.add(() -> goBack(scanner));
        this.functions = functions;
    }

    private void studentManagement(Scanner scanner) {
        SystemTest.currentMenu = this.childrens.get(0);
    }

    private void accountManagement(Scanner scanner) {
        SystemTest.currentMenu = this.childrens.get(1);
    }
}