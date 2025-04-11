```asm
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define THREAD_COUNT 10
#define ARRAY_SIZE 1000000

int arr[ARRAY_SIZE];
int brr[ARRAY_SIZE];
int crr[ARRAY_SIZE];

void generateRandomArrays() {
    for (int i = 0; i < ARRAY_SIZE; i++) {
        arr[i] = rand() % 1000;
        brr[i] = rand() % 1000;
        crr[i] = rand() % 1000;
    }
}

void printFirst100Elements() {
    for (int i = 0; i < 100; i++) {
        printf("%d ", crr[i]);
    }
    printf("\n");
}

void performSerialAddition() {
    for (int i = 0; i < ARRAY_SIZE; i++) {
        crr[i] = arr[i] + brr[i];
    }
}

void *performConcurrentAddition(void *arg) {
    int threadId = *((int *)arg);
    int startIdx = threadId * (ARRAY_SIZE / THREAD_COUNT);
    int endIdx = startIdx + (ARRAY_SIZE / THREAD_COUNT);

    for (int i = startIdx; i < endIdx; i++) {
        crr[i] = arr[i] + brr[i];
    }

    pthread_exit(NULL);
}

int main() {
    generateRandomArrays();

    // Serial computation
    performSerialAddition();
    printf("First 100 values of crr from Serial Computation:\n");
    printFirst100Elements();

    // Concurrent computation
    pthread_t threads[THREAD_COUNT];
    int threadIds[THREAD_COUNT];

    for (int i = 0; i < THREAD_COUNT; i++) {
        threadIds[i] = i;
        pthread_create(&threads[i], NULL, performConcurrentAddition, (void *)&threadIds[i]);
    }

    for (int i = 0; i < THREAD_COUNT; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("First 100 values of crr from Concurrent Computation:\n");
    printFirst100Elements();

    pthread_exit(NULL);
    return 0;
}

```

![Screenshot 2025-04-11 105806](https://github.com/user-attachments/assets/c6f67dde-35ad-4646-827b-2e757022e1bf)

