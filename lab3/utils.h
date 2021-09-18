#ifndef _UTILS_H_
#define _UTILS_H_

#include <string>
#include <vector>

#include "Logger.h"
#include "Matrix.h"

namespace util {
// Function that takes a string as input and trims whitespaces from front and back of the string
void trim(std::string &str);

// Function that tells whether the line is useful or not, i.e. it should not be empty and not a comment
bool isUsefulLine(const std::string &line);

// Function that tells whether the line is valid or not, i.e. it should only contain digits or ' ' or ',' or '-'
bool isValidLine(const std::string &line);

// Function that tells whether the line contains dimensions or not
bool hasDimensions(const std::string &line);

// Function that tells whether the line contains values of matrix or not
bool hasMatrixValues(const std::string &line);

// Get current date and time
std::string getDateTime();

// Function that returns the prefix string for log output
std::string getLogString(const char *filename, int lineNum);

// Function to log the vector<ll> (array) to the log file
void logArray(Logger *logger, const std::vector<ll> &arr);

// Function to log the matrix to the log file
void logMatrix(Logger *logger, const Matrix &mat);

}  // namespace util

#endif  // _UTILS_H_