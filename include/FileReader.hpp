#ifndef FILE_READER_HPP_
#define FILE_READER_HPP_

#include "Buffer.h"
#include "ErrorCodes.hpp"
#include "WordData.hpp"

ErrorCode GetWords (const char *filename, Buffer <WordData> *words);

#endif
