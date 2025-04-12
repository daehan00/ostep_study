#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void) {
    char *fname = "file.txt";
    int fd;
    char buf[50];
    
    fd = open(fname,O_RDWR);

    if (fd < 0) {
        fprintf(stderr, "Open error for %s\n",fname);
        exit(1);
    }

    // 파일 읽기
    ssize_t len = read(fd, buf, 49);
    if (len >= 0) buf[len] = '\0';
    printf("READ:\n%s\n", buf);
    
    int rc = fork();
    if (rc < 0) {
        printf("Error occured call fork\n");
    } else if (rc == 0) {
        write(fd, "Child is Writting...\n", strlen("Child is Writting...\n"));
        printf("Child Writting\n");
    } else  {
        // int wc = wait(NULL);
        write(fd, "Parent is Writting...\n", strlen("Parent is Writting...\n"));
        printf("Parent Writting\n");
    }
    close(fd);
}
