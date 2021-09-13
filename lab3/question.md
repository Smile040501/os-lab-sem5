# Lab 3: Matrix Operations in C++ (deadline: 19-Sep 2021 23:59 hrs)

## Submission instructions

1.  All the source files and header files have to be present inside the
    folder lab3

2.  The instructor/TA will pull the repo, and issue to the following
    commands to build, run, and grade your submission. Therefore, make
    sure that your submission is in order. `test.in` has all the
    matrices that will be given as input, and `test.out` should have
    all the matrices that are output at the end of the execution. The
    command-line argument to indicate any operation listed in the
    question below.

``` bash
    $ cd lab3
    $ g++ *.cpp -o lab3
    $ ./lab3 -a < test.in > test.out
```


## Format of matrix (input and output)

The input and output files are considered to be legal if it follows
the following rules:

1.  A line that starts with # is a comment. The character '#' should be
    the first character in the line, and a comment has to be a line by
    itself.

2.  A single value in a line is a scalar.

3.  Two values separated by a <space> in a line indicates the
    dimensions of the matrix. Such a line should be followed by the
    content/elements of the matrix.

4.  Each row of the matrix is in one line. Therefore, a M &times; N
    matrix will span over M+1 lines: one line for the dimensions and
    then one line for each of the M rows. The elements on each row are
    separated by comma.

5.  If there are more than one matrix in a file, then the matrices
    are concatenated (or appended) one after the other.

6.  Empty lines (and lines with only whitespaces) are ignored.

7.  Two sample files (sample1.in and sample2.in) illustrates the format
    better.


## Question

Write a C++ program to do the following:

1.  *[5 marks]* Read an input file that contains one (or more) matrices (given
    in the format above).  Note that you have to infer the number of
    matrices given as input from the input file and there is no
    explicit line in the file that indicates the same. The operation
    to perform on the inputs is taken as an command line argument.

2.  *[20 marks]* Perform the following functions. Note that you should
    use object-oriented programming constructs and principles such as
    classes, inheritance, function and operator overloading, etc
    **where applicable**. You can use
    [Getopt](https://www.gnu.org/savannah-checkouts/gnu/libc/manual/html_node/Getopt.html)
    to parse command line arguments. An example that uses getopt() is
    available
    [here](https://www.gnu.org/savannah-checkouts/gnu/libc/manual/html_node/Example-of-Getopt.html)
    **The operations should be performed in the order in which command
    line arguments are specified.**
    
    -   Scalar Operations
        -   addition (add a scalar value to all elements of a matrix)
            [COMMAND-LINE OPTION: -a]
        
        -   subtraction (subtract a scalar value to all elements of a
            matrix) [COMMAND-LINE OPTION: -s]
        
        -   multiplication (multiply all elements of a matrix with a
            scalar) [COMMAND-LINE OPTION: -m]
        
        -   division (divide all elements of a matrix with a scalar)
            [COMMAND-LINE OPTION: -d]
    
    -   Matrix Operations
        -   add two matrices [COMMAND-LINE OPTION: -a]
        
        -   subtract one matrix from the other matrix [COMMAND-LINE
            OPTION: -s]
        
        -   multiply two matrices [COMMAND-LINE OPTION: -m]
        
        -   transpose a matrix [COMMAND-LINE OPTION: -t]
        
        -   compute the determinant of a matrix [COMMAND-LINE OPTION:
            -x]

3.  *[5 marks]* Write the resultant matrix (or scalar value) in the
    format mentioned above. You may create other output files such
    as log files, temp files, etc as you deem fit in the same
    directory. However, the output should not be cluttered with
    error and debug prints.

4.  *[10 marks]* Spread the code across multiple files. Follow [this](https://www.youtube.com/watch?v=nbd7o8iKh9Q)
    video to help you do this.

5.  *[10 marks]* Implement a logging mechanism such that debug
    prints (or messages) are directed to a separate log file. Note
    that the log messages should not clutter the output. There are
    several simple loggers available on the internet such as [this](https://cppcodetips.wordpress.com/2014/01/02/a-simple-logger-class-in-c/),
    [this](https://www.drdobbs.com/cpp/logging-in-c/201804215), or [this](https://bitbucket.org/volkanozyilmaz/logcpp/src/master/main.cpp). NOTE: there are more powerful loggers but using
    them will not satisfy the submission instructions.

6.  *[10 marks]* Handle errors gracefully. The output should
    continue to be in the format mentioned above even in case of an
    error. It is fine to not print any output messages if the error
    is logged in a log file. Follow [this FAQ](https://isocpp.org/wiki/faq/exceptions) to help you achieve
    this. Pay special attention to the fifth question.

