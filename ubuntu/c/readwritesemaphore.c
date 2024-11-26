#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

// Shared variables
int readerCount = 0;          // Number of active readers
sem_t mutex;                  // Semaphore to protect readerCount
sem_t writerLock;             // Semaphore to ensure writers get exclusive access

// Time variables
int hours = 0, minutes = 0, seconds = 0;

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
        // Protect readerCount updates
        sem_wait(&mutex);
        readerCount++;
        if (readerCount == 1) {
            // First reader locks the writer
            sem_wait(&writerLock);
        }
        sem_post(&mutex);

        // Simulate reading
        char timeStr[9];
        getTimeString(timeStr);
        printf("Reader%d reads clock %s\n", readerId, timeStr);

        simulateDelay(100);

        // Protect readerCount updates
        sem_wait(&mutex);
        readerCount--;
        if (readerCount == 0) {
            // Last reader unlocks the writer
            sem_post(&writerLock);
        }
        sem_post(&mutex);

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
        // Ensure exclusive access for the writer
        sem_wait(&writerLock);

        // Simulate writing
        char timeStr[9];
        getTimeString(timeStr);
        printf("Writer%d writes clock %s\n", writerId, timeStr);

        simulateDelay(200);

        // Release writer lock
        sem_post(&writerLock);

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

    // Initialize semaphores
    sem_init(&mutex, 0, 1);
    sem_init(&writerLock, 0, 1);

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
        incrementClock();

        sleep(1); // Simulate 1-second delay
    }

    // Cleanup (not reachable in this simulation)
    sem_destroy(&mutex);
    sem_destroy(&writerLock);

    return 0;
}
