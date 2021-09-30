#include "exceptions.h"

// if no arguments are provided during execution of program
const char* NoArgumentsException::what() const noexcept {
    return "No arguments received, do you really want to perform something? :/";
}

// if any invalid/unknown argument is provided during execution of program
const char* InvalidArgumentsException::what() const noexcept {
    return "Invalid arguments received, make sure they matches as specified!! :(";
}

// if input is not received as specified in the desired format
const char* InvalidInputException::what() const noexcept {
    return "Invalid input received, make sure input format matches as specified!! :(";
}

// if trying to divide by zero
const char* DivideByZeroException::what() const noexcept {
    return "Can't divide by zero!! Are you really a programmer? :/";
}

// if trying to have positive values like #rows and #columns as negative
const char* NegativeValueException::what() const noexcept {
    return "Value can't be negative!! :/";
}

// if trying to access index out of bounds
const char* OutOfBoundsException::what() const noexcept {
    return "Going out of bounds!! Want to go to the space? :/";
}

// when matrix is provided as non-square matrix for calculating determinant
const char* NonSquareMatrixException::what() const noexcept {
    return "Matrix has to be a square matrix for this operation to perform!! :/";
}

// if invalid dimensions or dimensions not in desired format are given
const char* InvalidDimensionsException::what() const noexcept {
    return "Invalid dimensions of matrix received!! :/";
}

// if user is trying to do invalid operation like (determinant of scalar) (matrix / matrix)
const char* UnsupportedOperationException::what() const noexcept {
    return "Unsupported operation!! :/";
}

// if file we are trying to open is not found
const char* FileNotFoundException::what() const noexcept {
    return "File not found!! :/";
}