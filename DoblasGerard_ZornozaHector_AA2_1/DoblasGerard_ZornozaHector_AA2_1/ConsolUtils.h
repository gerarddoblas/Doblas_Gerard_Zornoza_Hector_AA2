#pragma once
#include <Windows.h>

struct Position {
    int x;
    int y;
};

inline void CloseConsole() {
    HWND hwnd = GetConsoleWindow();
    if (hwnd != NULL) {
        PostMessage(hwnd, WM_CLOSE, 0, 0);
    }
}