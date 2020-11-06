#include "Button.h"

using namespace std;

void Button::inicialize()
{
    registerClass();
    std::wstring stemp = std::wstring(text.begin(), text.end());
    LPCWSTR sw = stemp.c_str();
    hwnd = CreateWindowW(L"BUTTON", sw, style, position.x, position.y, geom.x, geom.y, parent, (HMENU)windowID, prop.hInst, nullptr);
}