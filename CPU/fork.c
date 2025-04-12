#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

int main(void) {
    int rc = fork();
    if (rc < 0) {
        perror("fork");
        exit(1);
    } else if (rc == 0) {
        printf("hello %d\n", getpid());
    } else {
        int wc;
        do {
            wc = waitpid(rc, NULL, 0);
        } while (wc == -1 && errno == EINTR);  // 🔁 인터럽트 발생 시 재시도

        if (wc == -1) {
            perror("waitpid");
        } else {
            printf("this is %d, goodbye %d\n", getpid(), wc);  // 자식의 PID가 출력되어야 함
        }
    }
}
