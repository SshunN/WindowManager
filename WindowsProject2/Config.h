#pragma once

#include <map>
#include <sstream>
#include <stdexcept>
#include <string>
#include <istream>
#include <fstream>
#include <vector>

class Config
{
public:
    Config() {}

    //загрузка предыдущего порядка окон приложения
    std::vector<int> read(std::string _file) const;

    //запись порядка окон
    void write(std::string _file, const std::vector<int> &order) const;
};

