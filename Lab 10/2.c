#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>
#include<stdlib.h>

int customer=10;
sem_t weight,check,boared;

void *runner(void *args){
    int id = *(int *)args;
    sem_wait(&weight);
    printf("Customer %d in Weighting Laguage\n", id);
    sleep(2);
    sem_post(&weight);

    sem_wait(&check);
    printf("Customer %d in Checking Laguage\n", id);
    sleep(3);
    sem_post(&check);

    sem_wait(&boared);
    printf("Customer %d in boarding  pass \n", id);
    sleep(1);
    sem_post(&boared);
    pthread_exit(NULL);
}

int main(){
    pthread_t threads[customer];
    int args[customer];

    sem_init(&weight, 0, 1);
    sem_init(&check, 0, 1);
    sem_init(&boared, 0, 1);

    for(int i = 0; i < customer; i++){
        args[i] = i;
        pthread_create(&threads[i], NULL, runner, (void*)&args[i]);
    }

    for(int i = 0; i < customer; i++){
        pthread_join(threads[i], NULL);
    }

    sem_destroy(&weight);
    sem_destroy(&check);
    sem_destroy(&boared);

    return 0;
}
