# Lab 4 (Deadline: 07-Oct 2021 @ 23:59 hrs)

In this lab, you will organize the code or application developed in Lab 3, write
test cases, and setup a build system for it.


## Instructions

1.  Commit your progress often.

2.  Do not commit temporary files and folders into the repo. (Do a `make clean`
    before you commit your changes into the repo)

3.  The `makefile` should be part of the repo. Avoid using absolute paths in
    the `makefile` because that will affect portability (I will not be able to
    pull your submission and run `make` on it).

## Question

1.  [0 marks] Refine the code you submitted in lab3 for this lab if necessary.
    Your code should use features such as abstraction and encapsulation
    (supported in C++).
    -   Use Standard Template Libraries (if required)

    -   Think of how many new "Types" you can create (using classes) in your code,
        and the relationship between these custom "Types". This will help you get
        started with designing your code.

2.  [10 marks] Write at least four test cases for your code. You have to create a
    file with the test input and another file with expected output. The input and
    output formats were described in lab3. In addition to the input and output
    formats, you will need a mechanism to compare the output produced with the
    expected output. You can the command `diff` to do the comparison.

3.  [20 marks] Create separate folders and organize your code (in the
    following manner):
    -   `src/` - This folder should contain all the source files (.cpp or .cc)

    -   `include/` - T=his folder should contain all the header files (.h or .hpp)

    -   `lib/` - This folder should contain all the libraries against which you code
        will link. This should also contain the libraries that you will generate
        from your code (as part of this lab).

    -   `bin/` - The final executable should be in this folder

    -   `tests/` - This folder should contain all the input files and expected output
        files for all the test cases that you have written to test your code.

    -   `build/` - This is optional. You can have all the temporarily files that are
        created when compiling your code (such as object files) in this folder.

4.  [40 marks] Setup a build system for your application using the make utility
    with the following targets. Use Makefile variables, text-substitutions,
    pattern-matching, implicit rules, etc as much as possible. **Do not embed
    absolute paths in your makefile.** The folders have to be created as part of
    the makefile (`make` or `make build`) itself. Do not expect that the folder
    structure mention above is created beforehand (or is to be manually created).
    -   `build` - compile your code to produce an executable (name of the executable
        does not matter because we will never call the executable directly from the
        terminal) in the appropriate folder (`bin/` in our case). This should be
        the default target (just issuing \`make\` without any targets should build
        the executable).

    -   `libs` - create two libraries: (i) a static library that contains only the
        scalar operations in it, and (ii) a dynamically linked library that
        contains only the matrix operations in the appropriate folder (`lib/` in
        our case).

    -   `prepare` - takes input from user on input and output file names (paths).
        Typically this is followed by the target that runs the application.

    -   `run` - runs the executable created using the build target. This target is
        expected to follow the `prepare` target. In case it is not preceded by the
        `prepare` target, it assumes that the input and output files are `run.in`
        and `run.out` (which are located in the present working directory).

    -   `tests` - runs all test cases on your application

    -   `test1` / `test2` / `test3` / ... - runs only test case 1/2/3/... on your application

    -   `clean` - deletes the executable, the temporary files, and any files that
        are generated such as execution logs, output files etc. After running `make clean`,
        the folder should have only the makefile, source files, header
        files, and the test cases (including their correspnding expected outputs).
        Should also delete the containing folders such as `build`.
