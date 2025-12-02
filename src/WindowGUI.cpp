#include "WindowGUI.h"
#include "sgfplib.h"
#include <iostream>

#define BTN_SCAN 1

HINSTANCE g_hInst;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {

    case WM_COMMAND:
        if (LOWORD(wParam) == BTN_SCAN) {

            MessageBox(hwnd, "Scanning fingerprint...", "Info", MB_OK);

            DWORD rc;
            HSGFPM hFPM = NULL;

            rc = SGFPM_Create(&hFPM);
            if (rc != SGFDX_ERROR_NONE) {
                MessageBox(hwnd, "SGFPM_Create failed", "Error", MB_OK);
                break;
            }

            DWORD ndevs = 0;
            SGDeviceList *devlist = nullptr;
            rc = SGFPM_EnumerateDevice(hFPM, &ndevs, &devlist);
            if (rc != SGFDX_ERROR_NONE || ndevs == 0) {
                MessageBox(hwnd, "No fingerprint device found", "Error", MB_OK);
                SGFPM_Terminate(hFPM);
                break;
            }

            rc = SGFPM_Init(hFPM, SG_DEV_AUTO);
            if (rc != SGFDX_ERROR_NONE) {
                MessageBox(hwnd, "Init failed", "Error", MB_OK);
                SGFPM_Terminate(hFPM);
                break;
            }

            rc = SGFPM_OpenDevice(hFPM, USB_AUTO_DETECT);
            if (rc != SGFDX_ERROR_NONE) {
                MessageBox(hwnd, "Open device failed", "Error", MB_OK);
                SGFPM_Terminate(hFPM);
                break;
            }

            SGDeviceInfoParam devInfo = {0};
            SGFPM_GetDeviceInfo(hFPM, &devInfo);

            BYTE* img = new BYTE[devInfo.ImageWidth * devInfo.ImageHeight];
            rc = SGFPM_GetImageEx(hFPM, img, 10000, NULL, 80);

            if (rc == SGFDX_ERROR_NONE) {
                MessageBox(hwnd, "Fingerprint captured!", "Success", MB_OK);
            } else {
                MessageBox(hwnd, "Capture failed", "Error", MB_OK);
            }

            delete[] img;
            SGFPM_CloseDevice(hFPM);
            SGFPM_Terminate(hFPM);
        }
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

int WindowGUI::Run(HINSTANCE hInstance) {
    g_hInst = hInstance;

    const char CLASS_NAME[] = "FingerprintWindow";

    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(
        0,
        CLASS_NAME,
        "Fingerprint GUI",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        400, 200,
        NULL,
        NULL,
        hInstance,
        NULL
    );

    HWND button = CreateWindow(
        "BUTTON",
        "Scan Fingerprint",
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        100, 60, 200, 40,
        hwnd,
        (HMENU)BTN_SCAN,
        hInstance,
        NULL);

    ShowWindow(hwnd, SW_SHOW);
    UpdateWindow(hwnd);

    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}
