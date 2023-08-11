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

const wchar_t STR_PAUSE[5][30] =
{ L" ▄▄▄· ▄▄▄· ▄• ▄▌.▄▄ · ▄▄▄ .",
 L"▐█ ▄█▐█ ▀█ █▪██▌▐█ ▀.▀▄.▀· ",
 L" ██▀·▄█▀▀█ █▌▐█▌▄▀▀▀█▄▐▀▀▪▄",
 L"▐█▪·•▐█▪ ▐▌▐█▄█▌▐█▄▪▐█▐█▄▄▌",
 L".▀    ▀  ▀  ▀▀▀  ▀▀▀▀  ▀▀▀ ",
};

const wchar_t STR_PLAY[5][30] =
{
L" ▄▄▄·▄▄▌   ▄▄▄·  ▄· ▄▌",
L"▐█ ▄███•  ▐█ ▀█ ▐█▪██▌",
L" ██▀·██ ▪ ▄█▀▀█ ▐█▌▐█▪",
L"▐█▪·•▐█▌ ▄▐█▪ ▐▌ ▐█▀·.",
L".▀   .▀▀▀  ▀  ▀   ▀ • ",
};

const wchar_t STR_SAVE[5][30] =
{
L".▄▄ ·  ▄▄▄·  ▌ ▐·▄▄▄ .",
L"▐█ ▀.▐█ ▀█ ▪█·█▌▀▄.▀·",
L"▄▀▀▀█▄▄█▀▀█ ▐█▐█•▐▀▀▪▄",
L"▐█▄▪▐█▐█▪ ▐▌ ███ ▐█▄▄▌",
L" ▀▀▀▀  ▀  ▀.  ▀   ▀▀▀",
};

const wchar_t STR_LOAD[5][30] =
{
L"▄▄▌         ▄▄▄· ·▄▄▄▄",
L"██•   ▄█▀▄ ▐█ ▀█ ██· ██",
L"██ ▪ ▐█▌.▐▌▄█▀▀█ ▐█▪ ▐█▌",
L"▐█▌ ▄▐█▌.▐▌▐█▪ ▐▌██. ██",
L".▀▀▀  ▀█▄▀▪ ▀  ▀ ▀▀▀▀▀•",
};

const wchar_t STR_DEAD[5][30] =
{
L"·▄▄▄▄  ▄▄▄.  ▄▄▄· ·▄▄▄▄",
L"██· ██ ▀▄.▀·▐█ ▀█ ██· ██ ",
L"▐█▪ ▐█▌▐▀▀▪▄▄█▀▀█ ▐█▪ ▐█▌",
L"██. ██ ▐█▄▄▌▐█▪ ▐▌██. ██",
L"▀▀▀▀▀•  ▀▀▀  ▀  ▀ ▀▀▀▀▀•"
};

const wchar_t STR_W[5][30] = {
L" ▄▄▌ ▐ ▄▌",
L" ██· █▌▐█",
L" ██▪▐█▐▐▌",
L" ▐█▌██▐█▌",
L"  ▀▀▀▀ ▀▪",
};

const wchar_t STR_A[5][30] = {
L"  ▄▄▄·",
L" ▐█ ▀█",
L" ▄█▀▀█",
L" ▐█ ▪▐▌",
L"  ▀  ▀"
};

const wchar_t STR_S[5][30] = {
L".▄▄ ·",
L"▐█ ▀.",
L"▄▀▀▀█▄",
L"▐█▄▪▐█",
L" ▀▀▀▀",
};

const wchar_t STR_D[5][30] = {
L"·▄▄▄▄",
L"██▪ ██",
L"▐█· ▐█▌",
L"██. ██",
L"▀▀▀▀▀•"
};

const wchar_t STR_GROUP[5][30] = {
L".▄▄ ·  ▐ ▄  ▄▄▄· ▄ •▄ ▄▄▄ .",
L"▐█ ▀. •█▌▐█▐█ ▀█ █▌▄▌▪▀▄.▀·",
L"▄▀▀▀█▄▐█▐▐▌▄█▀▀█ ▐▀▀▄·▐▀▀▪▄",
L"▐█▄▪▐███▐█▌▐█▪ ▐▌▐█.█▌▐█▄▄▌",
L" ▀▀▀▀ ▀▀ █▪ ▀  ▀ ·▀  ▀ ▀▀▀",
};
