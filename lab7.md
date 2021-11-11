# Virtual to Physical address translations in xv6 (Deadline: 19 Nov 2021 at 23:59 hrs)

-   NOTE: The assignment is same the Exercise 2 given at: <https://moss.cs.iit.edu/cs450/assign02-xv6-syscall.html>

-   In this assignment, you have to add a new system call named v2paddr. The
    `v2paddr()` system call should take a virtual address in the address space of
    the process calling the system call as an argument, and should return the
    corresponding physical address. If the virtual address passed is invalid
    (inside the calling processes’ address space), then it has to return -1. You
    may also want to look at the Hints section of Exercise 2 given in the link
    for help on getting started with the assignment. You may want to make the
    xv6 kernel print suitable messages on to the console so that you can verify
    the correctness of your implementation.

-   You have to create a user or application program named `test_v2paddr.c` that
    will call your newly created `v2paddr()` system call, edit the `makefile`
    appropriately to compile `test_v2paddr.c` and insert it into the filesystem of
    xv6 appropriately.

-   To evaluate the submission, the instructor will do the following:
    
        pull your changes 
        run the command make qemu-nox 
        In the command prompt of (booted) xv6, type test_v2paddr
        For grading purposes, the instructor will replace your test_v2paddr.c with different programs.

