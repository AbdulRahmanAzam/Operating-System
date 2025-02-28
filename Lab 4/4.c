#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>


int main(){
    char buffer[1000];


    int inputf = open("input.txt", O_RDONLY);
    if(inputf == -1){
        printf("Error opening input file\n");
        return 1;
    }

    int outputf = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if(outputf == -1){
        printf("Error opening output file\n");
        close(outputf);
        return 1;
    }

    int bytes_read = read(inputf, buffer, sizeof(buffer) - 1);
    if(bytes_read < 0){
        printf("Error reading from input file\n");
        close(inputf);
        return 1;
    }else if(bytes_read == 0){
        printf("Input file is empty\n");
        close(inputf);
        return 1;
    }else{
        buffer[bytes_read] = '\0';
        int bytes_written = write(outputf, buffer, bytes_read);

        if(bytes_written < 0){
            printf("Error writing to output file\n");
            close(inputf);
            close(outputf);
            return 1;
        }
    }


    close(inputf);
    close(outputf);

    printf("File is copied successfully...\n");
    return 0;
}
