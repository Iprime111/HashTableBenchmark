#include <cassert>
#include <cstddef>
#include <cstdio>
#include <Buffer.h>
#include <Tracy.hpp>

#include "ErrorCodes.hpp"
#include "WordData.hpp"
#include "FileReader.hpp"

static size_t GetFileSize     (FILE *file);
static char  *ReadFileContent (const char *filename, size_t *fileSize);

//WARNING assumes that word length < 64 bytes
ErrorCode GetWords (const char *filename, Buffer <WordData> *words) {
    assert (filename);
    assert (words);
     
    size_t fileSize    = 0;
    char  *fileContent = ReadFileContent (filename, &fileSize);

    if (!fileContent)
        return ErrorCode::FILE_IO_ERROR;

    char *currentWord = fileContent;

    while (currentWord < fileContent + fileSize) {
        WordData newWord = {};
        int wordLength   = 0;

        sscanf (currentWord, "%s%n[^\n]", newWord.word, &wordLength);
        newWord.length = (size_t) wordLength - 1;

        WriteDataToBuffer (words, &newWord, 1);
        currentWord += wordLength;
    }

    free (fileContent);

    return ErrorCode::NO_ERRORS;
}

static char *ReadFileContent (const char *filename, size_t *fileSize) {
    assert (filename);
    assert (fileSize);

    FILE *wordsFile = fopen (filename, "r");
    
    if (!wordsFile)
        return nullptr;

    *fileSize = GetFileSize (wordsFile);

    char *fileText = (char *) calloc (*fileSize + 1, sizeof (char));
    
    if (!fileText)
        return nullptr;

    fread  (fileText, sizeof (char), *fileSize, wordsFile);
    fclose (wordsFile);

    return fileText;
}

static size_t GetFileSize (FILE *file) {
    assert (file);

    long beginPosition = ftell (file);

    fseek (file, 0, SEEK_END);
    size_t fileSize = (size_t) ftell (file);
    fseek (file, beginPosition, SEEK_SET);
    
    return fileSize;
}
