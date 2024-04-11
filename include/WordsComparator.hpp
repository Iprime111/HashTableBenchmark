#ifndef WORDS_COMPARATOR_HPP_
#define WORDS_COMPARATOR_HPP_

#include <HashTable.hpp>

#include "WordData.hpp"

inline int WordsComparator (HashTableLib::Pair <WordData, WordData> *firstWord, HashTableLib::Pair <WordData, WordData> *secondWord) {
    return strcmp (firstWord->key.word, secondWord->key.word);
}

#endif
