#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/wait.h>

int main(void) {
    int rc;
    rc = fork();

    if (rc < 0) {
        printf("error\n");
        exit(1);
    } else if (rc == 0) {
        printf("close stdout\n");
        close(STDOUT_FILENO);
        printf("this should not print out\n");
    } else {
        int wc;
        do {
            wc = waitpid(rc, NULL, 0);
        } while (wc == -1 && errno == EINTR);

        printf("printing something after close stdout\n");
    }
}
