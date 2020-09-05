#include "Timer.h"
#include <tchar.h>
#define INTERVAL_TIMER_IDFIX 100


static std::map<int, Timer*> TIMER_INSTANCES;
static std::map<int, std::function<void(HWND)>> Interval1SecondFuncs;

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
    timer->StartTimer(hwnd, timer->timerId, timer->settingMinute, NULL);
}

VOID CALLBACK Interval1Second(HWND hwnd, UINT uMsg, UINT idEvent, DWORD dwTime) {

    Timer* timer = TIMER_INSTANCES[idEvent - INTERVAL_TIMER_IDFIX];
    timer->reminingSecond -= 1;
    Interval1SecondFuncs[idEvent - INTERVAL_TIMER_IDFIX](hwnd);
}


void Timer::StartTimer(HWND hWnd, UINT id, int m, std::function<void(HWND)> func) {
    timerId = id;
    settingMinute = m;
    reminingSecond = settingMinute * 60;
    isCounting = true;
    timerStartTime = time(NULL);
    TIMER_INSTANCES[timerId] = this;
    if (func != NULL) {
        Interval1SecondFuncs[timerId] = func;
    }
    KillTimer(hWnd, timerId);
    KillTimer(hWnd, timerId + INTERVAL_TIMER_IDFIX);
    SetTimer(hWnd, timerId, reminingSecond *1000, SendNotification);
    SetTimer(hWnd, timerId + INTERVAL_TIMER_IDFIX, 1000, Interval1Second);
}

void Timer::PauseTimer(HWND hWnd) {
    if (isCounting) {
        KillTimer(hWnd, timerId);
        KillTimer(hWnd, timerId + INTERVAL_TIMER_IDFIX);
    }
    else {
        timerStartTime = time(NULL);
        KillTimer(hWnd, timerId);
        KillTimer(hWnd, timerId + INTERVAL_TIMER_IDFIX);
        SetTimer(hWnd, timerId, reminingSecond * 1000, SendNotification);
        SetTimer(hWnd, timerId + INTERVAL_TIMER_IDFIX, 1000, Interval1Second);
    }
    isCounting = !isCounting;
}
