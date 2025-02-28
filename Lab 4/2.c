#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

int main(){
    pid_t child = fork();

    if(child < 0){
        printf("Fork failed for child");
        return 1;
    }

    if(child == 0){
        for(int i = 0; i < 100; i++){
            printf("%d  child process, PID: %d\n",i, getpid());
        }
        exit(0);
    }else{
        wait(NULL);
        for(int i = 0; i < 100; i++){
            printf("%d  parent process, PID: %d\n",i, getpid());
        }
    }

    return 0;
}
