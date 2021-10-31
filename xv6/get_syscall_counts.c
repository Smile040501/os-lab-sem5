#include "types.h"
#include "user.h"
#include "syscall.h"

int main(int argc, char *argv[]) {
    printf(1, "Initial fork count %d\n", getcount(SYS_fork));
    sleep(50);

    if (fork() == 0) {
        printf(1, "Child fork count %d\n", getcount(SYS_fork));
        printf(1, "Child write count %d\n", getcount(SYS_write));
        printf(1, "Child process id:", getpid());
    } else {
        wait();
        printf(1, "Parent fork count %d\n", getcount(SYS_fork));
        printf(1, "Parent write count %d\n", getcount(SYS_write));
        printf(1, "Parent process id:", getpid());
    }
    printf(1, "wait count %d\n", getcount(SYS_wait));

    printf(1, "exit count %d\n", getcount(SYS_exit));
    printf(1, "pipe count %d\n", getcount(SYS_pipe));
    printf(1, "read count %d\n", getcount(SYS_read));
    printf(1, "kill count %d\n", getcount(SYS_kill));
    printf(1, "exec count %d\n", getcount(SYS_exec));
    printf(1, "fstat count %d\n", getcount(SYS_fstat));
    printf(1, "chdir count %d\n", getcount(SYS_chdir));
    printf(1, "dup count %d\n", getcount(SYS_dup));
    printf(1, "getpid count %d\n", getcount(SYS_getpid));
    printf(1, "sbrk count %d\n", getcount(SYS_sbrk));
    printf(1, "sleep count %d\n", getcount(SYS_sleep));
    printf(1, "uptime count %d\n", getcount(SYS_uptime));
    printf(1, "open count %d\n", getcount(SYS_open));
    printf(1, "write count %d\n", getcount(SYS_write));
    printf(1, "mknod count %d\n", getcount(SYS_mknod));
    printf(1, "unlink count %d\n", getcount(SYS_unlink));
    printf(1, "link count %d\n", getcount(SYS_link));
    printf(1, "mkdir count %d\n", getcount(SYS_mkdir));
    printf(1, "close count %d\n", getcount(SYS_close));
    printf(1, "getcount count %d\n", getcount(SYS_getcount));

    exit();
}