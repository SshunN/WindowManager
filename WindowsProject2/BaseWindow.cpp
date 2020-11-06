#include "BaseWindow.h"

#include <iostream>
#include "WindowManager.h"
#include <iterator>
WindowProperties BaseWindow::prop;

using namespace std;

void BaseWindow::setParent(HWND _parent)
{
    if (parent == _parent) return;
    parent = _parent;
    SetWindowPos(hwnd, _parent, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
}

void BaseWindow::inicialize()
{
    a = registerClass();
    std::wstring stemp = std::wstring(text.begin(), text.end());
    LPCWSTR sw = stemp.c_str();
    hwnd = CreateWindow(szWindowClass, sw, style, position.x, position.y, geom.x, geom.y, nullptr, nullptr, prop.hInst, nullptr);
    setParent(parent);
}

bool BaseWindow::show()
{
    if (!hwnd)
    {
        LoadStringW(prop.hInst, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
        LoadStringW(prop.hInst, IDC_WINDOWSPROJECT2, szWindowClass, MAX_LOADSTRING);

        inicialize();
    }
    ShowWindow(hwnd, showCmd);
    return true;
};

void BaseWindow::update() { UpdateWindow(hwnd); }

ATOM BaseWindow::registerClass()
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WindowManager::procEvents;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = prop.hInst;
    wcex.hIcon = LoadIcon(prop.hInst, MAKEINTRESOURCE(IDI_WINDOWSPROJECT2));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_WINDOWSPROJECT2);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

void BaseWindow::setWindowText(const std::string &_text)
{
    text = _text;
    SetWindowTextA(hwnd, text.c_str());
}