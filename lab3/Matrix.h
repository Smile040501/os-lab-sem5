#ifndef _MATRIX_H_
#define _MATRIX_H_

#include <iostream>
#include <vector>

using ll = long long;

// Matrix class to represent a matrix
class Matrix {
   public:
    // Constructor
    Matrix(ll rows, ll columns);

    // Destructor
    ~Matrix() noexcept;

    // Default Copy Constructor
    Matrix(const Matrix &mat) = default;

    // Default Move Constructor
    Matrix(Matrix &&mat) = default;

    // Getters
    int getRows() const noexcept;
    int getColumns() const noexcept;
    std::vector<std::vector<ll>> getMatrix() const noexcept;

    // Overloaded operators
    // Default overloaded assignment operator
    Matrix &operator=(const Matrix &mat) = default;
    Matrix &operator=(Matrix &&mat) = default;

    // Scalar Operations
    Matrix operator+(ll val) const noexcept;
    Matrix operator-(ll val) const noexcept;
    Matrix operator*(ll val) const noexcept;
    Matrix operator/(ll val) const;

    // Matrix Operations
    Matrix operator+(const Matrix &mat) const;
    Matrix operator-(const Matrix &mat) const;
    Matrix operator*(const Matrix &mat) const;
    Matrix operator/(const Matrix &mat) const;

    // Function to get transpose of the matrix
    Matrix transpose() const noexcept;

    // Function to get the determinant of the matrix
    ll determinant() const;

    // Making overloaded stream insertion and extraction operator as friend functions
    friend std::ostream &operator<<(std::ostream &os, const Matrix &mat);
    friend std::istream &operator>>(std::istream &is, Matrix &mat);

   private:
    // number of rows and columns of the matrix
    ll rows, columns;

    // matrix represented as a 2D vector/array
    std::vector<std::vector<ll>> matrix;

    // Function to get the remaining submatrix of the given matrix, provided the row (r) and the column (c) to exclude.
    std::vector<std::vector<ll>> getRemainingSubmatrix(const std::vector<std::vector<ll>> &mat, ll r, ll c) const;

    // (Helper) Function to get the determinant of the matrix
    ll determinant(const std::vector<std::vector<ll>> &mat, ll n) const;
};

// Overloaded stream insertion operator for the Matrix class
std::ostream &operator<<(std::ostream &os, const Matrix &mat);

// Overloaded stream extraction operator for the Matrix class
std::istream &operator>>(std::istream &is, Matrix &mat);

#endif  // _MATRIX_H_