#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

sem_t mutex, writeBlock;
int data = 0, readersCount = 0;

void *reader(void *arg) {
    int i = 0;
    while (i < 10) {
        sem_wait(&mutex);
        readersCount++;
        if (readersCount == 1) {
            sem_wait(&writeBlock);
        }
        sem_post(&mutex);
        
        // Reading operation
        printf("Reader reads data: %d\n", data);
        
        sem_wait(&mutex);
        readersCount--;
        if (readersCount == 0) {
            sem_post(&writeBlock);
        }
        sem_post(&mutex);
        
        i++;
    }
    return NULL;
}

void *writer(void *arg) {
    int i = 0;
    while (i < 10) {
        sem_wait(&writeBlock);
        
        // Writing operation
        data++;
        printf("Writer writes data: %d\n", data);
        
        sem_post(&writeBlock);
        i++;
    }
    return NULL;
}

int main() {
    pthread_t readers[5], writers[2];  // Create 5 reader threads and 2 writer threads
    
    sem_init(&mutex, 0, 1);
    sem_init(&writeBlock, 0, 1);

    // Create reader threads
    for (int i = 0; i < 5; i++) {
        pthread_create(&readers[i], NULL, reader, NULL);
    }

    // Create writer threads
    for (int i = 0; i < 2; i++) {
        pthread_create(&writers[i], NULL, writer, NULL);
    }

    // Join reader threads
    for (int i = 0; i < 5; i++) {
        pthread_join(readers[i], NULL);
    }

    // Join writer threads
    for (int i = 0; i < 2; i++) {
        pthread_join(writers[i], NULL);
    }

    sem_destroy(&mutex);
    sem_destroy(&writeBlock);

    return 0;
}

