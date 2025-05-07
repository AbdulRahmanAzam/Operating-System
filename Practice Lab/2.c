#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int *array;
int *temp;
int size;

typedef struct {
    int start;
    int end;
} SortParams;

void merge(int start, int mid, int end) {
    int i, j, k;
    i = start;
    j = mid + 1;
    k = start;
    
    while (i <= mid && j <= end) {
        if (array[i] <= array[j])
            temp[k++] = array[i++];
        else
            temp[k++] = array[j++];
    }
    
    while (i <= mid)
        temp[k++] = array[i++];
        
    while (j <= end)
        temp[k++] = array[j++];
        
    for (i = start; i <= end; i++)
        array[i] = temp[i];
}

void sort(int start, int end) {
    if (start < end) {
        int mid = (start + end) / 2;
        sort(start, mid);
        sort(mid + 1, end);
        merge(start, mid, end);
    }
}

void *thread_sort(void *arg) {
    SortParams *params = (SortParams *)arg;
    sort(params->start, params->end);
    pthread_exit(NULL);
}

int main() {
    int i;
    size = 10;
    
    array = (int *)malloc(size * sizeof(int));
    temp = (int *)malloc(size * sizeof(int));
    
    for (i = 0; i < size; i++) {
        array[i] = rand() % 100;
        printf("%d ", array[i]);
    }
    printf("\n");
    
    pthread_t tid[2];
    SortParams params[2];
    
    params[0].start = 0;
    params[0].end = size/2 - 1;
    
    params[1].start = size/2;
    params[1].end = size - 1;
    
    pthread_create(&tid[0], NULL, thread_sort, &params[0]);
    pthread_create(&tid[1], NULL, thread_sort, &params[1]);
    
    pthread_join(tid[0], NULL);
    pthread_join(tid[1], NULL);
    
    merge(0, size/2 - 1, size - 1);
    
    for (i = 0; i < size; i++)
        printf("%d ", array[i]);
    printf("\n");
    
    free(array);
    free(temp);
    
    return 0;
}
