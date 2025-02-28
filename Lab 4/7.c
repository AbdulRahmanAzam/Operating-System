#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
    pid_t child = fork();

    if(child < 0){
        printf("Fork Failed for child\n");
        return 1;
    }

    if(child == 0){
        printf("Child printing the contents of current directory\n\n");

        execlp("ls","ls","-l", NULL);
        printf("Child process failed to execute ls command\n");
        exit(1);
    }else{
        wait(NULL);
        printf("Parent Process: CHild finished");
    }
    return 0;
}
