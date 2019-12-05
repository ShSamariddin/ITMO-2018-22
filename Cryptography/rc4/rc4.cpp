//
// Created by maxlun on 11/13/19.
//

#include <iostream>

using namespace std;

string text, key;

int S[256];


string gen(const string &s) {
    for (int i = 0; i < 256; ++i)
        S[i] = i;
    int j = 0;
    for (int i = 0; i < 256; ++i) {
        j = (j + S[i] + key[i % key.size()]) & 0xFF;
        swap(S[i], S[j]);
    }
    int i = 0;
    j = 0;
    string ret;
    for (char t : s) {
        i = (i + 1) & 0xFF;
        j = (j + S[i]) & 0xFF;
        swap(S[i], S[j]);
        int t1 = (S[i] + S[j]) & 0xFF;
        ret += t ^ S[t1];
    }
    return ret;
}

int main() {
    text = "My name is Jeff";
    key = "My key";
    string cur = gen(text);
    cout << cur << std::endl;
    cout << gen(cur) << std::endl;
    return 0;
}