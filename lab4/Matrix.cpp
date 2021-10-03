#include "Matrix.h"

#include <sstream>

#include "Scalar.h"
#include "constants.h"
#include "exceptions.h"
#include "utils.h"

using ll = long long;

// Constructor
Matrix::Matrix(ll rows, ll columns)
    : rows{rows}, columns{columns} {
    // For a valid matrix, rows >= 1 and columns >= 1
    if (rows <= 0 || columns <= 0) {
        throw InvalidDimensionsException();
    }

    // Initializing the matrix with all 0's
    matrix.assign(rows, std::vector<ll>(columns, 0));
}

// Destructor
Matrix::~Matrix() noexcept {
}

// Getters
int Matrix::getRows() const noexcept {
    return this->rows;
}

int Matrix::getColumns() const noexcept {
    return this->columns;
}

std::vector<std::vector<ll>> Matrix::getMatrix() const noexcept {
    return this->matrix;
}

// Setters
void Matrix::setVal(ll i, ll j, ll val) {
    if (i < 0 || i >= this->rows || j < 0 || j >= this->columns) {
        throw OutOfBoundsException();
    }
    this->matrix[i][j] = val;
}

// Overloaded operators

// Matrix Operations

// Adds the matrix to the current matrix and returns the new matrix
Matrix Matrix::operator+(const Matrix &mat) const {
    // Matrix dimensions have to be exactly same for valid addition
    if (this->rows != mat.rows || this->columns != mat.columns) {
        throw InvalidDimensionsException();
    }

    Matrix result(this->rows, this->columns);

    for (ll i = 0; i < this->rows; ++i) {
        for (ll j = 0; j < this->columns; ++j) {
            result.matrix[i][j] = this->matrix[i][j] + mat.matrix[i][j];
        }
    }

    return result;
}

// Subtracts the matrix from the current matrix and returns the new matrix
Matrix Matrix::operator-(const Matrix &mat) const {
    // Matrix dimensions have to be exactly same for valid subtraction
    if (this->rows != mat.rows || this->columns != mat.columns) {
        throw InvalidDimensionsException();
    }

    Matrix result(this->rows, this->columns);

    for (ll i = 0; i < this->rows; ++i) {
        for (ll j = 0; j < this->columns; ++j) {
            result.matrix[i][j] = this->matrix[i][j] - mat.matrix[i][j];
        }
    }

    return result;
}

// Multiplies the matrix with the current matrix and returns the new matrix
Matrix Matrix::operator*(const Matrix &mat) const {
    // Matrices have to be of the form (nxp) and (pxm) for valid matrix multiplication
    if (this->columns != mat.rows) {
        throw InvalidDimensionsException();
    }

    // Resultant matrix will be of the form (nxm)
    Matrix result(this->rows, mat.columns);

    for (ll i = 0; i < this->rows; ++i) {
        for (ll j = 0; j < mat.columns; ++j) {
            for (ll k = 0; k < this->columns; ++k) {
                result.matrix[i][j] += this->matrix[i][k] * mat.matrix[k][j];
            }
        }
    }

    return result;
}

// Divides the matrix from the current matrix and returns the new matrix
// IMP: Unused function, just defined so as to match the template function for generality
Matrix Matrix::operator/(const Matrix &mat) const {
    // Matrix dimensions have to be exactly same for valid division
    if (this->rows != mat.rows || this->columns != mat.columns) {
        throw InvalidDimensionsException();
    }

    Matrix result(this->rows, this->columns);

    for (ll i = 0; i < this->rows; ++i) {
        for (ll j = 0; j < this->columns; ++j) {
            if (mat.matrix[i][j] == 0) throw DivideByZeroException();
            result.matrix[i][j] = this->matrix[i][j] / mat.matrix[i][j];
        }
    }

    return result;
}

// Function to get transpose of the matrix
Matrix Matrix::transpose() const noexcept {
    // Resultant matrix will have rows and columns swapped
    Matrix result(this->columns, this->rows);

    for (ll i = 0; i < this->rows; ++i) {
        for (ll j = 0; j < this->columns; ++j) {
            result.matrix[j][i] = this->matrix[i][j];
        }
    }

    return result;
}

// Function to get the remaining submatrix of the given matrix, provided the row (r) and the column (c) to exclude.
std::vector<std::vector<ll>> Matrix::getRemainingSubmatrix(const std::vector<std::vector<ll>> &mat, ll r, ll c) const {
    // Matrix needs to have at least two rows and two columns
    if (mat.size() <= 1 || mat[0].size() <= 1) {
        throw InvalidDimensionsException();
    }

    // n = #rows of the matrix, m = #columns of the matrix
    ll n = mat.size(), m = mat[0].size();

    // row and column number should be within the index bounds (0-based indexing)
    if (r < 0 || c < 0 || r >= n || c >= m) {
        throw OutOfBoundsException();
    }

    // Resultant matrix will be one dimension small in each row and column
    std::vector<std::vector<ll>> result(n - 1, std::vector<ll>(m - 1, 0));

    ll p = 0, q = 0;
    for (ll i = 0; i < n; ++i) {
        if (i == r) continue;  // if i = row to exclude

        for (ll j = 0; j < m; ++j) {
            if (j == c) continue;  // if j = column to exclude
            result[p][q++] = mat[i][j];
        }

        ++p;
        q = 0;
    }

    return result;
}

// (Helper) Function to get the determinant of the matrix
ll Matrix::determinant(const std::vector<std::vector<ll>> &mat, ll n) const {
    // Determinant of 1x1 matrix is the value itself
    if (n == 1) {
        return mat[0][0];
    }

    // result = final answer, i = row along which determinant is evaluated
    ll result = 0, i = 0, sign = 1;
    for (ll j = 0; j < n; ++j) {
        result += (sign * mat[i][j] * determinant(getRemainingSubmatrix(mat, i, j), n - 1));
        sign = -sign;
    }

    return result;
}

// Function to get the determinant of the matrix
Scalar Matrix::determinant() const {
    // Determinant can only be evaluated for square matrices
    if (this->rows != this->columns) {
        throw NonSquareMatrixException();
    }

    return Scalar(determinant(this->matrix, this->rows));
}

// Overloaded stream insertion operator for the Matrix class
std::ostream &operator<<(std::ostream &os, const Matrix &mat) {
    // Printing in the desired format as specified
    os << mat.rows << " " << mat.columns << std::endl;
    for (ll i = 0; i < mat.rows; ++i) {
        for (ll j = 0; j < mat.columns; ++j) {
            os << mat.matrix[i][j] << ',';
        }
        os << std::endl;
    }

    return os;
}

// Overloaded stream extraction operator for the Matrix class
std::istream &operator>>(std::istream &is, Matrix &mat) {
    std::string line = "";
    // Reading number of lines = number of rows
    for (ll i = 0; i < mat.rows; ++i) {
        std::getline(is, line);
        util::trim(line);
        // line should be comma separated matrix values, else it is invalid input
        if (!util::isUsefulLine(line) || !util::isValidLine(line)) {
            throw InvalidInputException();
        }

        std::stringstream ss(line);
        ll j = 0;  // To keep track of how many values are provided for each row
        std::string num = "";
        // Reading each matrix value in the line
        while (std::getline(ss, num, constants::MATRIX_VALUES_SEPARATOR)) {
            // if number of values provided are greater than number of columns, it is invalid input
            if (j >= mat.columns) {
                throw InvalidInputException();
            }

            ll val = std::stoll(num);
            mat.matrix[i][j++] = val;
        }

        // if number of values provided are less than number of columns, it is invalid input
        if (j != mat.columns) {
            throw InvalidInputException();
        }
    }

    return is;
}