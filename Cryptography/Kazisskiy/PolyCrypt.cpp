//
// Created by maxlun on 9/22/19.
//

#include <random>
#include <algorithm>
#include <limits.h>
#include "PolyCrypt.h"

std::string PolyCrypt::code(const std::string &text) {
    return code(text, 4);
}

std::string PolyCrypt::code(const std::string &text, int period) {
    auto table = generate(period);
    std::string ans;
    ans.reserve(text.size());
    size_t count = 0;
    for (char ch : text) {
        ans.push_back(table[count][ch - CHAR_MIN]);
        ++count;
        count %= period;
    }
    return ans;
}

std::vector<std::vector<char>> PolyCrypt::generate(int period) {
    std::vector<std::vector<char>> ans;
    ans.reserve(period);
    std::vector<char> curr(1 << CHAR_WIDTH);
    for (int c = CHAR_MIN; c <= CHAR_MAX; ++c) {
        curr[c - CHAR_MIN] = (char) c;
    }
    std::random_device rd;
    std::mt19937 g(rd());
    for (int i = 0; i < period; ++i) {
        std::shuffle(curr.begin(), curr.end(), g);
        ans.push_back(curr);
    }
    return ans;
}
