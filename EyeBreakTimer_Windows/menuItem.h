#pragma once
#include <windows.h>
#include <iostream>
#include <functional>
#include "Timer.h"

class MenuItem {
public:
    int id;

    std::function<void(HWND, Timer*)> SelectedEvent;
    MENUITEMINFO CreateMenuItem(UINT id, LPWSTR name);
};
