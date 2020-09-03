#include <map>
#include <iostream>
#include "menu.h"
#include "menuItem.h"


void Menu::CreateMenu(HWND hWnd) {
    POINT po;
    GetCursorPos(&po);

    HMENU hMenu = CreatePopupMenu();
    WCHAR setting_name[] = L"setting";
    MenuItem settingMenuItem;
    MENUITEMINFO settingMenuItemInfo = settingMenuItem.CreateMenuItem(0, setting_name);
    WCHAR exit_name[] = L"exit";
    MenuItem exitMenuItem;
    MENUITEMINFO exitMenuItemInfo = exitMenuItem.CreateMenuItem(1, exit_name);
    settingMenuItem.SelectedEvent = [](HWND hWnd) {
        ShowWindow(hWnd, SW_SHOWNORMAL);
        UpdateWindow(hWnd);
    };
    exitMenuItem.SelectedEvent = [](HWND hWnd) {
        PostQuitMessage(0);
    };
    menuItems[0] = settingMenuItem;
    menuItems[1] = exitMenuItem;
    InsertMenuItem(hMenu, 0, TRUE, &exitMenuItemInfo);
    InsertMenuItem(hMenu, 0, TRUE, &settingMenuItemInfo);
    TrackPopupMenu(hMenu, 0, po.x, po.y, 0, hWnd, NULL);
}

void Menu::Command(HWND hWnd, int menuItemId) {
    if (menuItems.count(menuItemId) == 0) {
        return;
    }
    menuItems[menuItemId].SelectedEvent(hWnd);
}