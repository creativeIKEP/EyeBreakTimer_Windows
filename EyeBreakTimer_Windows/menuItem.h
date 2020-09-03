#pragma once
#include <windows.h>


class MenuItem {
public:
    int id;
    void (* SelectedEvent)(HWND hWnd);

    MENUITEMINFO CreateMenuItem(UINT id, LPWSTR name);
};
