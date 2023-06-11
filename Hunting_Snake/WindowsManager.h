#pragma once
#include <Windows.h>
namespace WindowsManager {
    void SetWindowSize(SHORT, SHORT);
    void SetScreenBufferSize(SHORT, SHORT);
    void DisableResizeWindow();
    void DisableCtrButton(bool, bool, bool);
    void ShowScrollbar(BOOL);
    void SetColor(int, int);
    void GoTo(SHORT, SHORT);
    BOOL M_SetConsoleTitle(_In_ LPCTSTR);
    void ShowCur(bool);
    void DisableSelection();
};

