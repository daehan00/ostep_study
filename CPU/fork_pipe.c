#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/wait.h>

int main(void) {
    int fd[2];
    pipe(fd);

    int rc1 = fork();
    if (rc1 < 0) {
        printf("error");
        exit(1);
    } else if (rc1 == 0) {
        close(fd[0]);
        dup2(fd[1], STDOUT_FILENO);
        close(fd[1]);
        execl("/bin/ls", "ls", "-l", (char *)NULL);
        exit(0);
    }

    int rc2 = fork();
    if (rc2 < 0) {
        printf("error");
        exit(1);
    } else if (rc2 == 0) {
        close(fd[1]);
        dup2(fd[0], STDIN_FILENO);
        close(fd[0]);
        char buffer[500];
        fgets(buffer, sizeof(buffer), stdin);
        printf("Read from child #2:\n");
        while (fgets(buffer, sizeof(buffer), stdin) != NULL) {
            printf("%s", buffer);
        }
        exit(0);
    }

    close(fd[0]);
    close(fd[1]);

    for (int i=0; i<2; i++) {
        int wc;
        do {
            wc = wait(NULL);
        } while (wc == -1 && errno == EINTR);
    }
    printf("process ended. This message print only once.\n");
}
