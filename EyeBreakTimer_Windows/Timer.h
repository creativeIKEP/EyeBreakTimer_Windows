#pragma once
#include <map>
#include <iostream>
#include <windows.h>
#include <time.h>
#include <functional>

class Timer {
public:
    time_t timerStartTime;
    UINT timerId;
    int settingMinute;
    int reminingSecond;
    bool isCounting;

    void StartTimer(HWND hWnd, UINT id, int minute, std::function<void(HWND)>);
    void PauseTimer(HWND hWnd);
};
