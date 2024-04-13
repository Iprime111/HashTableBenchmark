#ifndef WORDS_COMPARATOR_HPP_
#define WORDS_COMPARATOR_HPP_

#include <HashTable.hpp>
#include <cassert>
#include <immintrin.h>

#include "Tracy.hpp"
#include "WordData.hpp"

inline int WordsComparator (HashTableLib::Pair <WordData, WordData> *firstWord, HashTableLib::Pair <WordData, WordData> *secondWord) {
    assert (firstWord);
    assert (secondWord);

    return strcmp (firstWord->key.word, secondWord->key.word);
}

inline int WordsComparatorFast (HashTableLib::Pair <WordData, WordData> *firstWord, HashTableLib::Pair <WordData, WordData> *secondWord) {
    assert (firstWord);
    assert (secondWord);

    __mmask64 cmpMask = {};

    asm volatile (
        "vmovdqu8 %1, %%zmm0\n"
        "vmovdqu8 %2, %%zmm1\n"
        "vpcmpeqb %%zmm1, %%zmm0, %%k0\n"
        "kmovq %%k0, %0\n"
        : "=m" (cmpMask)
        : "m" (* ((__m512i *) firstWord->key.word)), "m" (* ((__m512i *) secondWord->key.word))
    );

    return ~cmpMask;
}

#endif
