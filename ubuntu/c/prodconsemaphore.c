#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

// Buffer structure
typedef struct {
    int *buffer;         // Fixed-size buffer array
    int capacity;        // Maximum capacity of the buffer
    int in;              // Index for the next insertion
    int out;             // Index for the next removal
    sem_t full;          // Semaphore for full slots
    sem_t empty;         // Semaphore for empty slots
    sem_t mutex;         // Semaphore for critical section
} Buffer;

// Initialize the buffer
void initBuffer(Buffer *buffer, int capacity) {
    buffer->capacity = capacity;
    buffer->buffer = (int *)malloc(capacity * sizeof(int));
    buffer->in = 0;
    buffer->out = 0;

    sem_init(&buffer->full, 0, 0);           // Initially, no full slots
    sem_init(&buffer->empty, 0, capacity);   // Initially, all slots are empty
    sem_init(&buffer->mutex, 0, 1);          // Mutex initialized to 1
}

// Produce an item
void produce(Buffer *buffer, int item, int producerId) {
    if (sem_trywait(&buffer->empty) != 0) {
        printf("Producer%d blocked ... buffer full\n", producerId);
    }
    sem_wait(&buffer->empty); // Wait if buffer is full
    sem_wait(&buffer->mutex); // Enter critical section

    // Add item to buffer
    buffer->buffer[buffer->in] = item;
    printf("Producer%d inserting %d in slot %d\n", producerId, item, buffer->in + 1);
    buffer->in = (buffer->in + 1) % buffer->capacity;

    sem_post(&buffer->mutex); // Leave critical section
    sem_post(&buffer->full);  // Signal that an item is available
}

// Consume an item
void consume(Buffer *buffer, int consumerId) {
    if (sem_trywait(&buffer->full) != 0) {
        printf("Consumer%d blocked ... buffer empty\n", consumerId);
    }
    sem_wait(&buffer->full);  // Wait if buffer is empty
    sem_wait(&buffer->mutex); // Enter critical section

    // Remove item from buffer
    int item = buffer->buffer[buffer->out];
    printf("Consumer%d consuming %d from slot %d\n", consumerId, item, buffer->out + 1);
    buffer->out = (buffer->out + 1) % buffer->capacity;

    sem_post(&buffer->mutex); // Leave critical section
    sem_post(&buffer->empty); // Signal that a slot is available
}

// Producer thread function
void *producer(void *arg) {
    int producerId = *((int *)arg);
    Buffer *buffer = ((Buffer **)arg)[1];
    free(arg); // Free dynamically allocated memory

    while (1) {
        int item = rand() % 100; // Produce a random item
        produce(buffer, item, producerId);
        usleep(rand() % 1000000); // Simulate production time
    }
}

// Consumer thread function
void *consumer(void *arg) {
    int consumerId = *((int *)arg);
    Buffer *buffer = ((Buffer **)arg)[1];
    free(arg); // Free dynamically allocated memory

    while (1) {
        consume(buffer, consumerId);
        usleep(rand() % 1000000); // Simulate consumption time
    }
}

int main() {
    int numProducers, numConsumers, bufferSize;

    // Input for number of producers, consumers, and buffer size
    printf("Enter number of producers: ");
    scanf("%d", &numProducers);

    printf("Enter number of consumers: ");
    scanf("%d", &numConsumers);

    printf("Enter buffer size: ");
    scanf("%d", &bufferSize);

    // Shared buffer
    Buffer buffer;
    initBuffer(&buffer, bufferSize);

    // Create producer and consumer threads
    pthread_t producerThreads[numProducers];
    pthread_t consumerThreads[numConsumers];

    for (int i = 1; i <= numProducers; i++) {
        int *arg = malloc(2 * sizeof(void *));
        arg[0] = i;
        ((Buffer **)arg)[1] = &buffer;
        pthread_create(&producerThreads[i - 1], NULL, producer, arg);
    }

    for (int i = 1; i <= numConsumers; i++) {
        int *arg = malloc(2 * sizeof(void *));
        arg[0] = i;
        ((Buffer **)arg)[1] = &buffer;
        pthread_create(&consumerThreads[i - 1], NULL, consumer, arg);
    }

    // Join threads (optional, depending on the use case)
    for (int i = 0; i < numProducers; i++) {
        pthread_join(producerThreads[i], NULL);
    }
    for (int i = 0; i < numConsumers; i++) {
        pthread_join(consumerThreads[i], NULL);
    }

    // Free resources
    free(buffer.buffer);
    sem_destroy(&buffer.full);
    sem_destroy(&buffer.empty);
    sem_destroy(&buffer.mutex);

    return 0;
}
