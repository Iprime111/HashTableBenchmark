#ifndef WORDS_COMPARATOR_HPP_
#define WORDS_COMPARATOR_HPP_

#include <HashTable.hpp>
#include <cassert>
#include <cstdint>
#include <immintrin.h>
#include <Tracy.hpp>

#include "WordData.hpp"

extern uint64_t StreqFast (char *firstWord, char *secondWord);

inline int WordsComparator (HashTableLib::Pair <WordData, WordData> *firstWord, HashTableLib::Pair <WordData, WordData> *secondWord) {
    ZoneScoped;
    assert (firstWord);
    assert (secondWord);

    return strcmp (firstWord->key.word, secondWord->key.word);
}

inline int WordsComparatorFast (HashTableLib::Pair <WordData, WordData> *firstWord, HashTableLib::Pair <WordData, WordData> *secondWord) {
    ZoneScoped;
    assert (firstWord);
    assert (secondWord);

    uint64_t mask = ~StreqFast (firstWord->key.word, secondWord->key.word);
    return (int) (mask | (mask << sizeof (int)));
}

inline int WordsComparatorFastInline (HashTableLib::Pair <WordData, WordData> *firstWord, HashTableLib::Pair <WordData, WordData> *secondWord) {
    ZoneScoped;
    assert (firstWord);
    assert (secondWord);

    uint64_t mask = 0;
    asm volatile (
        "vmovdqu8 %1, %%zmm0\n"
        "vmovdqu8 %2, %%zmm1\n"
        "vpcmpeqb %%zmm1, %%zmm0, %%k0\n"
        "kmovq %%k0, %0\n"
        : "=m" (mask)
        : "m" (firstWord->key.word), "m" (secondWord->key.word)
    );

    mask = ~mask;
    return (int) (mask | (mask << sizeof (int)));
}

#endif
