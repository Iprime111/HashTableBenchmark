#include <cassert>
#include <Tracy.hpp>
#include <Buffer.h>
#include <HashTable.hpp>
#include <cstdio>

#include "ErrorCodes.hpp"
#include "FileReader.hpp"
#include "HashTableDefinitions.hpp"
#include "Hashes.hpp"
#include "LinkedListDefinitions.hpp"
#include "WordData.hpp"
#include "WordsComparator.hpp"
#include "DataExporter.hpp"
#include "Config.hpp"
#include "GetList.hpp"

//TODO measure time spent by tracy functions

template <HashTableLib::HashFunction <WordData *> Hash, LinkedList::Comparator <HashTableLib::Pair <WordData, WordData> *> ElementComparator>
static ErrorCode RunLookupTests (HashTableLib::HashTable <WordData, WordData, Hash, ElementComparator> *hashTable, Buffer <WordData> *words);

template <HashTableLib::HashFunction <WordData *> Hash, LinkedList::Comparator <HashTableLib::Pair <WordData, WordData> *> ElementComparator>
static size_t CountUniqueValues (HashTableLib::HashTable <WordData, WordData, Hash, ElementComparator> *hashTable);

template <HashTableLib::HashFunction <WordData *> Hash, LinkedList::Comparator <HashTableLib::Pair <WordData, WordData> *> ElementComparator>
static ErrorCode FillHashTable (HashTableLib::HashTable <WordData, WordData, Hash, ElementComparator> *hashTable, const Buffer <WordData> *words);

template <HashTableLib::HashFunction <WordData *> Hash, LinkedList::Comparator <HashTableLib::Pair <WordData, WordData> *> ElementComparator>
static ErrorCode FreeWordsMemory (HashTableLib::HashTable <WordData, WordData, Hash, ElementComparator> *hashTable, Buffer <WordData> *words);
 
int main () {
    printf ("Reading file...\n");

    Buffer <WordData> words = {};
    InitBuffer (&words);

    char *applicationDirectory = GetApplicationDirectory ();
    char *wordsFilePath        = (char *) calloc (FILENAME_MAX, sizeof (char));

    snprintf (wordsFilePath, FILENAME_MAX, WORDS_FILE_PATH, applicationDirectory);
    GetWords (wordsFilePath, &words);

    free (wordsFilePath); 

    printf ("Total words number: %lu\nFilling hash table...\n", words.currentIndex);

    HashTableLib::HashTable <WordData, WordData, Crc32FastHash, WordsComparatorFast> hashTable = {};
    HashTableLib::InitHashTable (&hashTable, HASH_TABLE_SIZE);
    FillHashTable (&hashTable, &words);
    
    printf ("Hash table filled! (%lu unique values)\nRunning lookup test...\n", CountUniqueValues (&hashTable));
    
    if (RunLookupTests(&hashTable, &words) != ErrorCode::NO_ERRORS)
        return 0;

    printf ("Lookup test finished!\n");

    free (applicationDirectory);
    FreeWordsMemory (&hashTable, &words);
    
    return 0;
}

template <HashTableLib::HashFunction <WordData *> Hash, LinkedList::Comparator <HashTableLib::Pair <WordData, WordData> *> ElementComparator>
static ErrorCode RunLookupTests (HashTableLib::HashTable <WordData, WordData, Hash, ElementComparator> *hashTable, Buffer <WordData> *words) {
    ZoneScoped;
    assert (hashTable);
    assert (words);

    for (size_t testIndex = 0; testIndex < LOOKUPS_COUNT; testIndex++) {
        WordData *element = nullptr;

        HashTableLib::FindElement (hashTable, &words->data [testIndex % words->currentIndex], &element);

        if (!element)
            return ErrorCode::HASH_TABLE_ERROR;
    }

    return ErrorCode::NO_ERRORS;
}

template <HashTableLib::HashFunction <WordData *> Hash, LinkedList::Comparator <HashTableLib::Pair <WordData, WordData> *> ElementComparator>
static ErrorCode FreeWordsMemory (HashTableLib::HashTable <WordData, WordData, Hash, ElementComparator> *hashTable, Buffer <WordData> *words) {
    assert (hashTable);
    assert (words);

    DestroyBuffer (words);
    HashTableLib::DestroyHashTable (hashTable);

    return ErrorCode::NO_ERRORS;
}

template <HashTableLib::HashFunction <WordData *> Hash, LinkedList::Comparator <HashTableLib::Pair <WordData, WordData> *> ElementComparator>
static size_t CountUniqueValues (HashTableLib::HashTable <WordData, WordData, Hash, ElementComparator> *hashTable) {
    assert (hashTable);

    size_t valuesCount = 0;
        
    for (size_t listIndex = 0; listIndex < hashTable->capacity; listIndex++)
        valuesCount += (size_t) hashTable->table [listIndex].size - 1;

    return valuesCount;
}

template <HashTableLib::HashFunction <WordData *> Hash, LinkedList::Comparator <HashTableLib::Pair <WordData, WordData> *> ElementComparator>
static ErrorCode FillHashTable (HashTableLib::HashTable <WordData, WordData, Hash, ElementComparator> *hashTable, const Buffer <WordData> *words) {
    assert (hashTable);
    assert (words);

    for (size_t wordIndex = 0; wordIndex < words->currentIndex; wordIndex++) {
        HashTableLib::Pair <WordData, WordData> newEntry = {words->data [wordIndex], words->data [wordIndex]};

        if (HashTableLib::AddUniqueElement (hashTable, &newEntry) != HashTableLib::ErrorCode::NO_ERRORS) {
            return ErrorCode::HASH_TABLE_ERROR;
        }
    }


    return ErrorCode::NO_ERRORS;
}


