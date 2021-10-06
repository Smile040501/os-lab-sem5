#ifndef _CONSTANTS_H_
#define _CONSTANTS_H_

#include <string>

namespace constants {
const char COMMENT_STARTER = '#';
const char DIMENSIONS_SEPARATOR = ' ';
const char MATRIX_VALUES_SEPARATOR = ',';

const char SCALAR_SYMBOL = '0';
const char MATRIX_SYMBOL = '1';

const char ADD_ARG = 'a';
const char SUB_ARG = 's';
const char MUL_ARG = 'm';
const char DIV_ARG = 'd';
const char TRANSPOSE_ARG = 't';
const char DETERMINANT_ARG = 'x';
const char INVALID_ARG = '?';
const char *const ALLOWED_ARGS = ":asmdtx";

// This path is with respect to the `Makefile` present in the root directory
const std::string LOG_FILE = "./build/messages.log";
}  // namespace constants

#endif  // _CONSTANTS_H_