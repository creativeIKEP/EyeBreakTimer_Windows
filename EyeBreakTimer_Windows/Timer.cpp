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
    timer->StartTimer(hwnd, timer->timerId, timer->settingMinute);
}


void Timer::StartTimer(HWND hWnd, UINT id, int m) {
    timerId = id;
    settingMinute = m;
    reminingSecond = settingMinute * 60;
    isCounting = true;
    timerStartTime = time(NULL);
    TIMER_INSTANCES[timerId] = this;
    KillTimer(hWnd, timerId);
    SetTimer(hWnd, timerId, reminingSecond *1000, SendNotification);
}

void Timer::PauseTimer(HWND hWnd) {
    if (isCounting) {
        time_t currentTime = time(NULL);
        double diffSecond = difftime(currentTime, timerStartTime);
        KillTimer(hWnd, timerId);
        reminingSecond -= diffSecond;
    }
    else {
        timerStartTime = time(NULL);
        KillTimer(hWnd, timerId);
        SetTimer(hWnd, timerId, reminingSecond * 1000, SendNotification);
    }
    isCounting = !isCounting;
}
