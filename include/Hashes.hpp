#ifndef HASHES_HPP_
#define HASHES_HPP_

#include <cassert>
#include <cstdint>

#include "WordData.hpp"

inline uint32_t OnlyZeroHash (WordData *word) {
    return 0;
}

inline uint32_t FirstLetterHash (WordData *word) {
    assert (word);
    assert (word->word);

    return (uint32_t) word->word [0];
}

inline uint32_t WordLengthHash (WordData *word) {
    assert (word);

    return (uint32_t) word->length;
}

inline uint32_t ChecksumHash (WordData *word) {
    assert (word);
    assert (word->word);

    uint32_t checksum = 0;

    for (size_t letterIndex = 0; letterIndex < word->length; letterIndex++) {
        checksum += (uint32_t) word->word [letterIndex];
    }

    return checksum;
}

inline uint32_t NormalizedChecksumHash (WordData *word) {
    assert (word);
    assert (word->word);

    uint32_t checksum = 0;

    for (size_t letterIndex = 0; letterIndex < word->length; letterIndex++) {
        checksum += (uint32_t) word->word [letterIndex];
    }

    return checksum / (uint32_t) word->length;
}

inline uint32_t RorHash (WordData *word) {
    assert (word);
    assert (word->word);

    uint32_t hash = 0;

    for (size_t charIndex = 0; charIndex < word->length; charIndex++) {
        hash = ((hash >> 1) | (hash << (sizeof (hash) - 1) )) ^ ((uint32_t) word->word [charIndex]);
    }

    return hash;
}

inline uint32_t Crc32Hash (WordData *word) {
    assert (word);
    assert (word->word);

    uint32_t hash = 0xFFFFFFFF;
    uint32_t mask = 0;

    for (size_t byteIndex = 0; byteIndex < word->length; byteIndex++) {

        uint32_t byte = (uint32_t) word->word [byteIndex];
        hash = hash ^ byte;

        for (int bitIndex = 7; bitIndex >= 0; bitIndex--) {
            mask = -(hash & 1);
            hash = (hash >> 1) ^ (0xEDB88320 & mask);
        }
    }

    return ~hash; 
}

#endif
