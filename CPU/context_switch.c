#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <sched.h>
#include <sys/wait.h>
#include <errno.h>

#define N 10000

void set_cpu_affinity() { // 리눅스 환경에서 가능
    cpu_set_t set;
    CPU_ZERO(&set);
    if (sched_setaffinity(0, sizeof(set), &set) != 0) {
        perror("sched_setaffinity");
        exit(1);
    }
}

int main(void) {
    int pipe1[2], pipe2[2];
    pipe(pipe1); // A >> B
    pipe(pipe2); // B >> A

    set_cpu_affinity(); // 리눅스 환경에서 가능
    int pid = fork();
    if (pid < 0) {
        perror("fork");
        exit(1);
    } else if (pid == 0) {
        set_cpu_affinity(); // 리눅스 환경에서 가능

        for (int i=0; i<N; i++) {
            char buf;
            read(pipe1[0], &buf, 1);
            write(pipe2[1], "x", 1);
        }
        exit(0);
    } else {
        struct timeval start, end;

        gettimeofday(&start, NULL);
        for (int i = 0; i < N; i++) {
            write(pipe1[1], "x", 1);  // A → B
            char buf;
            read(pipe2[0], &buf, 1);  // B → A
        }
        gettimeofday(&end, NULL);

        wait(NULL);

        double elapsed_usec = (end.tv_sec - start.tv_sec) * 1000000.0 + (end.tv_usec - start.tv_usec);
        double avg_context_switch_time = elapsed_usec / (2 * N);  // 왕복당 문맥 교환 2번

        printf("총 시간: %.0f us\n", elapsed_usec);
        printf("문맥 교환 1회 평균 시간: %.3f us\n", avg_context_switch_time);
    }
}
