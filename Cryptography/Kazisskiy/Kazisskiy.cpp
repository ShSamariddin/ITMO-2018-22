//
// Created by maxlun on 9/22/19.
//

#include <stdexcept>
#include <unordered_map>
#include <vector>
#include <iostream>
#include <algorithm>
#include "Kazisskiy.h"

std::string Kazisskiy::decode(const std::string &text) {
    if (text.length() < 10) {
        throw std::runtime_error("unable to decode");
    }
    std::string trigram1;
//    std::string trigram2;
    trigram1.resize(3);
//    trigram2.resize(3);
    std::unordered_map<std::string, std::vector<size_t >> entrances;

    for (size_t i = 0; i < text.length() - 3; ++i) {
        trigram1[0] = text[i];
        trigram1[1] = text[i + 1];
        trigram1[2] = text[i + 2];
        if (auto itera = entrances.find(trigram1); itera == entrances.end()) {
            entrances.insert(std::make_pair(trigram1, std::vector<size_t>{i}));
        } else {
            itera->second.push_back(i);
        }
    }
    std::vector<size_t> repeat_count;
    for (auto &positions : entrances) {
        for (size_t i = 0; i < positions.second.size(); ++i) {
            for (size_t j = i + 1; j < positions.second.size(); ++j) {
                repeat_count.push_back(positions.second[j] - positions.second[i]);
            }
        }
    }

    std::vector<std::pair<size_t, size_t >> gcds(text.length());
    size_t n = 0;
    for (auto &gcd:gcds) {
        gcd = std::make_pair(0, n++);

    }
    for (size_t i = 0; i < std::min(repeat_count.size(), (size_t) 10000); ++i) {
        for (size_t j = i + 1; j < std::min(repeat_count.size(), (size_t) 10000); ++j) {
            ++gcds[gcd(repeat_count[i], repeat_count[j])].first;
        }
    }
    gcds[0].first = 0;
    std::sort(gcds.begin(), gcds.end(), std::greater<>());
    for (int i = 0; i < 10; ++i) {
        std::cout << gcds[i].second << " ";
    }
    std::cout << std::endl;
    return std::string();

}

size_t Kazisskiy::gcd(const size_t a, const size_t b) {
    if (b == 0) {
        return a;
    }
    return gcd(b, a % b);
}
