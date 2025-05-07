#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>
#include<stdlib.h>
int num_t=3;
int icecreamremaining=3;
sem_t cone;

void *runner(void *args){
    int id = *(int *)args;
    int time = rand()%4;
    printf("Time required %d to Contestant %d for counting money from Wallet \n", time, id);
    sleep(time);
    sem_wait(&cone);
    printf("Icecream Assign to Contestant %d \n", id);
    icecreamremaining--;
    sem_post(&cone);

    pthread_exit(NULL);

}

int main(){
    pthread_t threads[num_t];
    int args[num_t];

    sem_init(&cone, 0, 1);
    
    for(int i = 0; i < num_t; i++){
        args[i] = i;
        pthread_create(&threads[i], NULL, runner, (void*)&args[i]);
    }

    for(int i = 0; i < num_t; i++){
        pthread_join(threads[i], NULL);
    }

    sem_destroy(&cone);

    return 0;
}
