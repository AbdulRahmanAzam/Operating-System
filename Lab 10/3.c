#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>

int totalsellers = 5;
sem_t db_access;
int ticketcnt = 0;
pthread_mutex_t mutex;
int totaltickets = 100; 

void *runner(void *args){
    int id = *(int *)args;
    while(1){
        sem_wait(&db_access);
        pthread_mutex_lock(&mutex);

        if(ticketcnt >= totaltickets){
            pthread_mutex_unlock(&mutex);
            sem_post(&db_access);
            break;
        }

        printf("Seller %d sells ticket Number: %d\n", id, ticketcnt);
        ticketcnt++;
        sleep(0.5);

        pthread_mutex_unlock(&mutex);
        sem_post(&db_access);
    }
    pthread_exit(NULL);
}

int main(){
    pthread_t threads[totalsellers];
    int args[totalsellers];

    pthread_mutex_init(&mutex, NULL);
    sem_init(&db_access, 0, 1);

    for(int i = 0; i < totalsellers; i++){
        args[i] = i;
        pthread_create(&threads[i], NULL, runner, (void*)&args[i]);
    }

    for(int i = 0; i < totalsellers; i++){
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    sem_destroy(&db_access);

    return 0;
}
