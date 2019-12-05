//
// Created by maxlun on 9/22/19.
//

#pragma once

#include <string>
#include <vector>

class PolyCrypt {
public:
    static std::string code(const std::string& text);
    static std::string code(const std::string& text, int period);

private:
    static std::vector<std::vector<char>> generate(int period);
};


