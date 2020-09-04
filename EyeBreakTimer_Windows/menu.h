#pragma once
#include <windows.h>
#include <map>
#include <iostream>
#include "menuItem.h"
#include "Timer.h"


class Menu {
public:
    std::map<int, MenuItem> menuItems;
    HMENU hMenu = NULL;

    void CreateMenu(HWND hWnd);
    void ShowMenu(HWND hWnd);
    void Command(HWND hWnd, int menuItemId, Timer* timer);
};
