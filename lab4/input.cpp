#include "input.h"

#include <getopt.h>

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "Logger.h"
#include "Matrix.h"
#include "constants.h"
#include "exceptions.h"
#include "utils.h"

using ll = long long;

// Function that takes input arguments from command line, parses them and stores them in an array of char
void input::parseArgs(int argc, char **argv, std::vector<char> &args) {
    ll option;
    while ((option = getopt(argc, argv, constants::ALLOWED_ARGS)) != -1) {
        switch (option) {
            case constants::ADD_ARG:
            case constants::SUB_ARG:
            case constants::MUL_ARG:
            case constants::DIV_ARG:
            case constants::TRANSPOSE_ARG:
            case constants::DETERMINANT_ARG:
                args.emplace_back(option);  // add it to array/vector
                break;
            // if it is an invalid/unknown argument
            case constants::INVALID_ARG:
            default:
                throw InvalidArgumentsException();
        }
    }

    //! Logging logic starts
    Logger *logger = Logger::getLogger();
    *logger << util::getLogString(__FILE__, __LINE__) << "Arguments parsed successfully!!\n";
    *logger << util::getLogString(__FILE__, __LINE__) << "Parsed Arguments : ";
    for (auto &arg : args) {
        *logger << arg << ", ";
    }
    *logger << "\n";
    //! Logging logic ends
}

// Function to handle the input which reads an input file as per the input format
void input::handleInput(std::vector<Matrix> &matrices, std::vector<ll> &scalars, std::string &order) {
    std::string line = "";
    while (std::getline(std::cin, line)) {
        // trimming the input line
        util::trim(line);
        if (util::isUsefulLine(line)) {
            // Line should either contain a scalar or dimensions of matrix
            if (!util::isValidLine(line) || util::hasMatrixValues(line)) {
                throw InvalidInputException();
            }

            if (!util::hasDimensions(line)) {
                scalars.emplace_back(std::stoll(line));
                order += constants::SCALAR_SYMBOL;
            } else {
                std::stringstream ss(line);
                std::string num = "";
                int cnt = 0, rows = 0, columns = 0;
                // reading comma separated values
                while (std::getline(ss, num, constants::DIMENSIONS_SEPARATOR)) {
                    ++cnt;
                    if (cnt == 1) {
                        rows = std::stoll(num);
                    } else if (cnt == 2) {
                        columns = std::stoll(num);
                    } else {
                        // line has more than 2 dimensions mentioned for the matrix
                        throw InvalidInputException();
                    }
                }
                Matrix mat(rows, columns);
                std::cin >> mat;
                matrices.emplace_back(mat);
                order += constants::MATRIX_SYMBOL;
            }
        }
    }

    //! Logging logic starts
    Logger *logger = Logger::getLogger();
    *logger << util::getLogString(__FILE__, __LINE__) << "Input parsed successfully!!\n";
    *logger << util::getLogString(__FILE__, __LINE__) << "Found " << (ll)matrices.size() << " number of matrices:\n";
    for (ll i = 0; i < matrices.size(); ++i) {
        *logger << "Matrix number " << i + 1 << ": ";
        util::logMatrix(logger, matrices[i]);
        *logger << "\n";
    }
    *logger << util::getLogString(__FILE__, __LINE__) << "Found " << (ll)scalars.size() << " number of scalars: ";
    util::logArray(logger, scalars);
    *logger << "\n";
    *logger << util::getLogString(__FILE__, __LINE__) << "Order string: " << order << " (where " << constants::SCALAR_SYMBOL << " = SCALAR SYMBOL and " << constants::MATRIX_SYMBOL << " = MATRIX SYMBOL)\n";
    //! Logging logic ends
}