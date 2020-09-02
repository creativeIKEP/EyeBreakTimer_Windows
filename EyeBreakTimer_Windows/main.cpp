#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>
#define WM_TASKTRAY (WM_USER+1)
#define ID_TASKTRAY 0

static TCHAR szWindowClass[] = _T("Eye Break Timer"); // The main window class name.
static TCHAR szTitle[] = _T("Eye Break Timer"); // The string that appears in the application's title bar.
HINSTANCE hInst;


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);


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

    //ShowWindow(hWnd, nCmdShow);
    //UpdateWindow(hWnd);

    NOTIFYICONDATA nif;
    // タスクトレイに登録
    nif.cbSize = sizeof(NOTIFYICONDATA);
    nif.hIcon = LoadIcon(NULL, IDI_APPLICATION);
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

        TextOut(hdc, 5, 5, greeting, _tcslen(greeting));

        EndPaint(hWnd, &ps);
        break;
    case WM_TASKTRAY:
        if (wParam == ID_TASKTRAY)
        {
            switch (lParam)
            {
                case WM_LBUTTONUP:
                    //ShowWindow(hWnd, SW_SHOWNORMAL);
                    //UpdateWindow(hWnd);
                    break;
                case WM_RBUTTONUP:
                    POINT po;
                    GetCursorPos(&po);

                    HMENU hMenu = CreatePopupMenu();
                    MENUITEMINFO menuiteminfo;
                    menuiteminfo.cbSize = sizeof(menuiteminfo);
                    menuiteminfo.fMask = MIIM_STRING | MIIM_ID;
                    menuiteminfo.wID = 1;
                    WCHAR name[] = L"exit";
                    menuiteminfo.dwTypeData = name;
                    InsertMenuItem(hMenu, 0, TRUE, &menuiteminfo);

                    MENUITEMINFO menuiteminfo2;
                    menuiteminfo2.cbSize = sizeof(menuiteminfo2);
                    menuiteminfo2.fMask = MIIM_STRING | MIIM_ID;
                    menuiteminfo2.wID = 0;
                    WCHAR name2[] = L"setting";
                    menuiteminfo2.dwTypeData = name2;
                    InsertMenuItem(hMenu, 0, TRUE, &menuiteminfo2);
                    TrackPopupMenu(hMenu, 0, po.x, po.y, 0, hWnd, NULL);

                    //PostQuitMessage(0);
                    break;
            }
        }
        break;
  
    case WM_CLOSE:
        ShowWindow(hWnd, SW_HIDE);
        break;
    case WM_COMMAND:

        switch (LOWORD(wParam)) {

        case 0: /* Messageメニュー */
            ShowWindow(hWnd, SW_SHOWNORMAL);
            UpdateWindow(hWnd);
            break;

        case 1: /* Exitメニュー */
            PostQuitMessage(0);
            break;

        }
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
        break;
    }

    return 0;
}