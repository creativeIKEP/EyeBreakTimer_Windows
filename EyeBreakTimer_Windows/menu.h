#pragma once
#include <windows.h>
#include <map>
#include <iostream>
#include "menuItem.h"


class Menu {
public:
    std::map<int, MenuItem> menuItems;

    void CreateMenu(HWND hWnd);

    void Command(HWND hWnd, int menuItemId);
};
