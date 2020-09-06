#include <map>
#include <iostream>
#include <string>
#include "menu.h"
#include "menuItem.h"
#include"langage.h"

void Menu::CreateMenu(HWND hWnd) {
    int id = 0;
    
    if (hMenu == NULL) {
        hMenu = CreatePopupMenu();
    }

    WCHAR time_name[] = L"00:00";
    MenuItem timeMenuItem;
    MENUITEMINFO timeMenuItemInfo = timeMenuItem.CreateMenuItem(id, time_name);
    timeMenuItem.SelectedEvent = [&](HWND hWnd, Timer* timer) {
        int reminingSeconds = timer->reminingSecond;
        int minute = reminingSeconds / 60;
        int seconds = reminingSeconds % 60;
        wchar_t str[10];
        wsprintfW(str, L"%d:%d", minute, seconds);
        ModifyMenu(hMenu, 0, MF_STRING | MF_GRAYED, 0, str);
    };
    menuItems[id] = timeMenuItem;
    InsertMenuItem(hMenu, id, TRUE, &timeMenuItemInfo);
    ModifyMenu(hMenu, id, MF_GRAYED, id, time_name);

    id++;
    WCHAR restart_name[] = L"00 min";
    MenuItem restartMenuItem;
    MENUITEMINFO restartMenuItemInfo = restartMenuItem.CreateMenuItem(id, restart_name);
    restartMenuItem.SelectedEvent = [&](HWND hWnd, Timer* timer) {
        wchar_t str[10];
        wsprintfW(str, L"%d %s", timer->settingMinute, LANG_MINUTES);
        ModifyMenu(hMenu, 1, MF_STRING, 1, str);
        timer->StartTimer(hWnd, timer->timerId, timer->settingMinute, NULL);
    };
    menuItems[id] = restartMenuItem;
    InsertMenuItem(hMenu, id, TRUE, &restartMenuItemInfo);

    id++;
    MenuItem pauseMenuItem;
    MENUITEMINFO pauseMenuItemInfo = pauseMenuItem.CreateMenuItem(id, LANG_PAUSE);
    pauseMenuItem.SelectedEvent = [&](HWND hWnd, Timer* timer) {
        timer->PauseTimer(hWnd);
        if (timer->isCounting) {
            ModifyMenu(hMenu, 2, MF_STRING, 2, LANG_PAUSE);
            return;
        }
        ModifyMenu(hMenu, 2, MF_STRING, 2, LANG_RESTART);
    };
    menuItems[id] = pauseMenuItem;
    InsertMenuItem(hMenu, id, TRUE, &pauseMenuItemInfo);

    id++;
    MenuItem settingMenuItem;
    MENUITEMINFO settingMenuItemInfo = settingMenuItem.CreateMenuItem(id, LANG_SETTING);
    settingMenuItem.SelectedEvent = [](HWND hWnd, Timer* timer) {
        ShowWindow(hWnd, SW_SHOWNORMAL);
        UpdateWindow(hWnd);
    };
    menuItems[id] = settingMenuItem;
    InsertMenuItem(hMenu, id, TRUE, &settingMenuItemInfo);

    id++;
    MenuItem exitMenuItem;
    MENUITEMINFO exitMenuItemInfo = exitMenuItem.CreateMenuItem(id, LANG_EXIT);
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
