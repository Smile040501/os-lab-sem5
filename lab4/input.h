#ifndef _INPUT_H_
#define _INPUT_H_

#include <string>
#include <vector>

#include "Matrix.h"
#include "Scalar.h"

using ll = long long;

namespace input {
// Function that takes input arguments from command line, parses them and stores them in an array of char
void parseArgs(int argc, char **argv, std::vector<char> &args);

// Function to handle the input which reads an input file as per the input format
void handleInput(std::vector<Matrix> &matrices, std::vector<Scalar> &scalars, std::string &order);

}  // namespace input

#endif  // _INPUT_H_