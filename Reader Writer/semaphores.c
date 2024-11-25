#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h> // For sleep()

sem_t mutex, write_lock;
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
    sem_wait(&mutex);  // Lock mutex for read_count update
    read_count++;
    if (read_count == 1)
        sem_wait(&write_lock);  // First reader blocks the writer
    sem_post(&mutex);  // Unlock mutex

    // Critical section (reading)
    printf("Reader %ld is reading", (long)param);
    display_time();
    sleep(1); // Simulate reading time

    // Exit section
    sem_wait(&mutex);  // Lock mutex for read_count update
    read_count--;
    if (read_count == 0)
        sem_post(&write_lock);  // Last reader allows writers
    sem_post(&mutex);  // Unlock mutex
    return NULL;
}

void *writer(void *param) {
    // Entry section
    sem_wait(&write_lock);  // Lock write_lock for writing

    // Critical section (writing)
    printf("Writer %ld is writing", (long)param);
    display_time();
    sleep(2); // Simulate writing time

    // Exit section
    sem_post(&write_lock);  // Unlock write_lock
    return NULL;
}

int main() {
    pthread_t r1, r2, r3, w1, w2;
    sem_init(&mutex, 0, 1);  // Initialize mutex
    sem_init(&write_lock, 0, 1);  // Initialize write_lock

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

    sem_destroy(&mutex);
    sem_destroy(&write_lock);

    return 0;
}
