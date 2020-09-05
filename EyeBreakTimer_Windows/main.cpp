#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>
#include "menu.h"
#include "Timer.h"
#define WM_TASKTRAY (WM_USER+1)
#define ID_TASKTRAY 0
#define BUTTON_ID 999

const static TCHAR szWindowClass[] = _T("Eye Break Timer"); // The main window class name.
const static TCHAR szTitle[] = _T("Eye Break Timer"); // The string that appears in the application's title bar.
const static TCHAR settingFilePath[] = _T(".\\setting.ini");
HINSTANCE hInst;
Menu menu;
Timer timer;
HWND minuteTextBoxId;


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void AppicationInit(HWND hWnd);


int CALLBACK WinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR     lpCmdLine,
    _In_ int       nCmdShow
)
{
    WNDCLASSEX wcex;
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(wcex.hInstance, TEXT("APP_ICON"));
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, TEXT("APP_ICON"));

    if (!RegisterClassEx(&wcex))
    {
        MessageBox(NULL,
            _T("Call to RegisterClassEx failed!"),
            _T("Eye Break Timer"),
            NULL);

        return 1;
    }

    hInst = hInstance;

    HWND hWnd = CreateWindow(
        szWindowClass,
        szTitle,
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        500, 300,
        NULL,
        NULL,
        hInstance,
        NULL
    );

    AppicationInit(hWnd);

    CreateWindow(TEXT("STATIC"), TEXT("SetTime"), WS_CHILD | WS_VISIBLE, 125, 30, 55, 20, hWnd, NULL , hInstance , NULL);
    minuteTextBoxId = CreateWindow(TEXT("EDIT"), TEXT("000"), WS_CHILD | WS_VISIBLE | WS_BORDER, 200, 30, 30, 20, hWnd, NULL, hInstance, NULL);
    CreateWindow(TEXT("STATIC"), TEXT("minutes"), WS_CHILD | WS_VISIBLE, 250, 30, 55, 20, hWnd, NULL, hInstance, NULL);
    CreateWindow(TEXT("BUTTON"), TEXT("Enter"), WS_CHILD | WS_VISIBLE, 325, 25, 70, 30, hWnd, (HMENU)BUTTON_ID, hInstance, NULL);

    if (!hWnd)
    {
        MessageBox(NULL,
            _T("Call to CreateWindow failed!"),
            _T("Eye Break Timer"),
            NULL);

        return 1;
    }

    ShowWindow(hWnd, SW_SHOWNORMAL);
    UpdateWindow(hWnd);

    NOTIFYICONDATA nif;
    // タスクトレイに登録
    nif.cbSize = sizeof(NOTIFYICONDATA);
    nif.hIcon = LoadIcon(wcex.hInstance, TEXT("APP_ICON"));
    nif.hWnd = hWnd;
    nif.uCallbackMessage = WM_TASKTRAY;
    nif.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
    nif.uID = ID_TASKTRAY;
    ::wcscpy_s(nif.szTip, 128, szTitle);

    Shell_NotifyIcon(NIM_ADD, &nif);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT ps;
    HDC hdc;
    TCHAR greeting[] = _T("Hello, Windows desktop!");

    switch (message)
    {
    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);

        wchar_t str[3];
        wsprintfW(str, L"%d", timer.settingMinute);
        SetWindowText(minuteTextBoxId, str);

        EndPaint(hWnd, &ps);
        break;

    case WM_TASKTRAY:
        if (wParam == ID_TASKTRAY)
        {
            switch (lParam)
            {
                case WM_LBUTTONUP:
                    menu.ShowMenu(hWnd);
                    break;
            }
        }
        break;
  
    case WM_CLOSE:
        ShowWindow(hWnd, SW_HIDE);
        break;

    case WM_COMMAND:
        if (LOWORD(wParam) == BUTTON_ID) {
            wchar_t str[10];
            GetWindowText(minuteTextBoxId, str, 10);
            int m = _wtoi(str);
            if (m > 0) {
                WritePrivateProfileString(szWindowClass, L"minute", str, settingFilePath);
                timer.StartTimer(hWnd, 0, m, NULL);
                menu.Command(hWnd, 1, &timer);
            }
        }
        menu.Command(hWnd, LOWORD(wParam), &timer);
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
        break;
    }

    return 0;
}

void TimerMenuItemLabelChange(HWND hWnd) {
    menu.Command(hWnd, 0, &timer);
}

void AppicationInit(HWND hWnd) {
    int minute = GetPrivateProfileInt(szWindowClass, L"minute", 60, settingFilePath);
    if (minute <= 0) {
        minute = 60;
    }
    menu.CreateMenu(hWnd);
    timer.StartTimer(hWnd, 0, minute, TimerMenuItemLabelChange);
    menu.Command(hWnd, 1, &timer);
}

