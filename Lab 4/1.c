#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(){
    pid_t child1 = fork();

    if(child1 < 0){
        printf("Fork failed for child1");
        return 1;
    }    

    if(child1 == 0){
        printf("Child 1: Pid : %d \n", getpid());

        printf("CHild 1 is terminating\n\n");
        exit(0);
    }

    pid_t child2 = fork();

    if(child2 < 0){
        printf("Fork failed for child2");
        return 1;
    }

    if(child2 == 0){
        printf("Child 2: My pid is: %d \n", getpid()); // child 2 pid
        printf("Child 2: My parents Pid : %d \n", getppid()); // child2 parent pid

        exit(0);
    }

    wait(NULL);
    wait(NULL);

    printf("Parent: Both child have been finished");


    return 0;
}
