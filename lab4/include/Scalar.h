#ifndef _SCALAR_H_
#define _SCALAR_H_

#include <iostream>

#include "Matrix.h"

using ll = long long;

// To remove cyclic dependecy of header files
class Matrix;

// Scalar class to represent a scalar
class Scalar {
   public:
    // Constructor
    Scalar(ll val) noexcept;

    // Destructor
    ~Scalar() noexcept;

    // Default Copy Constructor
    Scalar(const Scalar &val) = default;

    // Default Move Constructor
    Scalar(Scalar &&val) = default;

    // Getters
    int getVal() const noexcept;

    // Overloaded operators
    // Default overloaded assignment operator
    Scalar &operator=(const Scalar &val) = default;
    Scalar &operator=(Scalar &&val) = default;

    // Scalar Operations
    Matrix operator+(const Matrix &mat) const noexcept;
    Matrix operator-(const Matrix &mat) const noexcept;
    Matrix operator*(const Matrix &mat) const noexcept;
    Matrix operator/(const Matrix &mat) const;

    // Making overloaded stream insertion and extraction operator as friend functions
    friend std::ostream &operator<<(std::ostream &os, const Scalar &val);

   private:
    // value of the scalar
    ll val;
};

// Overloaded stream insertion operator for the Scalar class
std::ostream &operator<<(std::ostream &os, const Scalar &val);

#endif  // _SCALAR_H_