#pragma once
#include <iostream>
#include <string>
#include <windows.h>
#include <conio.h>
#include <vector>
#include "MenuFunction.h"

using namespace std;

class Menu :public MenuFunction
{
private:
    HANDLE hStdOut;
    int active_menu;
    vector<string> menu_items;
public:
    Menu();
    void GoToXY(short x, short y);
    void ConsoleCursorVisible(bool show, short size);
    void SetConsoleTitle(const string& title);
    void PrintMenu();
    void ProcessMenu();
};






