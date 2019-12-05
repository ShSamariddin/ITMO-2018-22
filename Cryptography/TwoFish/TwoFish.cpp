#include <cstring>
#include "TwoFish.h"
#include <iostream>
#include <vector>
#include "H.cpp"


inline uint32_t rol(uint32_t in, size_t x) {
    __asm__ ("roll %%cl, %0" : "+d" (in) : "c" (x));
    return in;
}

inline uint32_t ror(uint32_t in, size_t x) {
    __asm__ ("rorl %%cl, %0" : "+d" (in) : "c" (x));
    return in;
}

inline uint8_t ror1_4bit_register(uint8_t in) {
    return ((in) >> 1) | (((in) << 3) & 0x8);
}

inline uint8_t get_byte(uint32_t n, uint8_t b) {
    return (((n) >> 8 * (b)) & 0xff);
}

inline uint8_t get_0_byte(uint32_t n) {
    return get_byte(n, 0);
}

inline uint8_t get_1_byte(uint32_t n) {
    return get_byte(n, 1);
}

inline uint8_t get_2_byte(uint32_t n) {
    return get_byte(n, 2);
}

inline uint8_t get_3_byte(uint32_t n) {
    return get_byte(n, 3);
}

inline uint32_t getint(const uint8_t *p) {
    return *((uint32_t *) p);
}

inline void putint(uint32_t &a, uint8_t *p) {
    *((uint32_t *) p) = a;
}

void testing() {

    uint8_t k128[] = {
            0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78,
            0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78,
    };
    uint8_t p128[5][16] = {
            {
                    "HELLO"
            },
            {
                    "WORLD"
            },
            {
                    "CRYPTO <3"
            },
            {
                    "Help"
            },
            {
                    "TwoFish"
            }
    };


    uint8_t tmp[16];
    uint8_t tmp1[16];
    m_key xkey{};

    prepare_key(k128, &xkey);
    for (auto &i : p128) {
        action(&xkey, i, tmp, "encrypt");
        action(&xkey, tmp, tmp1, "decrypt");
        if (memcmp(i, tmp1, 16) != 0) {
            std::cout << "Error" << std::endl;
            exit(0);
        }
    }
    std::cout << "Man test passed" << std::endl;
    for (int i1 = 0; i1 < 1000; ++i1) {
        std::vector<uint8_t> data1{};
        for (int i = 0; i < 16; ++i) {
            data1.push_back(rand());
        }
        action(&xkey, data1.data(), tmp, "encrypt");
        action(&xkey, tmp, tmp1, "decrypt");
        if (memcmp(data1.data(), tmp1, 16) != 0) {
            std::cout << "Error" << std::endl;
            exit(0);
        }
    }
    std::cout << "Random test passed" << std::endl;
}


uint8_t t_table[2][4][16] = {
        {
                {0x8, 0x1, 0x7, 0xD, 0x6, 0xF, 0x3, 0x2, 0x0, 0xB, 0x5, 0x9, 0xE, 0xC, 0xA, 0x4},
                {0xE, 0xC, 0xB, 0x8, 0x1, 0x2, 0x3, 0x5, 0xF, 0x4, 0xA, 0x6, 0x7, 0x0, 0x9, 0xD},
                {0xB, 0xA, 0x5, 0xE, 0x6, 0xD, 0x9, 0x0, 0xC, 0x8, 0xF, 0x3, 0x2, 0x4, 0x7, 0x1},
                {0xD, 0x7, 0xF, 0x4, 0x1, 0x2, 0x6, 0xE, 0x9, 0xB, 0x3, 0x0, 0x8, 0x5, 0xC, 0xA}
        },
        {
                {0x2, 0x8, 0xB, 0xD, 0xF, 0x7, 0x6, 0xE, 0x3, 0x1, 0x9, 0x4, 0x0, 0xA, 0xC, 0x5},
                {0x1, 0xE, 0x2, 0xB, 0x4, 0xC, 0x3, 0x7, 0x6, 0xD, 0xA, 0x5, 0xF, 0x9, 0x0, 0x8},
                {0x4, 0xC, 0x7, 0x5, 0x1, 0x6, 0x9, 0xA, 0x0, 0xE, 0xD, 0x8, 0x2, 0xB, 0x3, 0xF},
                {0xB, 0x9, 0x5, 0x1, 0xC, 0x3, 0xD, 0xE, 0x6, 0x4, 0x7, 0xF, 0x2, 0x0, 0x8, 0xA}
        }
};


void qinit(uint8_t q[2][256]) {
    uint8_t a0, b0, a1, b1; //4bits
    for (int j = 0; j < 2; ++j) {
        for (uint16_t i = 0; i < 256; i++) {

            a0 = i / 16;
            b0 = i % 16;
            a1 = a0 ^ b0;
            b1 = a0 ^ ror1_4bit_register(b0) ^ ((a0 * 8) & 8);
            a0 = t_table[j][0][a1];
            b0 = t_table[j][1][b1];
            a1 = a0 ^ b0;
            b1 = a0 ^ ror1_4bit_register(b0) ^ ((a0 * 8) & 8);
            a0 = t_table[j][2][a1];
            b0 = t_table[j][3][b1];

            q[j][i] = (uint8_t) ((b0 * 16) + a0);
        }
    }
}

static uint32_t h(int k, uint8_t L[]) {
    return H0(k, L) ^ H1(k, L) ^ H2(k, L) ^ H3(k, L);
}

void prepare_key(uint8_t key[], m_key *xkey) {

    uint8_t buffer[68];
    uint32_t B1, B2;

    memcpy(buffer, key, 16);
    memset(buffer + 16, 0, 52);
    for (int i = 0; i < 40; i += 2) {

        uint32_t temp1;

        B1 = h(i, buffer);
        B2 = h(i + 1, buffer + 4);
        B2 = rol(B2, 8);

        B1 += B2;
        B2 += B1;
        xkey->K[i] = B1;
        xkey->K[i + 1] = rol(B2, 9);
    }

    multiply(xkey, (buffer + 32));

    memset(buffer, 0, 68);
}

inline uint32_t g0(uint32_t X, m_key *key) {
    return (key->s[0][get_0_byte(X)] ^ key->s[1][get_1_byte(X)] ^ key->s[2][get_2_byte(X)] ^ key->s[3][get_3_byte(X)]);
}

inline uint32_t g1(uint32_t X, m_key *key) {
    return (key->s[0][get_3_byte(X)] ^ key->s[1][get_0_byte(X)] ^ key->s[2][get_1_byte(X)] ^ key->s[3][get_2_byte(X)]);
}

void encrypt(uint32_t &A, uint32_t &B, uint32_t &C, uint32_t &D, m_key *xkey) {
    for (int i = 0; i < 8; ++i) {
        uint32_t temp = g0(A, xkey);
        uint32_t temp1 = g1(B, xkey);
        C ^= temp + temp1 + xkey->K[8 + 4 * (i)];
        C = ror(C, 1);
        D = rol(D, 1);
        D ^= temp + 2 * temp1 + xkey->K[8 + 4 * (i) + 1];


        temp = g0(C, xkey);
        temp1 = g1(D, xkey);
        A ^= temp + temp1 + xkey->K[8 + 4 * (i) + 2];
        A = ror(A, 1);
        B = rol(B, 1);
        B ^= temp + 2 * temp1 + xkey->K[8 + 4 * (i) + 3];
    }
}

void decrypt(uint32_t &A, uint32_t &B, uint32_t &C, uint32_t &D, m_key *xkey) {
    for (uint8_t i = 8; i--;) {
        uint32_t temp = g0(A, xkey);
        uint32_t temp1 = g1(B, xkey);
        C = rol(C, 1);
        C ^= temp + temp1 + xkey->K[8 + 4 * (i) + 2];
        D ^= temp + 2 * temp1 + xkey->K[8 + 4 * (i) + 3];
        D = ror(D, 1);


        temp = g0(C, xkey);
        temp1 = g1(D, xkey);
        A = rol(A, 1);
        A ^= temp + temp1 + xkey->K[8 + 4 * (i)];
        B ^= temp + 2 * temp1 + xkey->K[8 + 4 * (i) + 1];
        B = ror(B, 1);
    }
}

void action(m_key *xkey, uint8_t p[16], uint8_t c[16], const std::string &status) {
    uint32_t B1, B2, B3, B4;
    uint8_t off;
    bool flag;

    if (status == "encrypt") {
        flag = false;
        off = 0;
    } else if (status == "decrypt") {
        flag = true;
        off = 4;
    } else {
        std::cout << "Error" << std::endl;
        exit(1);
    }

    B1 = getint(p) ^ xkey->K[off];
    B2 = getint(p + 4) ^ xkey->K[off + 1];
    B3 = getint(p + 8) ^ xkey->K[off + 2];
    B4 = getint(p + 12) ^ xkey->K[off + 3];

    off += 4;
    off %= 8;
    if (flag) {
        decrypt(B1, B2, B3, B4, xkey);
    } else {
        encrypt(B1, B2, B3, B4, xkey);
    }

    B3 ^= xkey->K[off];
    B4 ^= xkey->K[off + 1];
    B1 ^= xkey->K[off + 2];
    B2 ^= xkey->K[off + 3];
    putint(B3, c);
    putint(B4, c + 4);
    putint(B1, c + 8);
    putint(B2, c + 12);
}

int main() {
    qinit(q_table);
    mdsInit();

    testing();
}