#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void handle_alarm(int sig){
    printf("Alarm recieved\n");
    exit(0);
}

int main(){
    alarm(5); // alarm for 5 seconds

    signal(SIGALRM, handle_alarm); // Register the signal handler for SIG ALRM

    int count = 1;
    while(1){
        printf("Seconds: %d\n", count);
        sleep(1); // pause for 1 second
        count++;
    }

    return 0; 
}
