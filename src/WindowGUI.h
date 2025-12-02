#ifndef WINDOWGUI_H
#define WINDOWGUI_H

#include <windows.h>

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

class WindowGUI {
public:
    static int Run(HINSTANCE hInstance);
};

#endif
