#include <stdio.h>
#include <pthread.h>

#define NUM_THREADS 5

int shared_data = 0;
pthread_mutex_t mutex;

void *thread_function(void *args){
    int thread_id = *((int *)args);

    pthread_mutex_lock(&mutex);
    shared_data++;
    pthread_mutex_unlock(&mutex);

    pthread_exit(NULL);
}

int main(){
    printf("Hello World");
    pthread_t threads[NUM_THREADS];  // array of threads
    int thread_args[NUM_THREADS];  // array of thread arguments
    int i;

    pthread_mutex_init(&mutex, NULL);  // initialize MUTEX

    // create threads
    for(i = 0; i < NUM_THREADS; i++){
        thread_args[i] = i;
        pthread_create(&threads[i], NULL, thread_function, &thread_args[i]);
    }

    // wait for all threads to complete
    for(i = 0; i < NUM_THREADS; i++){
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&mutex);

    return 0;
}
