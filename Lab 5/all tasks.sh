
# 1. Create a directory called project in your home directory
mkdir -p ~/project

# 2. Navigate to the project directory
cd ~/project

# 3. Create an empty file named task1.txt in the project directory
touch task1.txt

# 4. List all files in the current directory using the ls command. Create a file called file1.txt
ls
> file1.txt

# 5. Change the permissions of file1.txt so that only the owner has read and write permissions, and others have no permissions
chmod 600 file1.txt

# 6. Check the permissions of file1.txt using the ls -l command
ls -l file1.txt

# 7. Grant execute permissions to the owner of file1.txt
chmod u+x file1.txt

# 8. Display the current working directory using the pwd command
pwd

# 9. Show the current date and time using the date command
date

# 10. Display your system’s disk usage with the df -h command
df -h

# 11. Display system uptime using the uptime command
uptime

# 12. Show all users currently logged into the system using the who command
who

# 13-14. The script will take a filename as input, count, and display the number of lines in that file
echo -n "Enter filename: "
read filename
wc -l "$filename"


# 15.
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
