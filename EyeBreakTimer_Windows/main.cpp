#pragma comment( lib, "wtsapi32.lib" )
#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>
#include<wtsapi32.h>
#include "menu.h"
#include "Timer.h"
#include "resource.h"
#define WM_TASKTRAY (WM_USER+1)
#define ID_TASKTRAY 0
#define BUTTON_ID1 101
#define BUTTON_ID2 102
#define BUTTON_ID3 103
#define BUTTON_ID4 104

const static TCHAR szWindowClass[] = _T("Eye Break Timer"); // The main window class name.
const static TCHAR szTitle[] = _T("Eye Break Timer"); // The string that appears in the application's title bar.
const static TCHAR settingFilePath[] = _T(".\\setting.ini");
HINSTANCE hInst;
Menu menu;
Timer timer;
HWND minuteTextBoxId;
HWND pauseCheckBoxId;
HWND restartCheckBoxId;
HWND resetCheckBoxId;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void AppicationInit(HWND hWnd);
BOOL RegisterMyProgramForStartup(PCWSTR pszAppName, PCWSTR pathToExe, PCWSTR args);


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
    wcex.hbrBackground = (HBRUSH)COLOR_BTNSHADOW;
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
        WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX,
        CW_USEDEFAULT, CW_USEDEFAULT,
        500, 300,
        NULL,
        NULL,
        hInstance,
        NULL
    );

    WTSRegisterSessionNotification(hWnd, NOTIFY_FOR_THIS_SESSION);
    AppicationInit(hWnd);

    CreateWindow(TEXT("STATIC"), TEXT("SetTime"), WS_CHILD | WS_VISIBLE, 125, 30, 55, 20, hWnd, NULL , hInstance , NULL);
    minuteTextBoxId = CreateWindow(TEXT("EDIT"), TEXT("000"), WS_CHILD | WS_VISIBLE, 200, 30, 30, 20, hWnd, NULL, hInstance, NULL);
    CreateWindow(TEXT("STATIC"), TEXT("minutes"), WS_CHILD | WS_VISIBLE, 250, 30, 55, 20, hWnd, NULL, hInstance, NULL);
    CreateWindow(TEXT("BUTTON"), TEXT("Enter"), WS_CHILD | WS_VISIBLE, 325, 25, 70, 30, hWnd, (HMENU)BUTTON_ID1, hInstance, NULL);
    pauseCheckBoxId = CreateWindow(TEXT("BUTTON"), TEXT("Stop timer when PC was locked"), WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX, 125, 80, 250, 30, hWnd, (HMENU)BUTTON_ID2, hInstance, NULL);
    restartCheckBoxId = CreateWindow(TEXT("BUTTON"), TEXT("Restart timer when PC unlocked"), WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX, 60, 150, 250, 30, hWnd, (HMENU)BUTTON_ID3, hInstance, NULL);
    resetCheckBoxId = CreateWindow(TEXT("BUTTON"), TEXT("Reset time and start timer when PC was unlocked"), WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX, 60, 190, 370, 30, hWnd, (HMENU)BUTTON_ID4, hInstance, NULL);

    if (!hWnd)
    {
        MessageBox(NULL,
            _T("Call to CreateWindow failed!"),
            _T("Eye Break Timer"),
            NULL);

        return 1;
    }

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

        wchar_t str[10];
        wsprintfW(str, L"%d", timer.settingMinute);
        SetWindowText(minuteTextBoxId, str);


        GetPrivateProfileString(szWindowClass, L"lockedPause", L"FALSE", str, 10, settingFilePath);
        if (wcscmp(str, L"TRUE") == 0) {
            SendMessage(pauseCheckBoxId, BM_SETCHECK, BST_CHECKED, NULL);
        }
        else {
            SendMessage(pauseCheckBoxId, BM_SETCHECK, BST_UNCHECKED, NULL);
        }
        
        GetPrivateProfileString(szWindowClass, L"unlockedRestart", L"FALSE", str, 10, settingFilePath);
        if (wcscmp(str, L"TRUE") == 0) {
            SendMessage(restartCheckBoxId, BM_SETCHECK, BST_CHECKED, NULL);
        }
        else {
            SendMessage(restartCheckBoxId, BM_SETCHECK, BST_UNCHECKED, NULL);
        }

        GetPrivateProfileString(szWindowClass, L"unlockedReset", L"FALSE", str, 10, settingFilePath);
        if (wcscmp(str, L"TRUE") == 0) {
            SendMessage(resetCheckBoxId, BM_SETCHECK, BST_CHECKED, NULL);
        }
        else {
            SendMessage(resetCheckBoxId, BM_SETCHECK, BST_UNCHECKED, NULL);
        }

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
        if (LOWORD(wParam) == BUTTON_ID1) {
            wchar_t str[10];
            GetWindowText(minuteTextBoxId, str, 10);
            int m = _wtoi(str);
            if (m > 0) {
                WritePrivateProfileString(szWindowClass, L"minute", str, settingFilePath);
                timer.StartTimer(hWnd, 0, m, NULL);
                menu.Command(hWnd, 1, &timer);
            }
        }
        else if (LOWORD(wParam) == BUTTON_ID2) {
            if (BST_CHECKED == SendMessage(pauseCheckBoxId, BM_GETCHECK, NULL, NULL)) {
                WritePrivateProfileString(szWindowClass, L"lockedPause", L"TRUE", settingFilePath);
                break;
            }
            WritePrivateProfileString(szWindowClass, L"lockedPause", L"FALSE", settingFilePath);
        }
        else if (LOWORD(wParam) == BUTTON_ID3) {
            if (BST_CHECKED == SendMessage(restartCheckBoxId, BM_GETCHECK, NULL, NULL)) {
                SendMessage(resetCheckBoxId, BM_SETCHECK, BST_UNCHECKED, NULL);
                WritePrivateProfileString(szWindowClass, L"unlockedRestart", L"TRUE", settingFilePath);
                WritePrivateProfileString(szWindowClass, L"unlockedReset", L"FALSE", settingFilePath);
                break;
            }
            WritePrivateProfileString(szWindowClass, L"unlockedRestart", L"FALSE", settingFilePath);
        }
        else if (LOWORD(wParam) == BUTTON_ID4) {
            if (BST_CHECKED == SendMessage(resetCheckBoxId, BM_GETCHECK, NULL, NULL)) {
                SendMessage(restartCheckBoxId, BM_SETCHECK, BST_UNCHECKED, NULL);
                WritePrivateProfileString(szWindowClass, L"unlockedReset", L"TRUE", settingFilePath);
                WritePrivateProfileString(szWindowClass, L"unlockedRestart", L"FALSE", settingFilePath);
                break;
            }
            WritePrivateProfileString(szWindowClass, L"unlockedReset", L"FALSE", settingFilePath);
        }
        else {
            menu.Command(hWnd, LOWORD(wParam), &timer);
        }
        break;
    case WM_WTSSESSION_CHANGE:
        switch (wParam) {
            wchar_t str[10];
        case WTS_SESSION_LOCK:
            GetPrivateProfileString(szWindowClass, L"lockedPause", L"FALSE", str, 10, settingFilePath);
            if (wcscmp(str, L"TRUE") == 0 && timer.isCounting) {
                menu.Command(hWnd, 2, &timer);
            }
            break;
        case WTS_SESSION_UNLOCK:
            GetPrivateProfileString(szWindowClass, L"unlockedRestart", L"FALSE", str, 10, settingFilePath);
            if (wcscmp(str, L"TRUE") == 0 && !timer.isCounting) {
                menu.Command(hWnd, 2, &timer);
            }

            GetPrivateProfileString(szWindowClass, L"unlockedReset", L"FALSE", str, 10, settingFilePath);
            if (wcscmp(str, L"TRUE") == 0) {
                menu.Command(hWnd, 1, &timer);
            }
            break;
        }
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

    //resister startup application
    wchar_t szPathToExe[MAX_PATH];
    GetModuleFileNameW(NULL, szPathToExe, MAX_PATH);
    RegisterMyProgramForStartup(szWindowClass, szPathToExe, NULL);
}

BOOL RegisterMyProgramForStartup(PCWSTR pszAppName, PCWSTR pathToExe, PCWSTR args)
{
    HKEY hKey = NULL;
    LONG lResult = 0;
    BOOL fSuccess = TRUE;
    DWORD dwSize;

    const size_t count = MAX_PATH * 2;
    wchar_t szValue[count] = {};


    wcscpy_s(szValue, count, L"\"");
    wcscat_s(szValue, count, pathToExe);
    wcscat_s(szValue, count, L"\" ");

    if (args != NULL)
    {
        // caller should make sure "args" is quoted if any single argument has a space
        // e.g. (L"-name \"Mark Voidale\"");
        wcscat_s(szValue, count, args);
    }

    lResult = RegCreateKeyExW(HKEY_CURRENT_USER, L"Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, NULL, 0, (KEY_WRITE | KEY_READ), NULL, &hKey, NULL);

    fSuccess = (lResult == 0);

    if (fSuccess)
    {
        dwSize = (wcslen(szValue) + 1) * 2;
        lResult = RegSetValueExW(hKey, pszAppName, 0, REG_SZ, (BYTE*)szValue, dwSize);
        fSuccess = (lResult == 0);
    }

    if (hKey != NULL)
    {
        RegCloseKey(hKey);
        hKey = NULL;
    }

    return fSuccess;
}