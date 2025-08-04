#include "student.h"
#include "admin.h"
#include "ui.h"
#include <locale.h>
#include <graphics.h>
#include "graphics_utils.h"

int main()
{
    initgraph(WIN_WIDTH, WIN_HEIGHT);
    setlocale(LC_ALL, "");
    FreeConsole();
    LoadStudentFromFile();
    LoadAdminFromFile();
    WelcomeGraph();
    closegraph();
    return 0;
}
