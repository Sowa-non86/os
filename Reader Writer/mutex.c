#include <stdio.h>
#include <pthread.h>
#include <unistd.h> // For sleep()

pthread_mutex_t mutex, write_lock;
int read_count = 0;
int simulated_time = 0; // Simulated time in seconds

// Function to display the simulated clock time
void display_time() {
    simulated_time++;
    int hours = simulated_time / 3600;
    int minutes = (simulated_time % 3600) / 60;
    int seconds = simulated_time % 60;
    printf(" [Clock: %02d:%02d:%02d]\n", hours, minutes, seconds);
}

void *reader(void *param) {
    // Entry section
    pthread_mutex_lock(&mutex); // Lock mutex for read_count update
    read_count++;
    if (read_count == 1)
        pthread_mutex_lock(&write_lock); // First reader blocks the writer
    pthread_mutex_unlock(&mutex); // Unlock mutex

    // Critical section (reading)
    printf("Reader %ld is reading", (long)param);
    display_time();
    sleep(1); // Simulate the time taken for reading

    // Exit section
    pthread_mutex_lock(&mutex); // Lock mutex for read_count update
    read_count--;
    if (read_count == 0)
        pthread_mutex_unlock(&write_lock); // Last reader allows writers
    pthread_mutex_unlock(&mutex); // Unlock mutex
    return NULL;
}

void *writer(void *param) {
    // Entry section
    pthread_mutex_lock(&write_lock); // Lock write_lock for writing

    // Critical section (writing)
    printf("Writer %ld is writing", (long)param);
    display_time();
    sleep(2); // Simulate the time taken for writing

    // Exit section
    pthread_mutex_unlock(&write_lock); // Unlock write_lock
    return NULL;
}

int main() {
    pthread_t r1, r2, r3, w1, w2;
    pthread_mutex_init(&mutex, NULL);     // Initialize mutex
    pthread_mutex_init(&write_lock, NULL); // Initialize write_lock

    pthread_create(&r1, NULL, reader, (void *)1);
    pthread_create(&r2, NULL, reader, (void *)2);
    pthread_create(&r3, NULL, reader, (void *)3);
    pthread_create(&w1, NULL, writer, (void *)1);
    pthread_create(&w2, NULL, writer, (void *)2);

    pthread_join(r1, NULL);
    pthread_join(r2, NULL);
    pthread_join(r3, NULL);
    pthread_join(w1, NULL);
    pthread_join(w2, NULL);

    pthread_mutex_destroy(&mutex);
    pthread_mutex_destroy(&write_lock);

    return 0;
}
