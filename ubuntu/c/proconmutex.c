#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

// Buffer structure
typedef struct {
    int *buffer;       // Fixed-size buffer array
    int capacity;      // Maximum capacity of the buffer
    int in;            // Index for the next insertion
    int out;           // Index for the next removal
    int count;         // Current count of items in the buffer

    pthread_mutex_t lock;        // Mutex lock
    pthread_cond_t notFull;      // Condition for producers
    pthread_cond_t notEmpty;     // Condition for consumers
} Buffer;

// Data structure for thread arguments
typedef struct {
    Buffer *buffer;
    int id;
} ThreadData;

// Initialize the buffer
void initBuffer(Buffer *buffer, int capacity) {
    buffer->capacity = capacity;
    buffer->buffer = (int *)malloc(capacity * sizeof(int));
    buffer->in = 0;
    buffer->out = 0;
    buffer->count = 0;

    pthread_mutex_init(&buffer->lock, NULL);
    pthread_cond_init(&buffer->notFull, NULL);
    pthread_cond_init(&buffer->notEmpty, NULL);
}

// Producer function
void *producer(void *arg) {
    ThreadData *data = (ThreadData *)arg;
    Buffer *buffer = data->buffer;
    int producerId = data->id;

    while (1) {
        int item = rand() % 100; // Produce a random item
        pthread_mutex_lock(&buffer->lock);

        while (buffer->count == buffer->capacity) {
            printf("Producer %d blocked ... buffer full\n", producerId);
            pthread_cond_wait(&buffer->notFull, &buffer->lock);
        }

        // Add item to buffer
        buffer->buffer[buffer->in] = item;
        printf("Producer %d inserting %d in slot %d\n", producerId, item, buffer->in + 1);
        buffer->in = (buffer->in + 1) % buffer->capacity;
        buffer->count++;

        pthread_cond_signal(&buffer->notEmpty);
        pthread_mutex_unlock(&buffer->lock);

        usleep(rand() % 1000000); // Simulate production time
    }
}

// Consumer function
void *consumer(void *arg) {
    ThreadData *data = (ThreadData *)arg;
    Buffer *buffer = data->buffer;
    int consumerId = data->id;

    while (1) {
        pthread_mutex_lock(&buffer->lock);

        while (buffer->count == 0) {
            printf("Consumer %d blocked ... buffer empty\n", consumerId);
            pthread_cond_wait(&buffer->notEmpty, &buffer->lock);
        }

        // Remove item from buffer
        int item = buffer->buffer[buffer->out];
        printf("Consumer %d consuming %d from slot %d\n", consumerId, item, buffer->out + 1);
        buffer->out = (buffer->out + 1) % buffer->capacity;
        buffer->count--;

        pthread_cond_signal(&buffer->notFull);
        pthread_mutex_unlock(&buffer->lock);

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
    pthread_t producers[numProducers];
    pthread_t consumers[numConsumers];

    // Thread data
    ThreadData producerData[numProducers];
    ThreadData consumerData[numConsumers];

    for (int i = 0; i < numProducers; i++) {
        producerData[i].buffer = &buffer;
        producerData[i].id = i + 1;
        pthread_create(&producers[i], NULL, producer, &producerData[i]);
    }

    for (int i = 0; i < numConsumers; i++) {
        consumerData[i].buffer = &buffer;
        consumerData[i].id = i + 1;
        pthread_create(&consumers[i], NULL, consumer, &consumerData[i]);
    }

    // Join threads (optional, depending on use case)
    for (int i = 0; i < numProducers; i++) {
        pthread_join(producers[i], NULL);
    }

    for (int i = 0; i < numConsumers; i++) {
        pthread_join(consumers[i], NULL);
    }

    // Free resources
    free(buffer.buffer);
    pthread_mutex_destroy(&buffer.lock);
    pthread_cond_destroy(&buffer.notFull);
    pthread_cond_destroy(&buffer.notEmpty);

    return 0;
}
