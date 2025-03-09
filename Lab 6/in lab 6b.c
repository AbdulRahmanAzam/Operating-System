

// PRODUCER CODE
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#define BUFFER_SIZE 25
#define READ_END 0
#define WRITE_END 1
#define FIFO_FILE "/tmp/myfifo"

int main(){
    int fd;
    char buffer[BUFFER_SIZE];
    ssize_t num_bytes;

    mkfifo(FIFO_FILE, 0666);
    fd = open(FIFO_FILE, O_WRONLY);

    if(fd == -1){
        fprintf(stderr, "Failed to open FIFO file");
        exit(EXIT_FAILURE);
    }

    while(1){
        printf("Producer: Enter a message (or 'exit' to quit): ");
        fgets(buffer, BUFFER_SIZE, stdin);

        num_bytes = write(fd, buffer, strlen(buffer) + 1);
        if(num_bytes == -1){
            fprintf(stderr, "Failed to write to FIFO file");
            exit(EXIT_FAILURE);
        }
        if(strncmp(buffer, "exit", 4) == 0){
            break;
        }
    }
    close(fd);
    unlink(FIFO_FILE); // if the consumer is there then no need for Unlink

    return 0;
}
