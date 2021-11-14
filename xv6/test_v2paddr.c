#include "types.h"
#include "user.h"
#include "syscall.h"
#include "memlayout.h"  // For using KERNBASE macro

// Function that takes a virtual address as argument and calls v2paddr() syscall to obtain the corresponding physical address if it exists
void getResults(addr_t *va) {
    addr_t pa;  // Physicall address to store the final answer
    printf(1, "Trying to convert Virtual Address: 0x%x\n", va);
    int status = v2paddr(&pa, va);
    if(status == 0) {   // Success
        printf(1, "Physical Address Obtained: 0x%x\n", pa);
    }
    printf(1, "\n");
}

int thirdTest = 99999;  // A test global variable

int main(int argc, char *argv[]) {

    // First Test
    int firstTest = 0;  // A test local variable
    addr_t* va = (addr_t*)(&firstTest);
    getResults(va);

    // Second Test
    addr_t* secondTest = (void*)(KERNBASE + 0x555); // A test in the Kernel space
    va = secondTest;
    getResults(va);

    // Third Test
    va = (addr_t*)(&thirdTest);
    getResults(va);

    exit();
}