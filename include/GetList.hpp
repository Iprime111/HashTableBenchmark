#ifndef GET_LIST_HPP
#define GET_LIST_HPP

#include <Tracy.hpp>
#include <HashTable.hpp>
#include <cstdint>

#include "Config.hpp"
#include "Hashes.hpp"
#include "WordData.hpp"
#include "WordsComparator.hpp"

namespace HashTableInternal {
    template <>
    inline LinkedList::List <HashTableLib::Pair <WordData, WordData>, WordsComparatorFast> 
        *GetList (HashTableLib::HashTable <WordData, WordData, Crc32FastHash, WordsComparatorFast> *table, WordData *elementKey) {
        ZoneScoped;
    
        uint32_t listIndex = 0;
        asm (
            "and %2, %1\n"
            "movl %1, %0"
            : "=r" (listIndex)
            : "r" (Crc32FastHash (elementKey)), "r" ((uint32_t) HASH_TABLE_SIZE - 1)
        );
    
        return &table->table [listIndex];
    }
}  
#endif
