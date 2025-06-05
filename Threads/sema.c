#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define BUFF_SIZE 100

int loops = 500;

int buffer[BUFF_SIZE];
int counter = 0;
int use = 0;

sem_t empty, fill, mutex;

void put(int i) {
    buffer[counter] = i;
    counter = (counter + 1) % BUFF_SIZE;
}

int get() {
    int tmp = buffer[use];
    use = (use + 1) % BUFF_SIZE;
    return tmp;
}

void* producer(void *arg) {
    printf("%s: begin\n", (char *) arg);
    int i;
    for (i=0; i<loops; i++) {
        sem_wait(&empty);

        sem_wait(&mutex);
        put(i);
        sem_post(&mutex);
        
        sem_post(&fill);
    }
    return 0;
}

void* consumer(void *arg) {
    printf("%s: begin\n", (char *) arg);
    int i;
    for (i=0; i<loops; i++) {
        sem_wait(&fill);

        sem_wait(&mutex);
        int tmp = get();
        sem_post(&mutex);
        
        printf("%d\n", tmp);
        sem_post(&empty);
    }
    return 0;
}

int main(int arg, char **args) {
    pthread_t p, c;

    sem_init(&empty, 0, BUFF_SIZE);
    sem_init(&fill, 0, 0);
    sem_init(&mutex, 0, 1);

    pthread_create(&p, NULL, producer, "producer");
    pthread_create(&c, NULL, consumer, "consumer");

    pthread_join(p, NULL);
    pthread_join(c, NULL);

    sem_destroy(&empty);
    sem_destroy(&fill);
    sem_destroy(&mutex);

    printf("end all\n");
    return 0;
}
