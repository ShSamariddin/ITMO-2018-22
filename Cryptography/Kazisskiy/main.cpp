#include <iostream>

#include "Kazisskiy.h"
#include "PolyCrypt.h"

int main() {
    std::ios_base::sync_with_stdio(false);
    freopen("input.txt", "r", stdin);
    std::string input;
    std::string file;
    while (getline(std::cin, input)) {
        file += input;
    }
    auto coded = PolyCrypt::code(file, 26);
    std::cout << coded << std::endl;
    Kazisskiy::decode(file);
}