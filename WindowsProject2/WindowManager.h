#pragma once

#include "framework.h"
#include <vector>
#include <map>
#include "MainWindow.h"

#define MAX_LOADSTRING 100

class WindowManager
{
    WindowProperties prop;

    //������� ����
    static MainWindow mw;
    //���� ��� ����������
    static std::vector<std::shared_ptr<BaseWindow>> windows;
    static bool loadingFlag;

    //������������ id ����� ������� ����, ������������� ��� ���������� ��� ����������/�������� ����
    static int maxID;
public:
    WindowManager(const WindowProperties &_prop) : prop(_prop) { BaseWindow::setWindowProperties(prop); };

    //������������� ����������
    HINSTANCE gethInst() const;

    //�������� �� ��� ���������� ��������
    void loadWindows();
    //���������� ������ ���� � ��������� title � id ��� �������� ����������
    static void addWindow(const std::string &title, int id);
    //��������� ������� (��������� � ������)
    static void changeOrder();
    //�������� ���� ��� ���������������
    static void removeWindow(HWND _hwnd);
    static void windowActivated(HWND _hwnd);

    //������ ��������� ��������� �� ��
    int startWindowsControll();

    //��������� ��������� �� ��
    static LRESULT CALLBACK procEvents(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};
