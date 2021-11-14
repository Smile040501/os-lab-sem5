#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

int sys_fork(void) {
    return fork();
}

int sys_exit(void) {
    exit();
    return 0;  // not reached
}

int sys_wait(void) {
    return wait();
}

int sys_kill(void) {
    int pid;

    if (argint(0, &pid) < 0)
        return -1;
    return kill(pid);
}

int sys_getpid(void) {
    return myproc()->pid;
}

int sys_sbrk(void) {
    int addr;
    int n;

    if (argint(0, &n) < 0)
        return -1;
    addr = myproc()->sz;
    if (growproc(n) < 0)
        return -1;
    return addr;
}

int sys_sleep(void) {
    int n;
    uint ticks0;

    if (argint(0, &n) < 0)
        return -1;
    acquire(&tickslock);
    ticks0 = ticks;
    while (ticks - ticks0 < n) {
        if (myproc()->killed) {
            release(&tickslock);
            return -1;
        }
        sleep(&ticks, &tickslock);
    }
    release(&tickslock);
    return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int sys_uptime(void) {
    uint xticks;

    acquire(&tickslock);
    xticks = ticks;
    release(&tickslock);
    return xticks;
}

// Returns the number of times the referenced system call was invoked by the calling process
// Takes a valid system call number (listed in file `syscall.h`) as an argument
int sys_getcount(void) {
    int syscall_num;
    // Getting the syscall argument
    if (argint(0, &syscall_num) < 0) {
        return -1;
    }
    return myproc()->countSyscalls[syscall_num - 1];
}

// System call to convert a virtual address to physical address
/*
    Takes two input arguments
        paddr - an unsigned integer pointer to store the final answer
        vaddr - an unsigned integer pointer which is the virtual address to convert
*/
// Returns -1 if input vaddr is invalid or there is any fault in page table walk and vaddr should be accessible in user mode
int sys_v2paddr(void) {
    addr_t *paddr, *vaddr;
    int paddr_num = 0, vaddr_num = 1;   // The order in which arguments are passed
    if(argptr(paddr_num, (void*) &paddr, sizeof(*paddr)) < 0) {
        cprintf("Invalid physical address pointer received to store to.\n");
        return -1;  // If the physical address pointer (where user wants to store the final answer) don't lie withing the process address space
    }

    if(argptr(vaddr_num, (void*) &vaddr, sizeof(*vaddr)) < 0) {
        cprintf("Invalid virtual address pointer received to be read.\n");
        return -1;  // If the virtual address pointer don't lie withing the process address space
    }

    struct proc *currProcess = myproc();  // the current process which called this system call

    pde_t *pgdir = currProcess->pgdir;  // The page directory of the process
    pde_t *pde = &pgdir[PDX(vaddr)];    // Getting the page directory from the va, as done in vm.c

    if(!(*pde & PTE_P)) {
        cprintf("Page directory entry not present.\n");
        return -1;  // If page directory entry is not present or can't be accessed in user mode
    }

    if(!(*pde & PTE_U)) {
        cprintf("Page directory entry can't be accessed in user mode.\n");
        return -1;  // If page directory entry is not present or can't be accessed in user mode
    }

    pde_t *pgtab = (pte_t *)P2V(PTE_ADDR(*pde));  // The page table obtained
    pde_t *pte = &pgtab[PTX(vaddr)];              // The page table entry obtained from the va, as done in vm.c

    if(!(*pte & PTE_P)) {
        cprintf("Page table entry not present.\n");
        return -1;  // If page table entry is not present or can't be accessed in user mode
    }

    if(!(*pte & PTE_U)) {
        cprintf("Page table entry can't be accessed in user mode.\n");
        return -1;  // If page table entry is not present or can't be accessed in user mode
    }

    // Concatencating last 12 bits of vaddr to the first 20 bits of the pte
    *paddr = PTE_ADDR(*pte) | PTE_FLAGS(vaddr);

    cprintf("Virtual address converted to physical address successfully.\n");
    return 0;   // Indicated everything went well
}