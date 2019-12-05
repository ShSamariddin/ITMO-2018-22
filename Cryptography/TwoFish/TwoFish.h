//
// Created by maxlun on 10/19/19.
//

#pragma once

#include <cstdint>
#include <string>

struct m_key {
    uint32_t s[4][256];   /* pre-computed S-boxes */
    uint32_t K[40];       /* Round key words */
};

enum m_options {
    option_CBC,
    option_PaddingPKCS7,
    options_default = option_CBC | option_PaddingPKCS7
};

struct m_context {
    uint8_t iv[16];
    m_key key;
    m_options options;
};


void test();


void prepare_key(uint8_t key[], m_key *xkey);


void action(m_key *xkey, uint8_t p[16], uint8_t c[16], const std::string &);

