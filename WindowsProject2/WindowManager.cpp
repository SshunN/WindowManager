#include "WindowManager.h"

#include "Resource.h"
#include <string>
#include "Config.h"

using namespace std;

MainWindow WindowManager::mw;
std::vector<std::shared_ptr<BaseWindow>> WindowManager::windows;
int WindowManager::maxID = -1;

typedef std::pair<HWND, BaseWindow&> bwPair;

std::string configFile = "config.ini";

void WindowManager::loadWindows()
{
    Config conf;
    std::vector<int> ids = conf.read(configFile);
    
    //�������� ���� � ����������� � ������������ id
    for (int i : ids)
    {
        addWindow("Window " + std::to_string(i), i);
        if (maxID < i) maxID = i;       //��� �������� ���������� ���� ����� ����� ������������ id
    }

    mw = MainWindow(Vec2D(800, 400), Vec2D(300, 300), WS_OVERLAPPEDWINDOW | WS_EX_TOPMOST, IDM_MAINWINDOW, nullptr);
    mw.show();
    mw.setParent(HWND_TOPMOST);     //���� �������� ������ �������
}

void WindowManager::addWindow(const std::string &title, int id)
{
    //���� ������ ���� �� ������, ����������� �������� last
    if(windows.empty()) windows.push_back(std::make_shared<BaseWindow>(BaseWindow(title, SW_MAXIMIZE, Vec2D(50, 50), 
        Vec2D(200, 200), WS_OVERLAPPEDWINDOW | WS_MAXIMIZEBOX, windows.size(), HWND_DESKTOP)));
    else
    {
        BaseWindow &last = *windows.back();
        windows.push_back(std::make_shared<BaseWindow>(BaseWindow(title, SW_MAXIMIZE, last.getPosition() + Vec2D(0, 25),
            Vec2D(200, 200), WS_OVERLAPPEDWINDOW | WS_MAXIMIZEBOX, windows.size(), last.getWindInd())));
    }
    windows.back()->show();
    windows.back()->setWindowID(id);
}

HINSTANCE WindowManager::gethInst() const { return prop.hInst; }

int WindowManager::startWindowsControll()
{
    HACCEL hAccelTable = LoadAccelerators(prop.hInst, MAKEINTRESOURCE(IDC_WINDOWSPROJECT2));
    MSG msg;

    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }
    if (!windows.empty())
    {
        Config c;
        std::vector<int> order;
        for (std::shared_ptr<BaseWindow> &w : windows)
            order.push_back(w->getWindowID());
        c.write(configFile, order);
    }
    return (int)msg.wParam;
}

LRESULT CALLBACK WindowManager::procEvents(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        switch (wmId)
        {
        case IDM_ADDBUT:
        {
            //������� �� ������ ���������� ����
            addWindow("Window " + std::to_string(++maxID), maxID);
            break;
        }
        case IDM_CHANGEBUT:
        {
            //������� �� ������ ��������� ������� �����������
            changeOrder();
            break;
        }
        case IDM_EXIT:
            //����� ����������
            DestroyWindow(hWnd);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
        break;
    }
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        // TODO: �������� ���� ����� ��� ����������, ������������ HDC...
        EndPaint(hWnd, &ps);
        break;
    }
    case WM_DESTROY:
    {
        if (mw.getWindInd() == hWnd) 
            PostQuitMessage(0);     //���� ������� ���� �������� - �����
        else 
            removeWindow(hWnd);     //���� ������� ������� ���� - �������� �� ������� ����
        break;
    }

    default:
        //����� ����������
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

void WindowManager::changeOrder()
{
    //��������� �������
    if (windows.size() < 2) return;

    std::vector<std::shared_ptr<BaseWindow>> vec;
    vec.push_back(windows.back());
    for (int i(0); i < windows.size() - 1; i++) vec.push_back(windows[i]);
    windows = vec;
    for (int i(1); i < windows.size(); i++) windows[i]->setParent(windows[i - 1]->getWindInd());
    windows[0]->setParent(HWND_DESKTOP);
}

void WindowManager::removeWindow(HWND _hwnd)
{
    for (int i(0); i < windows.size(); i++)
    {
        std::shared_ptr<BaseWindow> &w = windows[i];
        if (w->getWindInd() == _hwnd)
        {
            int id = w->getWindowID();
            
            windows.erase(windows.begin() + i);
            if (id == maxID)
            {
                maxID = -1;
                for (std::shared_ptr<BaseWindow> &w : windows)
                    if (maxID < w->getWindowID()) maxID = w->getWindowID();
            }
            break;
        }
    }
}