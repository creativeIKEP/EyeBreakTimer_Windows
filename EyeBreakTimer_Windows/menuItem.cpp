#include "menuItem.h"


MENUITEMINFO MenuItem::CreateMenuItem(UINT id, LPWSTR name) {
    MENUITEMINFO menuiteminfo;
    menuiteminfo.cbSize = sizeof(menuiteminfo);
    menuiteminfo.fMask = MIIM_STRING | MIIM_ID;
    menuiteminfo.wID = id;
    menuiteminfo.dwTypeData = name;
    this->id = id;
    return menuiteminfo;
}