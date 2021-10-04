#include "Scalar.h"

#include <sstream>

#include "Matrix.h"
#include "constants.h"
#include "exceptions.h"
#include "utils.h"

using ll = long long;

Scalar::Scalar(ll val) noexcept
    : val{val} {
}

// Destructor
Scalar::~Scalar() noexcept {
}

// Getters
int Scalar::getVal() const noexcept {
    return this->val;
}

// Overloaded operators

// Scalar Operations

// Adds the scalar value to all the values in the matrix and returns the new matrix
Matrix Scalar::operator+(const Matrix &mat) const noexcept {
    ll n = mat.getRows(), m = mat.getColumns();
    Matrix result(n, m);

    for (ll i = 0; i < n; ++i) {
        for (ll j = 0; j < m; ++j) {
            result.setVal(i, j, mat.getMatrix()[i][j] + val);
        }
    }

    return result;
}

// Subtracts the scalar value from all the values in the matrix and returns the new matrix
Matrix Scalar::operator-(const Matrix &mat) const noexcept {
    ll n = mat.getRows(), m = mat.getColumns();
    Matrix result(n, m);

    for (ll i = 0; i < n; ++i) {
        for (ll j = 0; j < m; ++j) {
            result.setVal(i, j, mat.getMatrix()[i][j] - val);
        }
    }

    return result;
}

// Multiplies the scalar value with all the values in the matrix and returns the new matrix
Matrix Scalar::operator*(const Matrix &mat) const noexcept {
    ll n = mat.getRows(), m = mat.getColumns();
    Matrix result(n, m);

    for (ll i = 0; i < n; ++i) {
        for (ll j = 0; j < m; ++j) {
            result.setVal(i, j, mat.getMatrix()[i][j] * val);
        }
    }

    return result;
}

// Divides the scalar value with all the values in the matrix and returns the new matrix
Matrix Scalar::operator/(const Matrix &mat) const {
    // Division by zero is not allowed
    if (val == 0) {
        throw DivideByZeroException();
    }

    ll n = mat.getRows(), m = mat.getColumns();
    Matrix result(n, m);

    for (ll i = 0; i < n; ++i) {
        for (ll j = 0; j < m; ++j) {
            result.setVal(i, j, mat.getMatrix()[i][j] / val);
        }
    }

    return result;
}

// Overloaded stream insertion operator for the Scalar class
std::ostream &operator<<(std::ostream &os, const Scalar &val) {
    // Printing in the desired format as specified
    os << val.val;

    return os;
}