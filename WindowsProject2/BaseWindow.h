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
    //настройки приложения (указан nCmdShow по умолчанию)
    static WindowProperties prop;
    
    int windowID;   //id окна (задается вручную при создании окна для будущего сохранения)

    std::string text;   //название окна

    ATOM a;
    UINT style;
    int showCmd;

    //позиция и габариты окна
    Vec2D position, geom;

    WCHAR szTitle[MAX_LOADSTRING], szWindowClass[MAX_LOADSTRING];
    //идентификатор текущего окна и родителя
    HWND hwnd = nullptr, parent = nullptr;

    virtual void inicialize();
public:
    BaseWindow() {}
    BaseWindow(const std::string &_text, int _showCmd, const Vec2D &_position, const Vec2D &_geom, UINT _style, int _windowID, HWND _parent = nullptr):
         text(_text), position(_position), geom(_geom), style(_style), showCmd(_showCmd), windowID(_windowID), parent(_parent) { }

    static void setWindowProperties(const WindowProperties &_properties) { prop = _properties; }

    //отображение текущего окна после окна _parent. изменение родителя
    void setParent(HWND _parent);

    //идентификатор окна
    const HWND &getWindInd() const { return hwnd; }
    //визуализация окна и инициализация (если ее не было)
    virtual bool show();

    //регистрация параметров окна
    ATOM registerClass();

    void update();

    //позиция окна
    const Vec2D &getPosition() const { return position; }
    //габариты окна
    const Vec2D &getGeometry() const { return geom; }

    //изменение id окна
    void setWindowID(int _id) { windowID = _id; }
    //id окна
    int getWindowID() const { return windowID; }

    //название окна
    const std::string &getText() const { return text; }
    //изменение названия окна
    void setWindowText(const std::string &_text);
};

