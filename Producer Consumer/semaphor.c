#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 5 // Define the size of the buffer
#define NUM_OPERATIONS 10 // Define the number of produce-consume operations

int buffer[BUFFER_SIZE]; // Shared buffer
int in = 0; // Index for producer
int out = 0; // Index for consumer

// Semaphores
sem_t empty; // Counts empty slots in the buffer
sem_t full;  // Counts full slots in the buffer
pthread_mutex_t mutex; // Mutex to protect shared buffer access

int simulated_time = 0; // Simulated clock time

// Function to display the simulated clock time
void display_time() {
    simulated_time++;
    int hours = simulated_time / 3600;
    int minutes = (simulated_time % 3600) / 60;
    int seconds = simulated_time % 60;
    printf(" [Clock: %02d:%02d:%02d]\n", hours, minutes, seconds);
}

// Producer function
void *producer(void *param) {
    int item;
    for (int i = 0; i < NUM_OPERATIONS; i++) {
        item = rand() % 100; // Produce a random item

        // Wait if buffer is full
        sem_wait(&empty);

        // Lock the mutex to access the buffer
        pthread_mutex_lock(&mutex);

        // Add the item to the buffer
        buffer[in] = item;
        printf("Producer produced: %d", item);
        display_time();
        in = (in + 1) % BUFFER_SIZE;

        // Unlock the mutex
        pthread_mutex_unlock(&mutex);

        // Signal that buffer now has an additional full slot
        sem_post(&full);

        // Simulate production time
        sleep(1);
    }
    return NULL;
}

// Consumer function
void *consumer(void *param) {
    int item;
    for (int i = 0; i < NUM_OPERATIONS; i++) {
        // Wait if buffer is empty
        sem_wait(&full);

        // Lock the mutex to access the buffer
        pthread_mutex_lock(&mutex);

        // Remove the item from the buffer
        item = buffer[out];
        printf("Consumer consumed: %d", item);
        display_time();
        out = (out + 1) % BUFFER_SIZE;

        // Unlock the mutex
        pthread_mutex_unlock(&mutex);

        // Signal that buffer now has an additional empty slot
        sem_post(&empty);

        // Simulate consumption time
        sleep(1);
    }
    return NULL;
}

int main() {
    pthread_t tid1, tid2;

    // Initialize the semaphores and mutex
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    pthread_mutex_init(&mutex, NULL);

    // Create the producer and consumer threads
    pthread_create(&tid1, NULL, producer, NULL);
    pthread_create(&tid2, NULL, consumer, NULL);

    // Wait for the threads to complete
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    // Clean up semaphores and mutex
    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);

    printf("Program completed.\n");
    return 0;
}
