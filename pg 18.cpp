#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 5
#define MAX_ITEMS 10 // Maximum number of items to be produced/consumed

int buffer[BUFFER_SIZE] = {0}; // Initialize the buffer to 0
sem_t empty, full;             // Semaphore variables

int produced_items = 0, consumed_items = 0; // Track the number of produced and consumed items

// Producer function
void* producer(void* arg) {
    while (produced_items < MAX_ITEMS) {
        sem_wait(&empty); // Wait for an empty slot in the buffer

        // Critical section: add item to buffer
        for (int i = 0; i < BUFFER_SIZE; ++i) {
            if (buffer[i] == 0) {  // Find an empty spot
                buffer[i] = produced_items + 1;  // Add the item
                printf("Produced: %d\n", buffer[i]);
                produced_items++;
                break;
            }
        }

        sem_post(&full); // Signal that there is an item in the buffer
        sleep(1);         // Sleep for a while (producer's "thinking" time)
    }
    return NULL;
}

// Consumer function
void* consumer(void* arg) {
    while (consumed_items < MAX_ITEMS) {
        sem_wait(&full); // Wait for a full slot in the buffer

        // Critical section: remove item from buffer
        for (int i = 0; i < BUFFER_SIZE; ++i) {
            if (buffer[i] != 0) { // Find an item to consume
                printf("Consumed: %d\n", buffer[i]);
                buffer[i] = 0;  // Remove the item from the buffer
                consumed_items++;
                break;
            }
        }

        sem_post(&empty); // Signal that there is an empty slot in the buffer
        sleep(2);         // Sleep for a while (consumer's "thinking" time)
    }
    return NULL;
}

int main() {
    pthread_t producer_thread, consumer_thread;

    // Initialize semaphores
    sem_init(&empty, 0, BUFFER_SIZE); // Initially, the buffer has empty slots
    sem_init(&full, 0, 0);            // Initially, the buffer has no items

    // Create producer and consumer threads
    pthread_create(&producer_thread, NULL, producer, NULL);
    pthread_create(&consumer_thread, NULL, consumer, NULL);

    // Wait for threads to finish
    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);

    // Destroy semaphores
    sem_destroy(&empty);
    sem_destroy(&full);

    return 0;
}

