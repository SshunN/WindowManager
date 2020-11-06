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

    //�������� ����������� ������� ���� ����������
    std::vector<int> read(std::string _file) const;

    //������ ������� ����
    void write(std::string _file, const std::vector<int> &order) const;
};

