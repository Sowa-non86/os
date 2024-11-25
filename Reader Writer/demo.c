#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<semaphore.h>

sem_t mutex,writelock;
int readcount=0;
int time=0;

void distime()
{
    time++;
    int hour = time / 3600;
    int min = (time % 3600) / 60;
    int sec = time % 60;
    printf("Clock[%d:%d:%d]\n",hour,min,sec);
}

void *reader(void *param)
{
    sem_wait(&mutex);
    readcount++;
    if(readcount == 1)
    {
        sem_wait(&writelock);
    }
    sem_post(&mutex);

    printf("\nReader %d reading\n",param);
    distime();
    sleep(1);

    sem_wait(&mutex);
    readcount--;
    if(readcount == 0)
    {
        sem_post(&writelock);
    }
    sem_post(&mutex);

    return NULL;

}

void *writer (void *param)
{
    sem_wait(&writelock);

    printf("\nWriter %d Writing\n",param);
    distime();
    sleep(1);

    sem_post(&writelock);
    return NULL;

}

int main()
{
    pthread_t r1,r2,r3,w1,w2;

    sem_init(&mutex,0,1);
    sem_init(&writelock,0,1);

    pthread_create(&r1,NULL,reader,(void *)1);
    pthread_create(&r2,NULL,reader,(void *)2);
    pthread_create(&r3,NULL,reader,(void *)3);
    pthread_create(&w1,NULL,writer,(void *)1);
    pthread_create(&w2,NULL,writer,(void *)2);

    pthread_join(r1,NULL);
    pthread_join(r2,NULL);
    pthread_join(r3,NULL);
    pthread_join(w1,NULL);
    pthread_join(w2,NULL);

    sem_destroy(&mutex);
    sem_destroy(&writelock);

    return 0;




}


