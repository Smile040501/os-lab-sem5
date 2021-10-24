# Adding a new system call in xv6 (Deadline: 31-Oct 2021 @ 23:59 hrs)

-   NOTE: The assignment is same the Exercise 1 given at: <https://moss.cs.iit.edu/cs450/assign02-xv6-syscall.html>

-   In this assignment, you have to add a new system call named `getcount`.

-   The `getcount()` system call should take a valid system call number (listed in
    the file `syscall.h`) as an argument, and should return the number of times the
    referenced system call was invoked by the calling process. Look at the link
    given above for a sample input and its corresponding output. You may also want
    to look at the Hints section of Exercise 1 given in the link.

-   You should write your own test program `get_syscall_counts.c` (a user program
    along similar lines given in the link). Edit the `Makefile` appropriately so
    that your user program is compiled and bundled into the xv6 image. (The
    instructions given in the link on editing the `Makefile` will not work in your
    case).
    
-   Modify the code in the `xv6/` folder of the repo and commit the changes.
    Push the changes to bitbucket.org before the deadline. 

