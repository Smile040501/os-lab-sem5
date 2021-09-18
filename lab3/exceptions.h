#ifndef _EXCEPTIONS_H_
#define _EXCEPTIONS_H_

#include <exception>

// My Exception classes to throw error wherever necessary
// Inheriting the standard `exception` class, having default constructor and destructor
// Overriding the virtual function what() inherited from `exception` class

// if no arguments are provided during execution of program
class NoArgumentsException : public std::exception {
   public:
    NoArgumentsException() noexcept = default;
    virtual ~NoArgumentsException() noexcept = default;

    virtual const char* what() const noexcept override;
};

// if any invalid/unknown argument is provided during execution of program
class InvalidArgumentsException : public std::exception {
   public:
    InvalidArgumentsException() noexcept = default;
    virtual ~InvalidArgumentsException() noexcept = default;

    virtual const char* what() const noexcept override;
};

// if input is not received as specified in the desired format
class InvalidInputException : public std::exception {
   public:
    InvalidInputException() noexcept = default;
    virtual ~InvalidInputException() noexcept = default;

    virtual const char* what() const noexcept override;
};

// if trying to divide by zero
class DivideByZeroException : public std::exception {
   public:
    DivideByZeroException() noexcept = default;
    virtual ~DivideByZeroException() noexcept = default;

    virtual const char* what() const noexcept override;
};

// if trying to have positive values like #rows and #columns as negative
class NegativeValueException : public std::exception {
   public:
    NegativeValueException() noexcept = default;
    virtual ~NegativeValueException() noexcept = default;

    virtual const char* what() const noexcept override;
};

// if trying to access index out of bounds
class OutOfBoundsException : public std::exception {
   public:
    OutOfBoundsException() noexcept = default;
    virtual ~OutOfBoundsException() noexcept = default;

    virtual const char* what() const noexcept override;
};

// when matrix is provided as non-square matrix for calculating determinant
class NonSquareMatrixException : public std::exception {
   public:
    NonSquareMatrixException() noexcept = default;
    virtual ~NonSquareMatrixException() noexcept = default;

    virtual const char* what() const noexcept override;
};

// if invalid dimensions or dimensions not in desired format are given
class InvalidDimensionsException : public std::exception {
   public:
    InvalidDimensionsException() noexcept = default;
    virtual ~InvalidDimensionsException() noexcept = default;

    virtual const char* what() const noexcept override;
};

// if user is trying to do invalid operation like (determinant of scalar) (matrix / matrix)
class UnsupportedOperationException : public std::exception {
   public:
    UnsupportedOperationException() noexcept = default;
    virtual ~UnsupportedOperationException() noexcept = default;

    virtual const char* what() const noexcept override;
};

// if file we are trying to open is not found
class FileNotFoundException : public std::exception {
   public:
    FileNotFoundException() noexcept = default;
    virtual ~FileNotFoundException() noexcept = default;

    virtual const char* what() const noexcept override;
};

#endif  // _EXCEPTIONS_H_