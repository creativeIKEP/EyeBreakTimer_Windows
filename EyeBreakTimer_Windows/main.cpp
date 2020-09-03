#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>
#include "menu.h"
#define WM_TASKTRAY (WM_USER+1)
#define ID_TASKTRAY 0

static TCHAR szWindowClass[] = _T("Eye Break Timer"); // The main window class name.
static TCHAR szTitle[] = _T("Eye Break Timer"); // The string that appears in the application's title bar.
HINSTANCE hInst;
Menu menu;


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
    wcex.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);

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
        500, 500,
        NULL,
        NULL,
        hInstance,
        NULL
    );

    if (!hWnd)
    {
        MessageBox(NULL,
            _T("Call to CreateWindow failed!"),
            _T("Eye Break Timer"),
            NULL);

        return 1;
    }

    NOTIFYICONDATA nif;
    // É^ÉXÉNÉgÉåÉCÇ…ìoò^
    nif.cbSize = sizeof(NOTIFYICONDATA);
    nif.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    nif.hWnd = hWnd;
    nif.uCallbackMessage = WM_TASKTRAY;
    nif.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
    nif.uID = ID_TASKTRAY;
    ::wcscpy_s(nif.szTip, 128, szTitle);

    Shell_NotifyIcon(NIM_ADD, &nif);

    AppicationInit(hWnd);

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

        TextOut(hdc, 5, 5, greeting, _tcslen(greeting));

        EndPaint(hWnd, &ps);
        break;

    case WM_TASKTRAY:
        if (wParam == ID_TASKTRAY)
        {
            switch (lParam)
            {
                case WM_LBUTTONUP:
                    menu.CreateMenu(hWnd);
                    break;
            }
        }
        break;
  
    case WM_CLOSE:
        ShowWindow(hWnd, SW_HIDE);
        break;

    case WM_COMMAND:
        menu.Command(hWnd, LOWORD(wParam));
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
        break;
    }

    return 0;
}

VOID CALLBACK SendNotification(HWND hwnd, UINT uMsg, UINT idEvent, DWORD dwTime) {
    NOTIFYICONDATA nid{ };
    nid.cbSize = sizeof(nid);
    nid.hWnd = hwnd;
    nid.uID = 0;
    nid.uFlags = NIF_INFO;
    nid.dwInfoFlags = NIIF_INFO;

    lstrcpy(nid.szInfoTitle, _T("Break Time!!"));
    lstrcpy(nid.szInfo, _T("Å`ï™Ç™åoâﬂÇµÇ‹ÇµÇΩÅBñ⁄ÇãxåeÇ≥ÇπÇ‹ÇµÇÂÇ§ÅB"));

    Shell_NotifyIcon(NIM_MODIFY, &nid);
}

void AppicationInit(HWND hWnd) {
    int minute = 1;
    int timerId = 1;
    SetTimer(hWnd, timerId, minute * 60 * 1000, SendNotification);
}

