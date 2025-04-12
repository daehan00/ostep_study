#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <assert.h>
#include <sys/wait.h>

int main(void) {
    int rc = fork();
    if (rc < 0) {
        printf("error\n");
        exit(1);
    } else if (rc == 0) {
        printf("Child process\n");
        // execl("/bin/ls", "ls", "-ㅣ", (char *)NULL);

        // char *args[] = {"ls", "-l", NULL};
        // execv("/bin/ls", args);

        // execlp("ls", "ls", "-l", (char *)NULL);

        // char *args[] = {"ls", "-l", NULL};
        // execvp("ls", args);

        // char *env[] = {"MYVAR=hello", NULL};
        // execle("/bin/ls", "ls", "-l", (char *)NULL, env);

        char *args[] = {"ls", "-l", NULL};
        char *env[] = {"MYVAR=hello", NULL};
        execve("/bin/ls", args, env);

        printf("This is NOT printing message\n");
    } else {
        wait(NULL);
        printf("Parent process\n");
    }
}
