#include <map>
#include <iostream>
#include "menu.h"
#include "menuItem.h"


void Menu::CreateMenu(HWND hWnd) {
    int id = 0;
    
    if (hMenu == NULL) {
        hMenu = CreatePopupMenu();
    }

    WCHAR time_name[] = L"00:00";
    MenuItem timeMenuItem;
    MENUITEMINFO timeMenuItemInfo = timeMenuItem.CreateMenuItem(id, time_name);
    timeMenuItem.SelectedEvent = [](HWND hWnd, Timer* timer) {
        
    };
    menuItems[id] = timeMenuItem;
    InsertMenuItem(hMenu, id, TRUE, &timeMenuItemInfo);
    ModifyMenu(hMenu, id, MF_GRAYED, id, time_name);

    id++;
    WCHAR restart_name[] = L"60minutes";
    MenuItem restartMenuItem;
    MENUITEMINFO restartMenuItemInfo = restartMenuItem.CreateMenuItem(id, restart_name);
    restartMenuItem.SelectedEvent = [](HWND hWnd, Timer* timer) {
        
    };
    menuItems[id] = restartMenuItem;
    InsertMenuItem(hMenu, id, TRUE, &restartMenuItemInfo);

    id++;
    WCHAR pause_name[] = L"Pause";
    MenuItem pauseMenuItem;
    MENUITEMINFO pauseMenuItemInfo = pauseMenuItem.CreateMenuItem(id, pause_name);
    pauseMenuItem.SelectedEvent = [&](HWND hWnd, Timer* timer) {
        timer->PauseTimer(hWnd);
        if (timer->isCounting) {
            ModifyMenu(hMenu, 2, MF_STRING, 2, L"Pause");
            return;
        }
        ModifyMenu(hMenu, 2, MF_STRING, 2, L"Restart");
    };
    menuItems[id] = pauseMenuItem;
    InsertMenuItem(hMenu, id, TRUE, &pauseMenuItemInfo);

    id++;
    WCHAR setting_name[] = L"setting";
    MenuItem settingMenuItem;
    MENUITEMINFO settingMenuItemInfo = settingMenuItem.CreateMenuItem(id, setting_name);
    settingMenuItem.SelectedEvent = [](HWND hWnd, Timer* timer) {
        ShowWindow(hWnd, SW_SHOWNORMAL);
        UpdateWindow(hWnd);
    };
    menuItems[id] = settingMenuItem;
    InsertMenuItem(hMenu, id, TRUE, &settingMenuItemInfo);

    id++;
    WCHAR exit_name[] = L"exit";
    MenuItem exitMenuItem;
    MENUITEMINFO exitMenuItemInfo = exitMenuItem.CreateMenuItem(id, exit_name);
    exitMenuItem.SelectedEvent = [](HWND hWnd, Timer* timer) {
        PostQuitMessage(0);
    };
    menuItems[id] = exitMenuItem;
    InsertMenuItem(hMenu, id, TRUE, &exitMenuItemInfo);
}

void Menu::ShowMenu(HWND hWnd) {
    POINT po;
    GetCursorPos(&po);
    TrackPopupMenu(hMenu, 0, po.x, po.y, 0, hWnd, NULL);
}

void Menu::Command(HWND hWnd, int menuItemId, Timer* timer) {
    if (menuItems.count(menuItemId) == 0) {
        return;
    }
    menuItems[menuItemId].SelectedEvent(hWnd, timer);
}
