#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define BUFFER_SIZE 5 // Define the size of the buffer
#define MAX_ITEMS 10  // Define the number of items to produce and consume

int buffer[BUFFER_SIZE]; // Shared buffer
int in = 0; // Index for producer
int out = 0; // Index for consumer
int count = 0; // Number of items in the buffer
int items_produced = 0; // Total items produced
int items_consumed = 0; // Total items consumed

pthread_mutex_t mutex; // Mutex to protect shared buffer access
pthread_cond_t not_empty; // Condition variable to check if buffer is not empty
pthread_cond_t not_full;  // Condition variable to check if buffer is not full

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
    while (1) {
        item = rand() % 100; // Produce a random item

        // Lock the mutex to access the buffer
        pthread_mutex_lock(&mutex);

        // Stop production after MAX_ITEMS
        if (items_produced >= MAX_ITEMS) {
            pthread_mutex_unlock(&mutex);
            break;
        }

        // Wait if buffer is full
        while (count == BUFFER_SIZE) {
            pthread_cond_wait(&not_full, &mutex);
        }

        // Add the item to the buffer
        buffer[in] = item;
        printf("Producer produced: %d", item);
        display_time();
        in = (in + 1) % BUFFER_SIZE;
        count++;
        items_produced++;

        // Signal that the buffer is not empty
        pthread_cond_signal(&not_empty);

        // Unlock the mutex
        pthread_mutex_unlock(&mutex);

        // Simulate production time
        sleep(1);
    }
    return NULL;
}

// Consumer function
void *consumer(void *param) {
    int item;
    while (1) {
        // Lock the mutex to access the buffer
        pthread_mutex_lock(&mutex);

        // Stop consumption after MAX_ITEMS
        if (items_consumed >= MAX_ITEMS) {
            pthread_mutex_unlock(&mutex);
            break;
        }

        // Wait if buffer is empty
        while (count == 0) {
            pthread_cond_wait(&not_empty, &mutex);
        }

        // Remove the item from the buffer
        item = buffer[out];
        printf("Consumer consumed: %d", item);
        display_time();
        out = (out + 1) % BUFFER_SIZE;
        count--;
        items_consumed++;

        // Signal that the buffer is not full
        pthread_cond_signal(&not_full);

        // Unlock the mutex
        pthread_mutex_unlock(&mutex);

        // Simulate consumption time
        sleep(1);
    }
    return NULL;
}

int main() {
    pthread_t tid1, tid2;

    // Initialize the mutex and condition variables
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&not_empty, NULL);
    pthread_cond_init(&not_full, NULL);

    // Create the producer and consumer threads
    pthread_create(&tid1, NULL, producer, NULL);
    pthread_create(&tid2, NULL, consumer, NULL);

    // Wait for the threads to complete
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    // Clean up mutex and condition variables
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&not_empty);
    pthread_cond_destroy(&not_full);

    printf("Program completed.\n");
    return 0;
}
