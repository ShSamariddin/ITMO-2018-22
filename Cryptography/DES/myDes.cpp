# include<bits/stdc++.h>

using namespace std;


unordered_map<string, char> msc;
unordered_map<char, string> mcs;
vector<string> key_list;
vector<string> key_list_h;
const int shift_table[16] =
        {1, 1, 2, 2,
         2, 2, 2, 2,
         1, 2, 2, 2,
         2, 2, 2, 1
        };//всего 16 раундов и на каждом из раундов мы сдвигаем либо на 1 либо на 2в лево
const int key_comp[48] =
        {14, 17, 11, 24, 1, 5,
         3, 28, 15, 6, 21, 10,
         23, 19, 12, 4, 26, 8,
         16, 7, 27, 20, 13, 2,
         41, 52, 31, 37, 47, 55,
         30, 40, 51, 45, 33, 48,
         44, 49, 39, 56, 34, 53,
         46, 42, 50, 36, 29, 32
        };//после сдвига мы сжимаем наш key до
const int com_key[56] =
        {57, 49, 41, 33, 25, 17, 9,
         1, 58, 50, 42, 34, 26, 18,
         10, 2, 59, 51, 43, 35, 27,
         19, 11, 3, 60, 52, 44, 36,
         63, 55, 47, 39, 31, 23, 15,
         7, 62, 54, 46, 38, 30, 22,
         14, 6, 61, 53, 45, 37, 29,
         21, 13, 5, 28, 20, 12, 4
        };//чтобы убрать 8 бит  64->56

const int initial_perm[64] =
        {58, 50, 42, 34, 26, 18, 10, 2,
         60, 52, 44, 36, 28, 20, 12, 4,
         62, 54, 46, 38, 30, 22, 14, 6,
         64, 56, 48, 40, 32, 24, 16, 8,
         57, 49, 41, 33, 25, 17, 9, 1,
         59, 51, 43, 35, 27, 19, 11, 3,
         61, 53, 45, 37, 29, 21, 13, 5,
         63, 55, 47, 39, 31, 23, 15, 7
        };//чтобы просто переставит  pr

const int ex_d[48] =
        {32, 1, 2, 3, 4, 5, 4, 5,
         6, 7, 8, 9, 8, 9, 10, 11,
         12, 13, 12, 13, 14, 15, 16, 17,
         16, 17, 18, 19, 20, 21, 20, 21,
         22, 23, 24, 25, 24, 25, 26, 27,
         28, 29, 28, 29, 30, 31, 32, 1
        };//чтобы увеличит последовательность pr 32->48
const int s[8][4][16] =
        {
                {
                        14, 4,  13, 1,  2,  15, 11, 8,  3,  10, 6,  12, 5,  9,  0,  7,
                        0,  15, 7,  4,  14, 2,  13, 1,  10, 6, 12, 11, 9,  5,  3,  8,
                        4,  1,  14, 8,  13, 6,  2,  11, 15, 12, 9,  7,  3,  10, 5,  0,
                        15, 12, 8,  2,  4,  9,  1,  7,  5,  11, 3,  14, 10, 0, 6,  13
                },
                {
                        15, 1,  8,  14, 6,  11, 3,  4,  9,  7,  2,  13, 12, 0,  5,  10,
                        3,  13, 4,  7,  15, 2,  8,  14, 12, 0, 1,  10, 6,  9,  11, 5,
                        0,  14, 7,  11, 10, 4,  13, 1,  5,  8,  12, 6,  9,  3,  2,  15,
                        13, 8,  10, 1,  3,  15, 4,  2,  11, 6,  7,  12, 0,  5, 14, 9
                },


                {
                        10, 0,  9,  14, 6,  3,  15, 5,  1,  13, 12, 7,  11, 4,  2,  8,
                        13, 7,  0,  9,  3,  4,  6,  10, 2,  8, 5,  14, 12, 11, 15, 1,
                        13, 6,  4,  9,  8,  15, 3,  0,  11, 1,  2,  12, 5,  10, 14, 7,
                        1,  10, 13, 0,  6,  9,  8,  7,  4,  15, 14, 3,  11, 5, 2,  12
                },
                {
                        7,  13, 14, 3,  0,  6,  9,  10, 1,  2,  8,  5,  11, 12, 4,  15,
                        13, 8,  11, 5,  6,  15, 0,  3,  4,  7, 2,  12, 1,  10, 14, 9,
                        10, 6,  9,  0,  12, 11, 7,  13, 15, 1,  3,  14, 5,  2,  8,  4,
                        3,  15, 0,  6,  10, 1,  13, 8,  9,  4,  5,  11, 12, 7, 2,  14
                },
                {
                        2,  12, 4,  1,  7,  10, 11, 6,  8,  5,  3,  15, 13, 0,  14, 9,
                        14, 11, 2,  12, 4,  7,  13, 1,  5,  0, 15, 10, 3,  9,  8,  6,
                        4,  2,  1,  11, 10, 13, 7,  8,  15, 9,  12, 5,  6,  3,  0,  14,
                        11, 8,  12, 7,  1,  14, 2,  13, 6,  15, 0,  9,  10, 4, 5,  3
                },
                {
                        12, 1,  10, 15, 9,  2,  6,  8,  0,  13, 3,  4,  14, 7,  5,  11,
                        10, 15, 4,  2,  7,  12, 9,  5,  6,  1, 13, 14, 0,  11, 3,  8,
                        9,  14, 15, 5,  2,  8,  12, 3,  7,  0,  4,  10, 1,  13, 11, 6,
                        4,  3,  2,  12, 9,  5,  15, 10, 11, 14, 1,  7,  6,  0, 8,  13
                },
                {
                        4,  11, 2,  14, 15, 0,  8,  13, 3,  12, 9,  7,  5,  10, 6,  1,
                        13, 0,  11, 7,  4,  9,  1,  10, 14, 3, 5,  12, 2,  15, 8,  6,
                        1,  4,  11, 13, 12, 3,  7,  14, 10, 15, 6,  8,  0,  5,  9,  2,
                        6,  11, 13, 8,  1,  4,  10, 7,  9,  5,  0,  15, 14, 2, 3,  12
                },
                {
                        13, 2,  8,  4,  6,  15, 11, 1,  10, 9,  3,  14, 5,  0,  12, 7,
                        1,  15, 13, 8,  10, 3,  7,  4,  12, 5, 6,  11, 0,  14, 9,  2,
                        7,  11, 4,  1,  9,  12, 14, 2,  0,  6,  10, 13, 15, 3,  5,  8,
                        2,  1,  14, 7,  4,  10, 8,  13, 15, 12, 9,  0,  3,  5, 6,  11
                }};//s-box
const int per[32] =
        {16, 7, 20, 21,
         29, 12, 28, 17,
         1, 15, 23, 26,
         5, 18, 31, 10,
         2, 8, 24, 14,
         32, 27, 3, 9,
         19, 13, 30, 6,
         22, 11, 4, 25
        };
const int final_perm[64] =
        {40, 8, 48, 16, 56, 24, 64, 32,
         39, 7, 47, 15, 55, 23, 63, 31,
         38, 6, 46, 14, 54, 22, 62, 30,
         37, 5, 45, 13, 53, 21, 61, 29,
         36, 4, 44, 12, 52, 20, 60, 28,
         35, 3, 43, 11, 51, 19, 59, 27,
         34, 2, 42, 10, 50, 18, 58, 26,
         33, 1, 41, 9, 49, 17, 57, 25
        };

void fill_msc() {
    msc["0000"] = '0';
    msc["0001"] = '1';
    msc["0010"] = '2';
    msc["0011"] = '3';
    msc["0100"] = '4';
    msc["0101"] = '5';
    msc["0110"] = '6';
    msc["0111"] = '7';
    msc["1000"] = '8';
    msc["1001"] = '9';
    msc["1010"] = 'A';
    msc["1011"] = 'B';
    msc["1100"] = 'C';
    msc["1101"] = 'D';
    msc["1110"] = 'E';
    msc["1111"] = 'F';
}

void fill_mcs() {
    mcs['0'] = "0000";
    mcs['1'] = "0001";
    mcs['2'] = "0010";
    mcs['3'] = "0011";
    mcs['4'] = "0100";
    mcs['5'] = "0101";
    mcs['6'] = "0110";
    mcs['7'] = "0111";
    mcs['8'] = "1000";
    mcs['9'] = "1001";
    mcs['A'] = "1010";
    mcs['B'] = "1011";
    mcs['C'] = "1100";
    mcs['D'] = "1101";
    mcs['E'] = "1110";
    mcs['F'] = "1111";
}

string get_text() {
    return "123456ABCD132536";
}

string get_key() {
    return "AABB09182736CCDD";
}

string compare(const string &cur, const int *ma, int si) {
    string ans = "";
    for (int i = 0; i < si; i++) {
        ans = ans + cur[ma[i] - 1];
    }
    return ans;
}

string convert_to_bin(const string &str) {//конвертировать в бинарную строку
    string ans = "";
    for (char x: str) {
        ans = ans + mcs[x];
    }
    return ans;
}

string conver_to_hex(const string &str) {
    string ans = "";
    for (int i = 0; i < str.size(); i += 4) {
        string new_str = "";
        new_str = new_str + str[i] + str[i + 1] + str[i + 2] + str[i + 3];
        ans = ans + msc[new_str];
    }
    return ans;
}

string axorb(const string &a, const string &b) {
    string ans;
    for (size_t i = 0; i < a.size(); i++) {
        int x = a[i] - '0';
        int y = b[i] - '0';
        x = (x + y) % 2;
        ans += char(x + '0');
    }
    return ans;
}

string shift_key(const string &key, int n) {
    string ans;
    for (size_t i = n; i < key.size(); i++) {
        ans += key[i];
    }
    for (int i = 0; i < n; i++) {
        ans += key[i];
    }
    return ans;
}

void round_key(string left_key, string right_key) {
    for (int i = 0;
         i < 16; i++) {//сдвигаем на shift_table[i] влево  обе части и соединяем их а потом  уменьшаем размер 56-48
        left_key = shift_key(left_key, shift_table[i]);
        right_key = shift_key(right_key, shift_table[i]);
        string new_key = left_key + right_key;
        new_key = compare(new_key, key_comp, 48);
        key_list.push_back(new_key);
        key_list_h.push_back(conver_to_hex(new_key));
    }
}

string encrypt(string text) {
    text = convert_to_bin(text);
    text = compare(text, initial_perm, 64);
    string left = text.substr(0, 32);
    string right = text.substr(32, 64);
    for (int j = 0; j < 16; j++) {
        //cout <<"left, right = "<< left<<' '<<right<<'\n';
        string new_right = compare(right, ex_d, 48);//увеличим размер правой части до 48
        string xo = axorb(key_list[j], new_right);//xor
        string ans = "";
        for (int i = 0; i < 8; i++) {
            int co = i * 6;
            int r = 2 * (xo[co] - '0') + (xo[co + 5] - '0');
            int c = 8 * (xo[co + 1] - '0') + 4 * (xo[co + 2] - '0') + 2 * (xo[co + 3] - '0') + (xo[co + 4] - '0');
            //r,c - номер строки и столбца  соответственно, в котором стоит наш элемент в s-box
            int val = s[i][r][c], t = 8;
            while (t != 0) {//двоичное представление val
                ans = ans + char((val / t) + '0');
                val = val % t;
                t /= 2;
            }
        }
        ans = compare(ans, per, 32);//просто переставляем биты
        left = axorb(ans, left);
        if (j != 15) {
            swap(left, right);
        }
    }
    text = left + right;
    string en_text = conver_to_hex(compare(text, final_perm, 64));
    return en_text;

}

void prepare(const string &key) {
    fill_msc();
    fill_mcs();
    string key1 = convert_to_bin(key);
    key1 = compare(key1, com_key, 56);
    round_key(key1.substr(0, 28), key1.substr(28, 56));
}


std::pair<string, int> code(const string &text, const string &key) {
    prepare(key);

    string ans;
    for (char c : text) {
        ans += std::bitset<8>(int(c)).to_string();
    }
//    ans.reserve();
    int os = (64 - ans.size() % 64) % 64;
    for (int i = 0; i < os; i++) {
        ans = ans + "0";
    }
    string sol;

    for (int i = 0; i < ans.size(); i += 64) {
        string str = "";
        for (int j = i; j < i + 64; j++) {
            str += ans[j];
        }
        str = conver_to_hex(str);
        sol += encrypt(str);
    }
    return std::make_pair(sol, os);
}

void reverse_keys() {
    reverse(key_list.begin(), key_list.end());
    reverse(key_list_h.begin(), key_list_h.end());
}

string decode(const std::pair<string, int> &coded, const string &key) {
    reverse_keys();

    string result;
    for (int i = 0; i < coded.first.size(); i += 16) {
        string str;
        for (int j = i; j < i + 16; j++) {
            str += coded.first[j];
        }
        result += encrypt(str);
    }
    string binary_res = convert_to_bin(result);
    for (int i = 0; i < coded.second; ++i) {
        binary_res.pop_back();
    }

    string ans;
    for (size_t i = 0; i < binary_res.size(); i += 8) {
        int x = 0;
        for (int j = 0; j < 8; ++j) {
            x <<= 1;
            x += (binary_res[i + j] - '0');
        }
        ans += char(x);
    }

    return ans;

}

int main() {
    string s1, key;
    cin >> s1;
    key = get_key();
    auto coded = code(s1, key);
    std::cout << coded.first << endl;

    std::cout << decode(coded, key);
}
