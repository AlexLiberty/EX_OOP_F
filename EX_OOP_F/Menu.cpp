#include "Menu.h"

Menu::Menu()
{
    hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    active_menu = 0;
    menu_items.push_back("Показати на екран всі файли");
    menu_items.push_back("Створит новий каталог");
    menu_items.push_back("Видалити каталог");
    menu_items.push_back("Створит новий файл");
    menu_items.push_back("Видалити файл");
    menu_items.push_back("Перейменувати файл");
    menu_items.push_back("Перемісти файл");
    menu_items.push_back("Вивести зміст файлу на екран");
    menu_items.push_back("Вийти");
}

void Menu::GoToXY(short x, short y)
{
    SetConsoleCursorPosition(hStdOut, { x,y });
}

void Menu::ConsoleCursorVisible(bool show, short size)
{
    CONSOLE_CURSOR_INFO structCursorInfo;
    GetConsoleCursorInfo(hStdOut, &structCursorInfo);
    structCursorInfo.bVisible = show;
    structCursorInfo.dwSize = size;
    SetConsoleCursorInfo(hStdOut, &structCursorInfo);
}

void Menu::SetConsoleTitle(const string& title)
{
    SetConsoleTitleA(title.c_str());
}

void Menu::PrintMenu()
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hStdOut, &csbi);
    WORD currentAttributes = csbi.wAttributes;

    GoToXY(40, 10);

    for (int i = 0; i < 9; i++)
    {
        if (i == active_menu)
            SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN | FOREGROUND_RED);
        else
            SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN);

        GoToXY(40, 10 + i);
        cout << menu_items[i] << endl;
    }

    SetConsoleTextAttribute(hStdOut, currentAttributes);
}

void Menu::ProcessMenu()
{
    ConsoleCursorVisible(false, 100);
    char ch;
    do
    {
        PrintMenu();
        ch = _getch();
        if (ch == -32) ch = _getch();
        switch (ch)
        {
        case 27:
            exit(0);
            break;
        case 72:
            if (active_menu == 0)
                active_menu = menu_items.size() - 1;
            else
                --active_menu;
            break;
        case 80:
            if (active_menu == menu_items.size() - 1)
                active_menu = 0;
            else
                ++active_menu;
            break;
        case 13:
            switch (active_menu)
            {
            case 0:
                system("CLS");
                GoToXY(45, 0);
                SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                cout << menu_items[0] << "\n\n";

                show_file(dir_name, full_name, type);

                _getch();
                system("CLS");
                break;
            case 1:
                system("CLS");
                GoToXY(45, 0);
                SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                cout << menu_items[2] << "\n\n";

                make_dir(dir_adres, dir_name, full_adres);

                _getch();
                system("CLS");
                break;
            case 2:
                system("CLS");
                GoToXY(45, 0);
                SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                cout << menu_items[3] << "\n\n";

                delete_dir(dir_adres, dir_name, full_adres);

                _getch();
                system("CLS");
                break;
            case 3:
                system("CLS");
                GoToXY(45, 0);
                SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                cout << menu_items[4] << "\n\n";

                create_file(dir_name, file_name, full_name);

                _getch();
                system("CLS");
                break;
            case 4:
                system("CLS");
                GoToXY(45, 0);
                SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                cout << menu_items[5] << "\n\n";

                delete_file(dir_name, file_name, full_name);

                _getch();
                system("CLS");
                break;
            case 5:
                system("CLS");
                GoToXY(45, 0);
                SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                cout << menu_items[6] << "\n\n";

                rename_file(dir_name, old_name, name, new_name, new_full_name);

                _getch();
                system("CLS");
                break;
            case 6:
                system("CLS");
                GoToXY(45, 0);
                SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                cout << menu_items[7] << "\n\n";

                move_file(adres, name, full_adres, new_adres, new_full_adres);

                _getch();
                system("CLS");
                break;
            case 7:
                system("CLS");
                GoToXY(45, 0);
                SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                cout << menu_items[8] << "\n\n";

                show_file_content(adres, name, full_name);

                _getch();
                system("CLS");
                break;

            case 8:
                cout << "Програма завершує роботу." << endl;
                exit(0);
                break;
            }
            break;
        default:
            break;
        }
    } while (ch != 27);
}


