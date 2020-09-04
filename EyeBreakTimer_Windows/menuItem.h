#pragma once
#include <windows.h>
#include "Timer.h"

class MenuItem {
public:
    int id;
    void (* SelectedEvent)(HWND hWnd, Timer* timer);

    MENUITEMINFO CreateMenuItem(UINT id, LPWSTR name);
};
