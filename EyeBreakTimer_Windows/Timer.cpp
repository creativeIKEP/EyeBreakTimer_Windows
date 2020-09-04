#include "Timer.h"
#include <tchar.h>


static std::map<int, Timer*> TIMER_INSTANCES;

VOID CALLBACK SendNotification(HWND hwnd, UINT uMsg, UINT idEvent, DWORD dwTime) {
    NOTIFYICONDATA nid{ };
    nid.cbSize = sizeof(nid);
    nid.hWnd = hwnd;
    nid.uID = 0;
    nid.uFlags = NIF_INFO;
    nid.dwInfoFlags = NIIF_INFO;

    lstrcpy(nid.szInfoTitle, _T("Break Time!!"));
    lstrcpy(nid.szInfo, _T("`•ª‚ªŒo‰ß‚µ‚Ü‚µ‚½B–Ú‚ð‹xŒe‚³‚¹‚Ü‚µ‚å‚¤B"));

    Shell_NotifyIcon(NIM_MODIFY, &nid);

    Timer* timer = TIMER_INSTANCES[idEvent];
    timer->timerStartTime = time(NULL);
}


Timer::Timer(int id) {
    timerId = id;
    minute = 60;
    isCounting = false;
    timerStartTime = time(NULL);
    TIMER_INSTANCES[id] = this;
}

void Timer::StartTimer(HWND hWnd, int m) {
	minute = m;
    isCounting = true;
    timerStartTime = time(NULL);
    KillTimer(hWnd, timerId);
    SetTimer(hWnd, timerId, 1000, SendNotification);
}

void Timer::PauseTimer(HWND hWnd) {
    if (isCounting) {
        time_t currentTime = time(NULL);
        double diffSecond = difftime(currentTime, timerStartTime);
        int diffMinute = diffSecond / 60;
        KillTimer(hWnd, timerId);
        minute -= diffMinute;
    }
    else {
        StartTimer(hWnd, minute);
    }
    isCounting = !isCounting;
}
