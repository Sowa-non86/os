#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>


#define BUFFERSIZE 5
#define MAX_ITEMS 10

int buffer[BUFFERSIZE];
int in = 0, out = 0;
int count=0;
int itemsproduced=0;
int itemsconsumed=0;

pthread_mutex_t mutex;
pthread_cond_t notfull;
pthread_cond_t notempty;

void *producer (void *param)
{
    int item;

    while(1)
    {
        item = rand() % 100;

        pthread_mutex_lock(&mutex);

        if(itemsproduced>=MAX_ITEMS)
        {
            pthread_mutex_unlock(&mutex);
            break;
        }

        while(count==BUFFERSIZE)
        {
            pthread_cond_wait(&notfull,&mutex);
        }

        buffer[in]=item;
        printf("Producer Produced:%d\n",item);
        in=(in+1)%BUFFERSIZE;
        count++;
        itemsproduced++;

        pthread_cond_signal(&notempty);

        pthread_mutex_unlock(&mutex);

        sleep(1);

    }

    return NULL;
}



void *consumer (void *param)
{
    int item;

    while(1)
    {
       

        pthread_mutex_lock(&mutex);

        if(itemsconsumed>=MAX_ITEMS)
        {
            pthread_mutex_unlock(&mutex);
            break;
        }

        while(count==0)
        {
            pthread_cond_wait(&notempty,&mutex);
        }

        item=buffer[out];
        printf("Consumer Consumed:%d\n",item);
        out=(out+1)%BUFFERSIZE;
        count--;
        itemsconsumed++;

        pthread_cond_signal(&notfull);

        pthread_mutex_unlock(&mutex);

        sleep(1);

    }

    return NULL;
}

int main() {
    pthread_t tid1, tid2;

    // Initialize the mutex and condition variables
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&notempty, NULL);
    pthread_cond_init(&notfull, NULL);

    // Create the producer and consumer threads
    pthread_create(&tid1, NULL, producer, NULL);
    pthread_create(&tid2, NULL, consumer, NULL);

    // Wait for the threads to complete
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    // Clean up mutex and condition variables
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&notempty);
    pthread_cond_destroy(&notfull);

    printf("Program completed.\n");
    return 0;
}