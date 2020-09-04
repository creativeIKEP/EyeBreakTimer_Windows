#pragma once
#include <map>
#include <iostream>
#include <windows.h>
#include <time.h>

class Timer {
public:
    time_t timerStartTime;

    Timer(int id);
    void StartTimer(HWND hWnd, int minute);
    void PauseTimer(HWND hWnd);

private:
    int timerId = 0;
    int minute;
    bool isCounting;
};
