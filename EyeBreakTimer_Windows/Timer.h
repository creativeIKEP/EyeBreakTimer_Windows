#pragma once
#include <windows.h>

class Timer {
public:
    Timer(int id);
    void StartTimer(HWND hWnd, int minute);

private:
    int timerId = 0;
    int minute;
};
