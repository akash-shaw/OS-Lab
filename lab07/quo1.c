#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define CAPACITY 5

int buffer[CAPACITY];
int in = 0, out = 0;

sem_t empty;   // Counts empty slots
sem_t full;    // Counts filled slots
sem_t pmutex;  // Mutex for producer
sem_t cmutex;  // Mutex for consumer

void* producer(void* arg) {
    int item;
    while (1) {
        item = rand() % 100;  // Produce an item
        sem_wait(&empty);     // Decrease empty count
        sem_wait(&pmutex);    // Enter critical section for producer

        buffer[in] = item;
        printf("Produced: %d at %d\n", item, in);
        in = (in + 1) % CAPACITY;

        sem_post(&pmutex);    // Leave critical section for producer
        sem_post(&full);      // Increase full count

        sleep(1); // Simulate other processing
    }
}

void* consumer(void* arg) {
    int item;
    while (1) {
        sem_wait(&full);      // Decrease full count
        sem_wait(&cmutex);    // Enter critical section for consumer

        item = buffer[out];
        printf("Consumed: %d from %d\n", item, out);
        out = (out + 1) % CAPACITY;

        sem_post(&cmutex);    // Leave critical section for consumer
        sem_post(&empty);     // Increase empty count

        sleep(2); // Simulate consumption delay
    }
}

int main() {
    pthread_t prod_tid, cons_tid;

    // Initialize semaphores
    sem_init(&empty, 0, CAPACITY);
    sem_init(&full, 0, 0);
    sem_init(&pmutex, 0, 1);
    sem_init(&cmutex, 0, 1);

    // Create producer and consumer threads
    pthread_create(&prod_tid, NULL, producer, NULL);
    pthread_create(&cons_tid, NULL, consumer, NULL);

    // Join threads (will run forever)
    pthread_join(prod_tid, NULL);
    pthread_join(cons_tid, NULL);

    // Destroy semaphores (unreachable, but good practice)
    sem_destroy(&empty);
    sem_destroy(&full);
    sem_destroy(&pmutex);
    sem_destroy(&cmutex);

    return 0;
}
