#include "Roarsomecpp.h"

import UpdateInfo;
import Decision;
import Creature;
import App;

using namespace std;

Roarsome::App* app = nullptr;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
    auto deskHwnd = GetDesktopWindow();
    RECT deskRect;
    GetClientRect(deskHwnd, &deskRect);

    const wchar_t CLASS_NAME[] = L"Roarsome Window Class";

    WNDCLASS wc = { };

    auto bgBrush = CreateSolidBrush(RGB(0, 0, 0));

    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hbrBackground = bgBrush;

    RegisterClass(&wc);

    auto hwnd = CreateWindowEx(
        WS_EX_LAYERED | WS_EX_TOPMOST | WS_EX_TRANSPARENT | WS_EX_NOACTIVATE,
        CLASS_NAME,                     // Window class
        L"Roarsome",    // Window text
        WS_POPUP,            // Window style

        // Size and position
        0, 0, deskRect.right, deskRect.bottom,

        NULL,       // Parent window    
        NULL,       // Menu
        hInstance,  // Instance handle
        NULL        // Additional application data
    );

    //SetLayeredWindowAttributes(hwnd, 0, 255, LWA_ALPHA);
    SetLayeredWindowAttributes(hwnd, RGB(0, 0, 0), 0, LWA_COLORKEY);

    if (hwnd == NULL)
    {
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);

    MSG msg = { };
    while (app->ShouldExit() == false)
    {
        GetMessage(&msg, NULL, 0, 0) > 0;

        if (app != nullptr)
        {
            app->Update();
            app->Draw();
        }
        
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    if (app != nullptr)
    {
        delete app;
        app = nullptr;
    }

    return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
        case WM_QUIT:
        {
            app->Exit();
            break;
        }
        case WM_CREATE:
        {
            if (app == nullptr)
            {
                app = new Roarsome::App(hwnd);
                app->Initialise();
            }
            return 0;
        }
        case WM_DESTROY:
        {
            PostQuitMessage(0);
            return 0;
        }

        case WM_PAINT:
        {
            return 0;
        }
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
