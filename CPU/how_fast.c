#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

#define ITERATIONS 1000000   // 시스템 콜 반복 횟수
#define REPEATS 30           // 측정 반복 횟수

int main(void) {
    struct timeval start, end;
    
    for (int j = 0; j < REPEATS; j++) {
        gettimeofday(&start, NULL);

        for (int i = 0; i < ITERATIONS; i++) {
            read(0, NULL, 0);  // 시스템 콜 (0바이트 읽기)
        }

        gettimeofday(&end, NULL);

        double elapsed_usec = (end.tv_sec - start.tv_sec) * 1000000.0 +
                              (end.tv_usec - start.tv_usec);
        double avg_per_call = elapsed_usec / ITERATIONS;

        printf("[%2d회차] 총 시간: %.0f us | 평균 시간: %.3f us\n",
               j + 1, elapsed_usec, avg_per_call);
    }

    return 0;
}
