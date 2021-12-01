#include "types.h"
#include "user.h"
#include "fcntl.h"
#include "syscall.h"

char buf[8192];
int stdout = 1;

int main(int argc, char *argv[]) {
    // START: test symlinks
    printf(stdout, "START: test symlinks!\n");

    int fda = open("a",  O_CREATE | O_RDWR);

    // Creating a
    printf(stdout, "Creating a!\n");
    if (fda < 0) {
        printf(stdout, "ERROR: Creating file 'a' failed!\n");
        exit();
    }

    // Linking b -> a
    printf(stdout, "Linking b -> a\n");
    if (symlink("a", "b") != 0) {
        printf(stdout, "ERROR: Linking b -> a failed!\n");
        exit();
    }

    // Writing to a
    printf(stdout, "Writing to a!\n");
    if (write(fda, "Hi", 2) != 2) {
        printf(stdout, "ERROR: Writing to file a failed!\n");
        exit();
    }

    // Reading from b
    int fdb = open("b", O_RDONLY);

    printf(stdout, "Opening b!\n");
    if (fdb < 0) {
        printf(stdout, "ERROR: Opening file 'b' failed!\n");
        exit();
    }

    printf(stdout, "Reading from b\n");
    if (read(fdb, buf, 2) != 2) {
        printf(stdout, "ERROR: Reading from file b failed!\n");
        exit();
    }

    close(fdb);

    // Removing a
    printf(stdout, "Removing a!\n");
    close(fda);
    if (unlink("a") < 0) {
        printf(stdout, "ERROR: Unlinking file a failed!\n");
        exit();
    }

    // Linking a -> b
    printf(stdout, "Linking a -> b\n");
    if (symlink("b", "a") != 0) {
        printf(stdout, "ERROR: Linking a -> b failed!\n");
        exit();
    }

    // Attempting to open b (cycle)
    printf(stdout, "Attempting to open b (cycle)!\n");
    if (open("b", O_RDONLY) != -1) {
        printf(stdout, "File b read successfully!\n");
        exit();
    }

    // Symlinking c to nonexistent file
    printf(stdout, "Symlinking c to nonexistent file!\n");
    if (symlink("xyz", "c") != 0) {
        printf(stdout, "ERROR: Linking c -> xyz failed!\n");
        exit();
    }

    // Creating symlink chain 1->2->3->4
    int fd4 = open("4",  O_CREATE | O_RDWR);
    if (fd4 < 0) {
        printf(stdout, "ERROR: Creating file '4' failed!\n");
        exit();
    }
    if (write(fd4, "Hi", 2) != 2) {
        printf(stdout, "ERROR: Writing to file 4 failed!\n");
        exit();
    }
    if (symlink("4", "3") != 0) {
        printf(stdout, "ERROR: Linking 3 -> 4 failed!\n");
        exit();
    }
    if (symlink("3", "2") != 0) {
        printf(stdout, "ERROR: Linking 2 -> 3 failed!\n");
        exit();
    }
    if (symlink("2", "1") != 0) {
        printf(stdout, "ERROR: Linking 1 -> 2 failed!\n");
        exit();
    }

    // Reading from 1
    int fd1 = open("1", O_RDONLY);

    printf(stdout, "Opening 1!\n");
    if (fd1 < 0) {
        printf(stdout, "ERROR: Opening file '1' failed!\n");
        exit();
    }

    printf(stdout, "Reading from 1!\n");
    if (read(fd1, buf, 2) != 2) {
        printf(stdout, "ERROR: Reading from file 1 failed!\n");
        exit();
    }

    close(fd4);
    close(fd1);

    printf(stdout, "SUCCESS: test symlinks!\n");

    exit();
}