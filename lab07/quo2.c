#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

int readercount = 0;
sem_t mutex;   
sem_t wrt; 

void* reader(void* arg) {
    int id = *((int*)arg);
    while (1) {
        sem_wait(&mutex);
        readercount++;
        if (readercount == 1) {
            sem_wait(&wrt); 
        }
        sem_post(&mutex);

        printf("Reader %d is reading\n", id);
        sleep(1);

        sem_wait(&mutex);
        readercount--;
        if (readercount == 0) {
            sem_post(&wrt); 
        }
        sem_post(&mutex);

        sleep(2);
    }
}

void* writer(void* arg) {
    int id = *((int*)arg);
    while (1) {
        sem_wait(&wrt);

        printf("Writer %d is writing\n", id);
        sleep(2);

        sem_post(&wrt);
        sleep(3); 
    }
}

int main() {
    pthread_t r1, r2, w1;
    int r1_id = 1, r2_id = 2, w1_id = 1;

    sem_init(&mutex, 0, 1);
    sem_init(&wrt, 0, 1);

    pthread_create(&r1, NULL, reader, &r1_id);
    pthread_create(&r2, NULL, reader, &r2_id);
    pthread_create(&w1, NULL, writer, &w1_id);

    pthread_join(r1, NULL);
    pthread_join(r2, NULL);
    pthread_join(w1, NULL);

    sem_destroy(&mutex);
    sem_destroy(&wrt);

    return 0;
}
