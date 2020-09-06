#pragma comment( lib, "wtsapi32.lib" )
#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>
#include<wtsapi32.h>
#include<fstream>
#include <Shlobj_core.h>
#include "menu.h"
#include "Timer.h"
#include "langage.h"
#define WM_TASKTRAY (WM_USER+1)
#define ID_TASKTRAY 0
#define BUTTON_ID1 101
#define BUTTON_ID2 102
#define BUTTON_ID3 103
#define BUTTON_ID4 104

const static TCHAR szWindowClass[] = _T("Eye Break Timer"); // The main window class name.
const static TCHAR szTitle[] = _T("Eye Break Timer"); // The string that appears in the application's title bar.
const static TCHAR settingFileName[] = _T("Setting.ini");
static TCHAR settingFilePath[MAX_PATH];
HINSTANCE hInst;
Menu menu;
Timer timer
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

    CreateWindow(TEXT("STATIC"), LANG_SETTIME, WS_CHILD | WS_VISIBLE, 125, 30, 70, 20, hWnd, NULL , hInstance , NULL);
    minuteTextBoxId = CreateWindow(TEXT("EDIT"), TEXT("000"), WS_CHILD | WS_VISIBLE | WS_BORDER,  205, 29, 30, 22, hWnd, NULL, hInstance, NULL);
    CreateWindow(TEXT("STATIC"), LANG_MINUTES, WS_CHILD | WS_VISIBLE, 250, 30, 55, 20, hWnd, NULL, hInstance, NULL);
    CreateWindow(TEXT("BUTTON"), TEXT("Enter"), WS_CHILD | WS_VISIBLE, 325, 25, 85, 30, hWnd, (HMENU)BUTTON_ID1, hInstance, NULL);
    pauseCheckBoxId = CreateWindow(TEXT("BUTTON"), LANG_LOCKEDPAUSE, WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX, 125, 80, 300, 30, hWnd, (HMENU)BUTTON_ID2, hInstance, NULL);
    restartCheckBoxId = CreateWindow(TEXT("BUTTON"), LANG_UNLOCKED_RESTART, WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX, 60, 150, 310, 30, hWnd, (HMENU)BUTTON_ID3, hInstance, NULL);
    resetCheckBoxId = CreateWindow(TEXT("BUTTON"), LANG_UNLOCKED_RESET, WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX, 60, 190, 390, 30, hWnd, (HMENU)BUTTON_ID4, hInstance, NULL);

    if (!hWnd)
    {
        MessageBox(NULL,
            _T("Call to CreateWindow failed!"),
            _T("Eye Break Timer"),
            NULL);

        return 1;
    }

    NOTIFYICONDATA nif;
    // �^�X�N�g���C�ɓo�^
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
    TCHAR iniPath[MAX_PATH];
    SHGetFolderPath(NULL, CSIDL_APPDATA, NULL, NULL, iniPath);
    //C:\Users\username\AppData\Roaming\Eye Break Timer
    wsprintf(iniPath, TEXT("%s\\%s"), iniPath, szWindowClass);
    CreateDirectory(iniPath, NULL);
    //C:\Users\username\AppData\Roaming\Eye Break Timer\Setting.ini
    wsprintf(settingFilePath, TEXT("%s\\%s"), iniPath, settingFileName);

    std::ifstream ifs(settingFilePath);
    if (ifs.fail()) {
        //Set default params if does not exist Setting.ini file
        WritePrivateProfileString(szWindowClass, L"minute", L"60", settingFilePath);
        WritePrivateProfileString(szWindowClass, L"lockedPause", L"FALSE", settingFilePath);
        WritePrivateProfileString(szWindowClass, L"unlockedRestart", L"FALSE", settingFilePath);
        WritePrivateProfileString(szWindowClass, L"unlockedReset", L"FALSE", settingFilePath);
    }

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
