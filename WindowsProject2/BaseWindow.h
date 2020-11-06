#pragma once

#include "framework.h"
#include "Resource.h"
#include <vector>
#include <map>
#include "boost\shared_ptr.hpp"
#include <codecvt>

#define MAX_LOADSTRING 100

struct WindowProperties
{
    HINSTANCE hInst;
    int nCmdShow;
    WindowProperties() {}
    WindowProperties(const WindowProperties &prop): hInst(prop.hInst), nCmdShow(prop.nCmdShow) {}
    WindowProperties(HINSTANCE _hInst, int _nCmdShow): hInst(_hInst), nCmdShow(_nCmdShow) {}
};
class WindowManager;

struct Vec2D
{
    int x, y;
    Vec2D(): x(0), y(0) {}
    Vec2D(int _x, int _y): x(_x), y(_y) {}

    Vec2D operator + (const Vec2D &vec) const { return Vec2D(x + vec.x, y + vec.y); }
};

class BaseWindow
{
protected:
    //��������� ���������� (������ nCmdShow �� ���������)
    static WindowProperties prop;
    
    int windowID;   //id ���� (�������� ������� ��� �������� ���� ��� �������� ����������)

    std::string text;   //�������� ����

    ATOM a;
    UINT style;
    int showCmd;

    //������� � �������� ����
    Vec2D position, geom;

    WCHAR szTitle[MAX_LOADSTRING], szWindowClass[MAX_LOADSTRING];
    //������������� �������� ���� � ��������
    HWND hwnd = nullptr, parent = nullptr;

    virtual void inicialize();
public:
    BaseWindow() {}
    BaseWindow(const std::string &_text, int _showCmd, const Vec2D &_position, const Vec2D &_geom, UINT _style, int _windowID, HWND _parent = nullptr):
         text(_text), position(_position), geom(_geom), style(_style), showCmd(_showCmd), windowID(_windowID), parent(_parent) { }

    static void setWindowProperties(const WindowProperties &_properties) { prop = _properties; }

    //����������� �������� ���� ����� ���� _parent. ��������� ��������
    void setParent(HWND _parent);

    //������������� ����
    const HWND &getWindInd() const { return hwnd; }
    //������������ ���� � ������������� (���� �� �� ����)
    virtual bool show();

    //����������� ���������� ����
    ATOM registerClass();

    void update();

    //������� ����
    const Vec2D &getPosition() const { return position; }
    //�������� ����
    const Vec2D &getGeometry() const { return geom; }

    //��������� id ����
    void setWindowID(int _id) { windowID = _id; }
    //id ����
    int getWindowID() const { return windowID; }

    //�������� ����
    const std::string &getText() const { return text; }
    //��������� �������� ����
    void setWindowText(const std::string &_text);
};

