#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_CUSTOMERS 10
#define NUM_CHEFS 2
#define MAX_ORDERS 20

typedef struct {
    int order_id;
    int customer_id;
} Order;

Order orders[MAX_ORDERS];
int order_count = 0;

pthread_mutex_t order_mutex;
sem_t chef_sem;

void *customer(void *arg) {
    int id = *((int *)arg);
    
    pthread_mutex_lock(&order_mutex);
    
    if (order_count < MAX_ORDERS) {
        orders[order_count].order_id = order_count + 1;
        orders[order_count].customer_id = id;
        
        printf("Customer %d placed order #%d\n", id, orders[order_count].order_id);
        
        order_count++;
    }
    
    pthread_mutex_unlock(&order_mutex);
    
    pthread_exit(NULL);
}

void *chef(void *arg) {
    int id = *((int *)arg);
    
    while (1) {
        sem_wait(&chef_sem);
        
        pthread_mutex_lock(&order_mutex);
        
        if (order_count > 0) {
            order_count--;
            Order current = orders[order_count];
            
            printf("Chef %d preparing order #%d for customer %d\n", 
                   id, current.order_id, current.customer_id);
                   
            pthread_mutex_unlock(&order_mutex);
            
            usleep((rand() % 1000000) + 500000);
            
            printf("Chef %d completed order #%d for customer %d\n", 
                   id, current.order_id, current.customer_id);
        } else {
            pthread_mutex_unlock(&order_mutex);
            break;
        }
    }
    
    pthread_exit(NULL);
}

int main() {
    pthread_t customers[NUM_CUSTOMERS];
    pthread_t chefs[NUM_CHEFS];
    int customer_ids[NUM_CUSTOMERS];
    int chef_ids[NUM_CHEFS];
    int i;
    
    pthread_mutex_init(&order_mutex, NULL);
    sem_init(&chef_sem, 0, NUM_CHEFS);
    
    for (i = 0; i < NUM_CUSTOMERS; i++) {
        customer_ids[i] = i + 1;
        pthread_create(&customers[i], NULL, customer, &customer_ids[i]);
    }
    
    for (i = 0; i < NUM_CHEFS; i++) {
        chef_ids[i] = i + 1;
        pthread_create(&chefs[i], NULL, chef, &chef_ids[i]);
        
        sem_post(&chef_sem);
    }
    
    for (i = 0; i < NUM_CUSTOMERS; i++) {
        pthread_join(customers[i], NULL);
    }
    
    for (i = 0; i < NUM_CHEFS; i++) {
        pthread_join(chefs[i], NULL);
    }
    
    pthread_mutex_destroy(&order_mutex);
    sem_destroy(&chef_sem);
    
    return 0;
}
