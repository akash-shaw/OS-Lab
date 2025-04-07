#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define CAPACITY 5

int buffer[CAPACITY];
int in = 0, out = 0;

sem_t empty;
sem_t full; 
sem_t pmutex; 
sem_t cmutex;

void* producer(void* arg) {
    int item;
    while (1) {
        item = rand() % 100; 
        sem_wait(&empty);     
        sem_wait(&pmutex);  

        buffer[in] = item;
        printf("Produced: %d at %d\n", item, in);
        in = (in + 1) % CAPACITY;

        sem_post(&pmutex);   
        sem_post(&full);      

        sleep(1); 
    }
}

void* consumer(void* arg) {
    int item;
    while (1) {
        sem_wait(&full);    
        sem_wait(&cmutex); 

        item = buffer[out];
        printf("Consumed: %d from %d\n", item, out);
        out = (out + 1) % CAPACITY;

        sem_post(&cmutex);   
        sem_post(&empty);    

        sleep(2); 
    }
}

int main() {
    pthread_t prod_tid, cons_tid;

    sem_init(&empty, 0, CAPACITY);
    sem_init(&full, 0, 0);
    sem_init(&pmutex, 0, 1);
    sem_init(&cmutex, 0, 1);

    pthread_create(&prod_tid, NULL, producer, NULL);
    pthread_create(&cons_tid, NULL, consumer, NULL);

    pthread_join(prod_tid, NULL);
    pthread_join(cons_tid, NULL);

    sem_destroy(&empty);
    sem_destroy(&full);
    sem_destroy(&pmutex);
    sem_destroy(&cmutex);

    return 0;
}
