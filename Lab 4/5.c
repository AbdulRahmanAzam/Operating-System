#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
    pid_t child = fork();

    if(child < 0){
        printf("Fork Failed for CHild\n");
        return 1;
    }else if(child == 0){
        printf("Child process executing ls -l \n");

        if(execlp("ls", "ls", "-l", NULL) == -1){
            printf("execlp failed\n");          
            exit(1);
        }
        
        exit(0);
    }else{
        printf("parent waiting for child");
        wait(NULL); //parent waiting

        printf("Child finished, Parent now terminating");


    }
}
