#include "Timer.h"
#include <tchar.h>


Timer::Timer(int id) {
    timerId = id;
    minute = 60;
}

VOID CALLBACK SendNotification(HWND hwnd, UINT uMsg, UINT idEvent, DWORD dwTime) {
    NOTIFYICONDATA nid{ };
    nid.cbSize = sizeof(nid);
    nid.hWnd = hwnd;
    nid.uID = 0;
    nid.uFlags = NIF_INFO;
    nid.dwInfoFlags = NIIF_INFO;

    lstrcpy(nid.szInfoTitle, _T("Break Time!!"));
    lstrcpy(nid.szInfo, _T("Å`ï™Ç™åoâﬂÇµÇ‹ÇµÇΩÅBñ⁄ÇãxåeÇ≥ÇπÇ‹ÇµÇÂÇ§ÅB"));

    Shell_NotifyIcon(NIM_MODIFY, &nid);
}

void Timer::StartTimer(HWND hWnd, int m) {
	minute = m;
    KillTimer(hWnd, timerId);
	SetTimer(hWnd, timerId, minute * 60 * 1000, SendNotification);
}
