```asm
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


void *calculateAverage(void *arg) {
    char **numbers = (char **)arg;
    int total = 0, count = 0;

    for (int i = 1; numbers[i] != NULL; i++) {
        total += atoi(numbers[i]);
        count++;
    }

    printf("Average: %.2f\n", (double)total / count);
    return NULL;
}


void *findMinimum(void *arg) {
    char **numbers = (char **)arg;
    int minValue = 10000;

    for (int i = 1; numbers[i] != NULL; i++) {
        int num = atoi(numbers[i]);
        if (num < minValue) {
            minValue = num;
        }
    }

    printf("Minimum Value: %d\n", minValue);
    return NULL;
}


void *findMaximum(void *arg) {
    char **numbers = (char **)arg;
    int maxValue = 0;

    for (int i = 1; numbers[i] != NULL; i++) {
        int num = atoi(numbers[i]);
        if (num > maxValue) {
            maxValue = num;
        }
    }

    printf("Maximum Value: %d\n", maxValue);
    return NULL;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Please provide integer inputs.\n");
        return 1;
    }

    pthread_t thread1, thread2, thread3;

    pthread_create(&thread1, NULL, calculateAverage, (void *)argv);
    pthread_create(&thread2, NULL, findMinimum, (void *)argv);
    pthread_create(&thread3, NULL, findMaximum, (void *)argv);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);

    pthread_exit(NULL);
    return 0;
}

```
