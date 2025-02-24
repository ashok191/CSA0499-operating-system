#include <stdio.h>
#include <pthread.h>

// Shared variables
int counter = 0;
pthread_mutex_t mutex;  // Mutex to protect the shared counter

// Function to be executed by threads
void *threadFunction(void *arg) {
    int i;
    for (i = 0; i < 1000000; ++i) {
        pthread_mutex_lock(&mutex);  // Lock the mutex before modifying the counter
        counter++;  // Modify the shared counter
        pthread_mutex_unlock(&mutex);  // Unlock the mutex after modifying the counter
    }
    return NULL;
}

int main() {
    // Initialize the mutex
    pthread_mutex_init(&mutex, NULL);

    pthread_t thread1, thread2;

    // Create two threads
    pthread_create(&thread1, NULL, threadFunction, NULL);
    pthread_create(&thread2, NULL, threadFunction, NULL);

    // Wait for the threads to finish
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    // Destroy the mutex
    pthread_mutex_destroy(&mutex);

    // Print the final value of the counter
    printf("Final counter value: %d\n", counter);

    return 0;
}

