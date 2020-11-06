#pragma once

#include "framework.h"
#include <vector>
#include <map>
#include "MainWindow.h"

#define MAX_LOADSTRING 100

class WindowManager
{
    WindowProperties prop;

    //главное окно
    static MainWindow mw;
    //окна для управления
    static std::vector<std::shared_ptr<BaseWindow>> windows;
    static bool loadingFlag;

    //максимальный id среди текущих окон, увеличивается или изменяется при добавлении/удалении окна
    static int maxID;
public:
    WindowManager(const WindowProperties &_prop) : prop(_prop) { BaseWindow::setWindowProperties(prop); };

    //идентификатор приложения
    HINSTANCE gethInst() const;

    //загрузка из ини предыдущих настроек
    void loadWindows();
    //добавление нового окна с названием title и id для будущего сохранения
    static void addWindow(const std::string &title, int id);
    //изменение порядка (последний в начало)
    static void changeOrder();
    //удаление окна под идентификатором
    static void removeWindow(HWND _hwnd);
    static void windowActivated(HWND _hwnd);

    //начало обработки сообщений от ОС
    int startWindowsControll();

    //обработка сообщений от ОС
    static LRESULT CALLBACK procEvents(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};
