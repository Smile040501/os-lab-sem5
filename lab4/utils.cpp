#include "utils.h"

#include <cctype>
#include <ctime>
#include <string>
#include <vector>

#include "Logger.h"
#include "Matrix.h"
#include "constants.h"

using ll = long long;

// Function that takes a string as input and trims whitespaces from front and back of the string
void util::trim(std::string &str) {
    // trim from front
    ll i = 0;
    while (i < str.length() && std::isspace(str[i])) {
        ++i;
    }
    str.erase(0, i);

    if (str.length() == 0) return;

    // trim from back
    i = str.length() - 1;
    while (i >= 0 && std::isspace(str[i])) {
        --i;
    }
    str.erase(i + 1, str.length() - i - 1);
}

// Function that tells whether the line is useful or not, i.e. it should not be empty and not a comment
bool util::isUsefulLine(const std::string &line) {
    return (line.length() != 0 && line[0] != constants::COMMENT_STARTER);
}

// Function that tells whether the line is valid or not, i.e. it should only contain digits or ' ' or ',' or '-'
bool util::isValidLine(const std::string &line) {
    for (auto &c : line) {
        if (!isdigit(c) && c != constants::DIMENSIONS_SEPARATOR && c != constants::MATRIX_VALUES_SEPARATOR && c != '-') {
            return false;
        }
    }
    return true;
}

// Function that tells whether the line contains dimensions or not
bool util::hasDimensions(const std::string &line) {
    return line.find(constants::DIMENSIONS_SEPARATOR) != std::string::npos;
}

// Function that tells whether the line contains values of matrix or not
bool util::hasMatrixValues(const std::string &line) {
    return line.find(constants::MATRIX_VALUES_SEPARATOR) != std::string::npos;
}

// Get current date and time
std::string util::getDateTime() {
    std::time_t now = std::time(nullptr);
    std::string result = std::ctime(&now);
    return result.substr(0, result.length() - 1);
}

// Function that returns the prefix string for log output
std::string util::getLogString(const char *filename, int lineNum) {
    return "\n" + util::getDateTime() + " :: " + std::string(filename) + ":" + std::to_string(lineNum) + " ~ ";
}

// Function to log the vector<ll> (array) to the log file
void util::logArray(Logger *logger, const std::vector<ll> &arr) {
    *logger << "{ ";
    for (ll i = 0; i < arr.size(); ++i) {
        *logger << arr[i];
        if (i != arr.size() - 1) *logger << ", ";
    }
    *logger << " }";
}

// Function to log the vector<Scalar> (array) to the log file
void util::logArray(Logger *logger, const std::vector<Scalar> &arr) {
    *logger << "{ ";
    for (ll i = 0; i < arr.size(); ++i) {
        *logger << arr[i];
        if (i != arr.size() - 1) *logger << ", ";
    }
    *logger << " }";
}

// Function to log the matrix to the log file
void util::logMatrix(Logger *logger, const Matrix &mat) {
    *logger << "[ ";
    for (ll i = 0; i < mat.getRows(); ++i) {
        util::logArray(logger, mat.getMatrix()[i]);
        if (i != mat.getRows() - 1) *logger << ", ";
    }
    *logger << " ]";
}