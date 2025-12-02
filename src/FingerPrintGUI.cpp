#include "FingerPrintGUI.h"

ATOM FingerPrintGUI::RegisterWindowClass(HINSTANCE hInstance) {
    WNDCLASSEX wc = {};
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = FingerPrintGUI::WindowProc;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszClassName = _T("FingerPrintWindowClass");

    return RegisterClassEx(&wc);
}

HWND FingerPrintGUI::CreateMainWindow(HINSTANCE hInstance, int nCmdShow) {
    HWND hwnd = CreateWindowEx(
        0,
        _T("FingerPrintWindowClass"),
        _T("Fingerprint GUI"),
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 500, 400,
        nullptr,
        nullptr,
        hInstance,
        nullptr
    );

    if (!hwnd)
        MessageBox(nullptr, _T("CreateWindowEx failed."), _T("Error"), MB_OK | MB_ICONERROR);

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    // Add button
    CreateWindow(
        _T("BUTTON"),
        _T("Scan Fingerprint"),
        WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
        50, 50, 150, 40,
        hwnd,
        (HMENU)1,
        hInstance,
        nullptr
    );

    return hwnd;
}

LRESULT CALLBACK FingerPrintGUI::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {

        case WM_COMMAND:
            if (LOWORD(wParam) == 1) {
                MessageBox(hwnd, _T("Fingerprint scanned!"), _T("Scan"), MB_OK);
            }
            break;

        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
