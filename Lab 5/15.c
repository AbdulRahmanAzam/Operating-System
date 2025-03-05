#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
    int fd;
    char buffer[200];
    ssize_t bytesRead;

    fd = open("input.txt", O_RDONLY);
    if(fd == -1){
        printf("Error opening input file");
        return 1;
    }

    bytesRead = read(fd, buffer, sizeof(buffer)-1);
    if(bytesRead == -1){
        printf("Error reading from file");
        close(fd);
        return 1;
    }
    buffer[bytesRead] = '\0';
    close(fd);

    pid_t pid = fork();
    if(pid < 0){
        printf("Error forking");
        return 1;
    }else if(pid == 0){
        fd = open("input.txt", O_WRONLY);
        if(fd == -1){
            printf("Error opening input file");
            return 1;
        }

        const char *msg = "child process done\n";
        write(fd, msg, strlen(msg)-1);
        close(fd);

        execlp("cat","cat", "input.txt", NULL);
        printf("execlp fialed");
        return 1;
    }else{
        wait(NULL);
    }

    return 0;
}
