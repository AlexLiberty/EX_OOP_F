#include "Menu.h"

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    Menu menu;
    menu.SetConsoleTitle("Простий файл менеджер");
    menu.ProcessMenu();

    return 0;
}
