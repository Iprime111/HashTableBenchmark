#ifndef DATA_EXPORTER_HPP_
#define DATA_EXPORTER_HPP_

#include <unistd.h>
#include <libgen.h>
#include <HashTable.hpp>
#include <Buffer.h>

#include "ErrorCodes.hpp"
#include "WordData.hpp"

const static size_t MAX_CSV_ROW_LENGTH = 64;

char *GetApplicationDirectory ();

template <HashTableLib::HashFunction <WordData *> Hash, LinkedList::Comparator <HashTableLib::Pair <WordData, WordData> *> ElementComparator>
ErrorCode ExportLoadData (HashTableLib::HashTable <WordData, WordData, Hash, ElementComparator> *hashTable, const char *filename) {
    assert (hashTable);
    assert (filename);

    FILE *outFile = fopen (filename, "w");

    if (!outFile)
        return ErrorCode::FILE_IO_ERROR;

    Buffer <char> outBuffer = {};
    InitBuffer (&outBuffer);

    char rowBuffer [MAX_CSV_ROW_LENGTH] = "";

    for (size_t listIndex = 0; listIndex < hashTable->capacity; listIndex++) {
        snprintf (rowBuffer, MAX_CSV_ROW_LENGTH, "%ld,", hashTable->table [listIndex].size - 1);
        WriteStringToBuffer (&outBuffer, rowBuffer);
    }

    fwrite (outBuffer.data, sizeof (char), outBuffer.currentIndex, outFile);
    fclose (outFile);
    DestroyBuffer (&outBuffer);

    return ErrorCode::NO_ERRORS;
}


#endif
