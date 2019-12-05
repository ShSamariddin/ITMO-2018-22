

#include <cstdint>
#include "TwoFish.h"

static uint32_t MDS_table[4][256];

static uint8_t q_table[2][256];

static void mdsInit() {
    uint32_t tmp1, tmp2;
    static uint32_t mds_poly_divx_const[] = {0, 0xb4};

    for (uint16_t i = 0; i < 256; i++) {

        tmp1 = (q_table[0][i] >> 1) ^ mds_poly_divx_const[q_table[0][i] & 1];

        tmp2 = (tmp1 >> 1) ^ mds_poly_divx_const[tmp1 & 1] ^ q_table[0][i];

        tmp1 ^= tmp2;


        MDS_table[1][i] = q_table[1][i] << 24 | tmp2 << 16 | tmp1 << 8 | tmp1;
        tmp1 = (q_table[1][i] >> 1) ^ mds_poly_divx_const[q_table[1][i] & 1];
        MDS_table[3][i] = tmp2 << 24 | tmp1 << 16 | q_table[1][i] << 8 | tmp2;
        tmp2 = (tmp1 >> 1) ^ mds_poly_divx_const[tmp1 & 1] ^ q_table[1][i];
        tmp1 ^= tmp2;

        MDS_table[0][i] = tmp1 << 24 | tmp1 << 16 | tmp2 << 8 | q_table[1][i];
        MDS_table[2][i] = tmp1 << 24 | q_table[1][i] << 16 | tmp1 << 8 | tmp2;
    }
}


#define H0(y, L)  MDS_table[0][q_table[0][q_table[0][y]^L[ 8]]^L[0]]
#define H1(y, L)  MDS_table[1][q_table[0][q_table[1][y]^L[ 9]]^L[1]]
#define H2(y, L)  MDS_table[2][q_table[1][q_table[0][y]^L[10]]^L[2]]
#define H3(y, L)  MDS_table[3][q_table[1][q_table[1][y]^L[11]]^L[3]]


static void multiply(m_key *xkey, const uint8_t *ptr) {
    for (int i = 0; i < 256; i++) {
        xkey->s[0][i] = H0(i, ptr);
        xkey->s[1][i] = H1(i, ptr);
        xkey->s[2][i] = H2(i, ptr);
        xkey->s[3][i] = H3(i, ptr);
    }
}