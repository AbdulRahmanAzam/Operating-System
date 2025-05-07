#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <pthread.h>
#include <stdlib.h>

#define NUM_THREADS 4
pthread_t threads[NUM_THREADS];

void siguser1_handler(int signum) {
    int i = gettid(), j = getppid(), k = getpid();
    printf("Thread id: %d, Process id: %d, Parent Process id: %d\n", i, k, j);
}

void *runner(void *arg) {
    while (1) sleep(1);
    return NULL;
}

int main() {
    signal(SIGUSR1, siguser1_handler); 

    for (int i = 0; i < NUM_THREADS; ++i) {
        if (pthread_create(&threads[i], NULL, runner, NULL) != 0) {
            perror("pthread_create");
            exit(EXIT_FAILURE);
        }
    }

    int i = gettid(), j = getppid(), k = getpid();
    printf("Parent Process ID: %u, Process ID: %u, main() thread ID: %u\n", k, k, i);
    printf("Thread IDs: 0=%lu, 1=%lu, 2=%lu and 3=%lu\n", threads[0], threads[1], threads[2], threads[3]);

    kill(k, SIGUSR1);              
    pthread_kill(threads[2], SIGUSR1); 

    for (int i = 0; i < NUM_THREADS; ++i) {
        if (pthread_join(threads[i], NULL) != 0) {
            perror("pthread_join");
            exit(EXIT_FAILURE);
        }
    }

    return 0;
}
