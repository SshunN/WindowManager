#include "MainWindow.h"

#include "Button.h"

using namespace std;

bool MainWindow::show()
{
    if (!hwnd)
    {
        LoadStringW(prop.hInst, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
        LoadStringW(prop.hInst, IDC_WINDOWSPROJECT2, szWindowClass, MAX_LOADSTRING);

        inicialize();
        
        //кнопки создаются и показываются после инициализации и показа текущего объекта
        typedef std::pair<HWND, BaseWindow&> bwPair;
        addBut = Button("Add window", Vec2D(40, 30), Vec2D(120, 30), WS_VISIBLE | WS_CHILD, IDM_ADDBUT, hwnd);
        changeBut = Button("Change order", Vec2D(40, 90), Vec2D(120, 30), WS_VISIBLE | WS_CHILD, IDM_CHANGEBUT, hwnd);
    }
    ShowWindow(hwnd, prop.nCmdShow);
    addBut.show();
    changeBut.show();
    return true;
}