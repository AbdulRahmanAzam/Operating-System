#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

int getUID(){
    printf("THe current UID: %d\n\n", getuid());
}

int main(){
    pid_t child = fork();

    if(child < 0){
        printf("Fork failed for child\n");
        return 1;
    }

    if(child == 0){ // child process
        printf("CHILD...\n");
        printf("The current PID: %d\n The parent PID: %d\n", getpid(), getppid());
        getUID();

        exit(0);
    }else{
        printf("PARENT...\n");
        printf("The parent PID: %d\n", getpid());
        getUID();

        wait(NULL);
    }

    return 0;
}
