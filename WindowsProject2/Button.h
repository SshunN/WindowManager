#pragma once

#include "BaseWindow.h"
#include <string>

typedef void (*func)();

class Button: public BaseWindow
{
    void inicialize() override;
public:
    Button() {}
    Button(const std::string &_text, const Vec2D &_position, const Vec2D &_geom, UINT _style, int _buttonId, HWND _parent = nullptr):
        BaseWindow(_text, SW_NORMAL, _position, _geom, _style, _buttonId, _parent) {}
};

