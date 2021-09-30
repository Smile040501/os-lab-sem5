#ifndef _OUTPUT_H_
#define _OUTPUT_H_

#include <string>
#include <vector>

#include "Matrix.h"

using ll = long long;

namespace output {
// Function to check if the given (index + offset) lies within index range of container
template <typename T>
void assertIndexBounds(const T &container, ll index, ll offset = 0);

// Function that evaluates the result of (val1 op val2) and stores it in val3
template <typename T1, typename T2, typename T3>
void evaluate(T1 &val1, T2 &val2, char option, T3 &val3);

// Function that performs operations in the order in which command line arguments are specified
void performOperations(const std::vector<char> &args, const std::vector<Matrix> &matrices, const std::vector<ll> &scalars, const std::string &order);

}  // namespace output

#endif  // _OUTPUT_H_