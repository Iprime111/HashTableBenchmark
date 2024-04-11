#ifndef ERROR_CODES_HPP_
#define ERROR_CODES_HPP_

enum class ErrorCode {
    NO_ERRORS        = 0,
    ALLOCATION_ERROR = 1 << 0,
    FILE_IO_ERROR    = 1 << 1,
    HASH_TABLE_ERROR = 1 << 2,
};

#endif
