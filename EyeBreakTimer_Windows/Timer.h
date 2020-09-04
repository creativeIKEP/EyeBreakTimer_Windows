#pragma once
#include <map>
#include <iostream>
#include <windows.h>
#include <time.h>

class Timer {
public:
    time_t timerStartTime;
    UINT timerId;
    int settingMinute;

    void StartTimer(HWND hWnd, UINT id, int minute);
    void PauseTimer(HWND hWnd);

private:
    int reminingSecond;
    bool isCounting;
};
