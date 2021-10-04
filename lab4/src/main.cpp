#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "Logger.h"
#include "Matrix.h"
#include "Scalar.h"
#include "exceptions.h"
#include "input.h"
#include "output.h"
#include "utils.h"

using ll = long long;

// __FILE__ : in-built in C++ to get the current filename
// __LINE__ : in-built in C++ to get the current line number

int main(int argc, char **argv) {
    Scalar test();
    // Logger object pointer to write debug/error messages to log file
    Logger *logger = nullptr;
    try {
        // Getting the instance of the singleton Logger class to write to log files
        logger = Logger::getLogger();

        *logger << "=============================================================================================================";

        std::vector<char> args{};  // Storing parsed arguments

        input::parseArgs(argc, argv, args);  // Parsing arguments received from command line

        std::vector<Matrix> matrices{};  // Storing all the matrices received from input
        std::vector<Scalar> scalars{};   // Storing all the scalars received from input
        std::string order = "";          // Keep track of order of matrices and scalars in input

        input::handleInput(matrices, scalars, order);  // Parsing input

        // Performing operations in order as received from command line on input
        output::performOperations(args, matrices, scalars, order);

    } catch (const std::exception &ex) {
        // In case any error occur
        // typeid(ex).name() -> to get the name of the exception occurred
        *logger << util::getLogString(__FILE__, __LINE__) << typeid(ex).name() << " : " << ex.what() << "\n";
    }

    if (logger) {
        *logger << "=============================================================================================================\n";
    }

    // Freeing memory allocated for logger object and closing the log file opened
    Logger::close();

    return EXIT_SUCCESS;
}