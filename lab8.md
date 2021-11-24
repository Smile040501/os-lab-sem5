# Symbolic links in xv6 (Deadline: 01-Dec 2021 @ 23:59 hrs)

-   NOTE: The assignment is same as the second assignment given [here](https://pdos.csail.mit.edu/6.828/2019/labs/fs.html).

-   In this assignment, you have to add support for symbolic links to xv6. This
    is achieved by adding a new system call named `symlink(char *target, char
        *orig)`. The `symlink()` system call takes as argument two file paths
    (`target` and `orig`). The behavior of `symlink()` should be similar to that
    of the corresponding one in Linux (you can check the Linux manpages `man
        symlink` for more details). Hints for implementation is given in the
    original link.

-   You have to create an application named `test_symlink.c` that will call your
    newly created `symlink()` system call to test various possible scenarios.
    For a list of scenarios, see the output of the symlinktest command shown in
    the original link. Edit the `makefile` appropriately to compile
    `test_symlink.c` and insert it into the filesystem of xv6 appropriately.

-   To evaluate the submission, the instructor will do the following:
    
        pull your changes 
        run the command make qemu-nox 
        In the command prompt of (booted) xv6, type test_symlink
        For grading purposes, the instructor will replace your test_symlink.c with different programs.

