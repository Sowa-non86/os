#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <stdbool.h>

// Shared variables
int readerCount = 0;          // Number of active readers
bool writerActive = false;    // Indicates if a writer is active
pthread_mutex_t lock;         // Mutex for synchronization
pthread_cond_t cond;          // Condition variable for synchronization

// Time variables
int hours, minutes, seconds;

// Increment clock logic
void incrementClock() {
    seconds++;
    if (seconds == 60) {
        seconds = 0;
        minutes++;
    }
    if (minutes == 60) {
        minutes = 0;
        hours++;
    }
    if (hours == 24) {
        hours = 0;
    }
}

// Get current time as string
void getTimeString(char *buffer) {
    sprintf(buffer, "%02d:%02d:%02d", hours, minutes, seconds);
}

// Simulate delay for a given duration
void simulateDelay(int iterations) {
    for (int i = 0; i < iterations * 100000; i++) {
        // Busy-wait to simulate delay
    }
}

// Reader function
void *reader(void *arg) {
    int readerId = *((int *)arg);
    free(arg);

    while (1) {
        pthread_mutex_lock(&lock);

        // Wait if a writer is active
        while (writerActive) {
            pthread_cond_wait(&cond, &lock);
        }

        readerCount++; // Increment reader count
        pthread_mutex_unlock(&lock);

        // Simulate reading
        char timeStr[9];
        getTimeString(timeStr);
        printf("Reader%d reads clock %s\n", readerId, timeStr);

        simulateDelay(100);

        pthread_mutex_lock(&lock);
        readerCount--; // Decrement reader count
        if (readerCount == 0) {
            pthread_cond_broadcast(&cond); // Notify writers waiting
        }
        pthread_mutex_unlock(&lock);

        // Exiting message for reader
        printf("Reader%d exiting clock %s\n", readerId, timeStr);

        usleep(100000); // Small delay to prevent tight looping
    }

    return NULL;
}

// Writer function
void *writer(void *arg) {
    int writerId = *((int *)arg);
    free(arg);

    while (1) {
        pthread_mutex_lock(&lock);

        // Wait if any reader is active or another writer is active
        while (writerActive || readerCount > 0) {
            pthread_cond_wait(&cond, &lock);
        }

        writerActive = true; // Mark writer as active
        pthread_mutex_unlock(&lock);

        // Simulate writing
        char timeStr[9];
        getTimeString(timeStr);
        printf("Writer%d writes clock %s\n", writerId, timeStr);

        simulateDelay(200);

        pthread_mutex_lock(&lock);
        writerActive = false; // Mark writer as inactive
        pthread_cond_broadcast(&cond); // Notify readers and writers
        pthread_mutex_unlock(&lock);

        // Exiting message for writer
        printf("Writer%d exiting clock %s\n", writerId, timeStr);

        usleep(100000); // Small delay to prevent tight looping
    }

    return NULL;
}

int main() {
    int numReaders, numWriters;

    // Input the number of readers and writers
    printf("Enter the number of readers: ");
    scanf("%d", &numReaders);
    printf("Enter the number of writers: ");
    scanf("%d", &numWriters);

    // Input the clock start time
    printf("Enter clock start (hh:mm:ss): ");
    scanf("%d:%d:%d", &hours, &minutes, &seconds);

    printf("Press Ctrl+C to stop the process.\n");

    pthread_t readers[numReaders], writers[numWriters];

    // Initialize mutex and condition variable
    pthread_mutex_init(&lock, NULL);
    pthread_cond_init(&cond, NULL);

    // Create writer threads
    for (int i = 0; i < numWriters; i++) {
        int *arg = malloc(sizeof(int));
        *arg = i + 1;
        pthread_create(&writers[i], NULL, writer, arg);
    }

    // Create reader threads
    for (int i = 0; i < numReaders; i++) {
        int *arg = malloc(sizeof(int));
        *arg = i + 1;
        pthread_create(&readers[i], NULL, reader, arg);
    }

    while (1) {
        // Increment the shared clock
        pthread_mutex_lock(&lock);
        incrementClock();
        pthread_mutex_unlock(&lock);

        sleep(1); // Simulate 1-second delay
    }

    // Cleanup (not reachable in this simulation)
    pthread_mutex_destroy(&lock);
    pthread_cond_destroy(&cond);

    return 0;
}
