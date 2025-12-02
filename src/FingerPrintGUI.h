#pragma once
#include <windows.h>
#include <tchar.h>  // For _T macro

class FingerPrintGUI {
public:
    // Registers the window class
    static ATOM RegisterWindowClass(HINSTANCE hInstance);

    // Creates and shows the main window
    static HWND CreateMainWindow(HINSTANCE hInstance, int nCmdShow);

    // Window procedure callback
    static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
};
