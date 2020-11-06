#include "Config.h"
#include <io.h>
#include <windows.h>

using namespace std;

vector<int> Config::read(string _file) const
{
    std::vector<int> out;
    std::string line;

    std::ifstream in(_file);
    if (in.is_open())
    {
        string line;
        if (!getline(in, line)) return out;

        string word;

        for (char c : line)
        {
            if (c == ',')
            {
                out.push_back(stoi(word));
                word = "";
            }
            else word += c;
        }
        if(!word.empty()) out.push_back(stoi(word));
        in.close();
    }
    return out;
}

void Config::write(string _file, const std::vector<int> &order) const
{
    std::ofstream out(_file);
    if (out.is_open())
    {
        string str;
        for (int i : order) str += std::to_string(i) + ",";
        str.pop_back();
        out << str << std::endl;
        out.close();
    }
}