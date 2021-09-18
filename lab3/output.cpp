#include "output.h"

#include <iostream>
#include <string>
#include <vector>

#include "Logger.h"
#include "Matrix.h"
#include "constants.h"
#include "exceptions.h"
#include "utils.h"

using ll = long long;

// Function to map option to operation log string
std::string getOperationLogString(char option) {
    switch (option) {
        case constants::ADD_ARG: {
            return "Adding";
        }
        case constants::SUB_ARG: {
            return "Subtracting";
        }
        case constants::MUL_ARG: {
            return "Multiplying";
        }
        case constants::DIV_ARG: {
            return "Dividing";
        }
        default:
            throw InvalidArgumentsException();
    }
}

// Function to check if the given (index + offset) lies within index range of container
template <typename T>
void output::assertIndexBounds(const T &container, ll index, ll offset) {
    if (index + offset >= container.size()) throw InvalidInputException();
}

// Function that evaluates the result of (val1 op val2) and stores it in val3
template <typename T1, typename T2, typename T3>
void output::evaluate(T1 &val1, T2 &val2, char option, T3 &val3) {
    switch (option) {
        case constants::ADD_ARG: {
            val3 = val1 + val2;
            break;
        }
        case constants::SUB_ARG: {
            val3 = val1 - val2;
            break;
        }
        case constants::MUL_ARG: {
            val3 = val1 * val2;
            break;
        }
        case constants::DIV_ARG: {
            val3 = val1 / val2;
            break;
        }
        default:
            throw InvalidArgumentsException();
    }
}

// Function that performs operations in the order in which command line arguments are specified
void output::performOperations(const std::vector<char> &args, const std::vector<Matrix> &matrices, const std::vector<ll> &scalars, const std::string &order) {
    // if no argument is specified
    if (args.size() == 0) {
        if (order.length() != 0) throw NoArgumentsException();
        return;
    }

    // first = true if processing the very first argument
    // currentMat = true if result of last computation was a matrix
    bool first = true, currentMat = true;

    // i, j, k = current index to process for matrices, scalars and order respectively
    ll i = 0, j = 0, k = 0;

    // result of last computation if it was a scalar result
    ll scalarResult = 0;

    // result of last computation if it was a matrix result
    Matrix matrixResult(1, 1);

    Logger *logger = Logger::getLogger();

    // looping all the arguments received
    for (auto &option : args) {
        switch (option) {
            case constants::ADD_ARG:
            case constants::SUB_ARG:
            case constants::MUL_ARG:
            case constants::DIV_ARG: {
                if (first) {  // if we are processing the very first argument
                    assertIndexBounds(order, k, 1);
                    if (order[k] == constants::SCALAR_SYMBOL && order[k + 1] == constants::SCALAR_SYMBOL) {  // both are scalars
                        assertIndexBounds(scalars, j, 1);
                        if (option == constants::DIV_ARG && scalars[j + 1] == 0) throw DivideByZeroException();

                        currentMat = false;
                        evaluate(scalars[j], scalars[j + 1], option, scalarResult);
                        j += 2;

                        //! Logging logic starts
                        *logger << util::getLogString(__FILE__, __LINE__) << getOperationLogString(option) << " two scalars: " << scalars[j - 2] << " and " << scalars[j - 1] << "\n";
                        *logger << "Result: " << scalarResult << "\n";
                        //! Logging logic ends

                    } else if (order[k] == constants::MATRIX_SYMBOL && order[k + 1] == constants::MATRIX_SYMBOL) {  // both are matrices
                        assertIndexBounds(matrices, i, 1);
                        if (option == constants::DIV_ARG) throw UnsupportedOperationException();

                        currentMat = true;
                        evaluate(matrices[i], matrices[i + 1], option, matrixResult);
                        i += 2;

                        //! Logging logic starts
                        *logger << util::getLogString(__FILE__, __LINE__) << getOperationLogString(option) << " two matrices: ";
                        util::logMatrix(logger, matrices[i - 2]);
                        *logger << " and ";
                        util::logMatrix(logger, matrices[i - 1]);
                        *logger << "\nResult: ";
                        util::logMatrix(logger, matrixResult);
                        *logger << "\n";
                        //! Logging logic ends

                    } else {  // matrix and a scalar
                        assertIndexBounds(matrices, i);
                        assertIndexBounds(scalars, j);
                        currentMat = true;
                        evaluate(matrices[i], scalars[j], option, matrixResult);
                        ++i;
                        ++j;

                        //! Logging logic starts
                        *logger << util::getLogString(__FILE__, __LINE__) << getOperationLogString(option) << " a scalar and a matrix: " << scalars[j - 1] << " and ";
                        util::logMatrix(logger, matrices[i - 1]);
                        *logger << "\nResult: ";
                        util::logMatrix(logger, matrixResult);
                        *logger << "\n";
                        //! Logging logic ends
                    }
                    k += 2;
                    first = false;
                } else {  // not the first argument
                    assertIndexBounds(order, k);
                    if (order[k] == constants::SCALAR_SYMBOL) {
                        assertIndexBounds(scalars, j);
                        if (currentMat) {
                            Matrix prevMatrixResult = matrixResult;  //! Logging logic
                            evaluate(matrixResult, scalars[j], option, matrixResult);

                            //! Logging logic starts
                            *logger << util::getLogString(__FILE__, __LINE__) << getOperationLogString(option) << " a scalar and a matrix: " << scalars[j] << " and ";
                            util::logMatrix(logger, prevMatrixResult);
                            *logger << "\nResult: ";
                            util::logMatrix(logger, matrixResult);
                            *logger << "\n";
                            //! Logging logic ends

                        } else {
                            if (option == constants::DIV_ARG && scalars[j] == 0) throw DivideByZeroException();
                            ll prevScalarResult = scalarResult;  //! Logging logic
                            evaluate(scalarResult, scalars[j], option, scalarResult);

                            //! Logging logic starts
                            *logger << util::getLogString(__FILE__, __LINE__) << getOperationLogString(option) << " two scalars: " << prevScalarResult << " and " << scalars[j] << "\n";
                            *logger << "Result: " << scalarResult << "\n";
                            //! Logging logic ends
                        }
                        ++j;
                    } else {
                        assertIndexBounds(matrices, i);
                        if (currentMat) {
                            if (option == constants::DIV_ARG) throw UnsupportedOperationException();
                            Matrix prevMatrixResult = matrixResult;  //! Logging logic
                            evaluate(matrixResult, matrices[i], option, matrixResult);

                            //! Logging logic starts
                            *logger << util::getLogString(__FILE__, __LINE__) << getOperationLogString(option) << " two matrices: ";
                            util::logMatrix(logger, prevMatrixResult);
                            *logger << " and ";
                            util::logMatrix(logger, matrices[i]);
                            *logger << "\nResult: ";
                            util::logMatrix(logger, matrixResult);
                            *logger << "\n";
                            //! Logging logic ends

                        } else {
                            evaluate(matrices[i], scalarResult, option, matrixResult);
                            currentMat = true;

                            //! Logging logic starts
                            *logger << util::getLogString(__FILE__, __LINE__) << getOperationLogString(option) << " a scalar and a matrix: " << scalarResult << " and ";
                            util::logMatrix(logger, matrices[i]);
                            *logger << "\nResult: ";
                            util::logMatrix(logger, matrixResult);
                            *logger << "\n";
                            //! Logging logic ends
                        }
                        ++i;
                    }
                    ++k;
                }
                break;
            }
            case constants::TRANSPOSE_ARG: {
                //! Logging logic starts
                *logger << util::getLogString(__FILE__, __LINE__) << "Taking transpose of the matrix: ";
                //! Logging logic ends

                if (first) {  // if we are processing the very first argument
                    assertIndexBounds(order, k);
                    if (order[k] == constants::SCALAR_SYMBOL) throw UnsupportedOperationException();

                    assertIndexBounds(matrices, i);
                    currentMat = true;
                    matrixResult = matrices[i].transpose();
                    ++i;
                    ++k;
                    first = false;

                    //! Logging logic starts
                    util::logMatrix(logger, matrices[i - 1]);
                    //! Logging logic ends

                } else {  // not the first argument
                    if (!currentMat) throw UnsupportedOperationException();

                    //! Logging logic starts
                    util::logMatrix(logger, matrixResult);
                    //! Logging logic ends

                    matrixResult = matrixResult.transpose();
                }

                //! Logging logic starts
                *logger << "\nResult: ";
                util::logMatrix(logger, matrixResult);
                *logger << "\n";
                //! Logging logic ends
                break;
            }
            case constants::DETERMINANT_ARG: {
                //! Logging logic starts
                *logger << util::getLogString(__FILE__, __LINE__) << "Taking determinant of the matrix: ";
                //! Logging logic ends

                if (first) {  // if we are processing the very first argument
                    assertIndexBounds(order, k);
                    if (order[k] == constants::SCALAR_SYMBOL) throw UnsupportedOperationException();

                    assertIndexBounds(matrices, i);
                    scalarResult = matrices[i].determinant();
                    ++i;
                    ++k;
                    first = false;

                    //! Logging logic starts
                    util::logMatrix(logger, matrices[i - 1]);
                    //! Logging logic ends

                } else {  // not the first argument
                    if (!currentMat) throw UnsupportedOperationException();

                    scalarResult = matrixResult.determinant();

                    //! Logging logic starts
                    util::logMatrix(logger, matrixResult);
                    //! Logging logic ends
                }
                currentMat = false;

                //! Logging logic starts
                *logger << "\nResult: " << scalarResult << "\n";
                //! Logging logic ends
                break;
            }
            default:
                throw InvalidArgumentsException();
        }
    }

    if (currentMat) {
        std::cout << matrixResult << std::endl;
    } else {
        std::cout << scalarResult << std::endl;
    }

    //! Logging logic starts
    *logger << util::getLogString(__FILE__, __LINE__) << " Result obtained: ";

    if (currentMat) {
        util::logMatrix(logger, matrixResult);
        *logger << "\n";
    } else {
        *logger << scalarResult << "\n";
    }

    if (i != matrices.size() && j != scalars.size()) {
        *logger << util::getLogString(__FILE__, __LINE__) << "Ignored last " << ((ll)matrices.size() - i) << " extra matrices and last " << ((ll)scalars.size() - j) << " extra scalars.\n";
    } else if (i != matrices.size()) {
        *logger << util::getLogString(__FILE__, __LINE__) << "Ignored last " << ((ll)matrices.size() - i) << " extra matrices.\n";
    } else if (j != scalars.size()) {
        *logger << util::getLogString(__FILE__, __LINE__) << "Ignored last " << ((ll)scalars.size() - j) << " extra scalars.\n";
    }
    //! Logging logic ends
}