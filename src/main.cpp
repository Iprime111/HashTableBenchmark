#include <cassert>
#include <Buffer.h>
#include <HashTable.hpp>
#include <cstdio>
#include <Tracy.hpp>

#include "ErrorCodes.hpp"
#include "FileReader.hpp"
#include "Hashes.hpp"
#include "WordData.hpp"
#include "WordsComparator.hpp"
#include "DataExporter.hpp"

const size_t HASH_TABLE_SIZE    = 1499;
const char   WORDS_FILE_PATH [] = "%s/words.txt";

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

    HashTableLib::HashTable <WordData, WordData, ChecksumHash, WordsComparator> hashTable = {};
    HashTableLib::InitHashTable (&hashTable, HASH_TABLE_SIZE);
    FillHashTable (&hashTable, &words);
    
    printf ("Hash table filled! (%lu unique values)\nEnter load factor file path: ", CountUniqueValues (&hashTable));
    
    char *loadFactorFilename = NULL;
    scanf ("%ms[^\n]", &loadFactorFilename);

    if (ExportLoadData (&hashTable, loadFactorFilename) != ErrorCode::NO_ERRORS)
        printf ("Export error!\n");

    free (applicationDirectory);
    free (loadFactorFilename);
    FreeWordsMemory (&hashTable, &words);
    
    return 0;
}

template <HashTableLib::HashFunction <WordData *> Hash, LinkedList::Comparator <HashTableLib::Pair <WordData, WordData> *> ElementComparator>
static ErrorCode FreeWordsMemory (HashTableLib::HashTable <WordData, WordData, Hash, ElementComparator> *hashTable, Buffer <WordData> *words) {
    assert (hashTable);
    assert (words);

    for (size_t wordIndex = 0; wordIndex < words->currentIndex; wordIndex++) {
        free (words->data [wordIndex].word);
    }

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


