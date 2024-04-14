#ifndef WORDS_COMPARATOR_HPP_
#define WORDS_COMPARATOR_HPP_

#include <HashTable.hpp>
#include <cassert>
#include <immintrin.h>

#include "WordData.hpp"

extern int StreqFast (char *firstWord, char *secondWord);

inline int WordsComparator (HashTableLib::Pair <WordData, WordData> *firstWord, HashTableLib::Pair <WordData, WordData> *secondWord) {
    assert (firstWord);
    assert (secondWord);

    return strcmp (firstWord->key.word, secondWord->key.word);
}

inline int WordsComparatorFast (HashTableLib::Pair <WordData, WordData> *firstWord, HashTableLib::Pair <WordData, WordData> *secondWord) {
    assert (firstWord);
    assert (secondWord);

    return ~StreqFast (firstWord->key.word, secondWord->key.word);
}

#endif
