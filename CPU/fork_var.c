#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int
main(void) {
    int x = 100;
    int rc = fork();
    if (rc < 0) {
        printf("Error occured call fork\n");
    } else if (rc == 0) {
        x = 150;
        printf("Child process, x=%d\n", x);
    } else  {
        // x = 200;
        int wc = wait(NULL);
        printf("Parent process, x=%d\n", x);
    }
}