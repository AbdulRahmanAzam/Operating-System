#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_TELLERS 3
#define NUM_TRANSACTIONS 15

pthread_mutex_t balance_mutex;
double account_balance = 1000.0;

void *teller(void *arg) {
    int id = *((int *)arg);
    int i;
    
    for (i = 0; i < NUM_TRANSACTIONS / NUM_TELLERS; i++) {
        double transaction = (rand() % 200) - 100;
        
        pthread_mutex_lock(&balance_mutex);
        
        double old_balance = account_balance;
        sleep(rand() % 2);
        account_balance += transaction;
        
        printf("Teller %d: %.2f %s %.2f = %.2f\n", 
               id, 
               old_balance, 
               transaction >= 0 ? "+" : "-", 
               transaction >= 0 ? transaction : -transaction, 
               account_balance);
               
        pthread_mutex_unlock(&balance_mutex);
        
        usleep(rand() % 500000);
    }
    
    pthread_exit(NULL);
}

int main() {
    pthread_t tid[NUM_TELLERS];
    int teller_ids[NUM_TELLERS];
    int i;
    
    pthread_mutex_init(&balance_mutex, NULL);
    
    printf("Initial balance: %.2f\n", account_balance);
    
    for (i = 0; i < NUM_TELLERS; i++) {
        teller_ids[i] = i + 1;
        pthread_create(&tid[i], NULL, teller, &teller_ids[i]);
    }
    
    for (i = 0; i < NUM_TELLERS; i++) {
        pthread_join(tid[i], NULL);
    }
    
    printf("Final balance: %.2f\n", account_balance);
    
    pthread_mutex_destroy(&balance_mutex);
    
    return 0;
}
