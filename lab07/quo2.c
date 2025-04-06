#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

int readercount = 0;
sem_t mutex;   // to protect readercount
sem_t write;   // to allow only one writer at a time or block writers when readers are active

void* reader(void* arg) {
    int id = *((int*)arg);
    while (1) {
        // Entry Section
        sem_wait(&mutex);
        readercount++;
        if (readercount == 1) {
            sem_wait(&write);  // First reader locks write
        }
        sem_post(&mutex);

        // Critical Section (Reading)
        printf("Reader %d is reading\n", id);
        sleep(1);

        // Exit Section
        sem_wait(&mutex);
        readercount--;
        if (readercount == 0) {
            sem_post(&write);  // Last reader unlocks write
        }
        sem_post(&mutex);

        // Remainder Section
        sleep(2); // simulate other processing
    }
}

void* writer(void* arg) {
    int id = *((int*)arg);
    while (1) {
        // Entry Section
        sem_wait(&write);

        // Critical Section (Writing)
        printf("Writer %d is writing\n", id);
        sleep(2);

        // Exit Section
        sem_post(&write);

        // Remainder Section
        sleep(3); // simulate other processing
    }
}

int main() {
    pthread_t r1, r2, w1;
    int r1_id = 1, r2_id = 2, w1_id = 1;

    // Initialize semaphores
    sem_init(&mutex, 0, 1);
    sem_init(&write, 0, 1);

    // Create reader and writer threads
    pthread_create(&r1, NULL, reader, &r1_id);
    pthread_create(&r2, NULL, reader, &r2_id);
    pthread_create(&w1, NULL, writer, &w1_id);

    // Join threads (runs indefinitely)
    pthread_join(r1, NULL);
    pthread_join(r2, NULL);
    pthread_join(w1, NULL);

    // Destroy semaphores (not reached, but good practice)
    sem_destroy(&mutex);
    sem_destroy(&write);

    return 0;
}
