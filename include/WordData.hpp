#ifndef WORD_DATA_HPP_
#define WORD_DATA_HPP_

#include <cstddef>

const size_t MAX_WORD_LENGTH = 64;

struct WordData {
    char   word [MAX_WORD_LENGTH] __attribute__ ((aligned (16))) = "";
    size_t length                 = 0;
};

#endif
