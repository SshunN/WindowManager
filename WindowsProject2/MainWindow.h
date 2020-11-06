#pragma once

#include "Button.h"

using namespace std;

class MainWindow : public BaseWindow
{
    //кнопки добавление и изменения порядка
    Button addBut, changeBut;
public:
    MainWindow() {}
    MainWindow(const Vec2D &_position, const Vec2D &_geom, int _windowType, int _windowID, HWND _parent = nullptr) :
        BaseWindow("Control", SW_NORMAL, _position, _geom, _windowType, _windowID, _parent) {}

    bool show() override;
};

