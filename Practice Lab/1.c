
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

FILE *tempfile = NULL;
char filename[32];

void handle_sigint(int sig) {
    if (tempfile) {
        fclose(tempfile);
        remove(filename);
        printf("\nFile closed and deleted. Exiting.\n");
    }
    exit(0);
}

int main() {
    sprintf(filename, "temp_%d.txt", getpid());
    
    tempfile = fopen(filename, "w");
    if (!tempfile) {
        perror("Failed to create temp file");
        return 1;
    }
    
    signal(SIGINT, handle_sigint);
    
    printf("Writing to %s (Ctrl+C to exit)\n", filename);
    
    int count = 0;
    while (1) {
        fprintf(tempfile, "Data entry %d\n", count++);
        fflush(tempfile);
        sleep(1);
    }
    
    return 0;
}
