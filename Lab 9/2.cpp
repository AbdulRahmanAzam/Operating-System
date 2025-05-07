#include<iostream>
#include<unistd.h>
#include<signal.h>
#include<sys/wait.h>
#include<sys/stat.h>
#include<errno.h>
using namespace std;

void Signal_handler(int signum){
    cout<<"Signal Generated with Id: "<<signum<<endl;
    const char* folderName = "Child!!!Folder";
    if(mkdir(folderName, 0777) == -1){
        if(errno == EEXIST){
            cout << "Folder '" << folderName << "' already exists." << endl;
        } else {
            perror("Error creating folder");
        }
    } else {
        cout << "Folder '" << folderName << "' created successfully." << endl;
    }
}

int main(){
    if(signal(SIGCHLD,Signal_handler) == SIG_ERR){
        perror("Signal Not successfully initialized");
        exit(EXIT_FAILURE);
    }
    pid_t id;
    id = fork();
    if(id < 0) exit(EXIT_FAILURE);
    if( id == 0){
        cout<<"IN child Process"<<endl;
    }
    wait(NULL);
    cout<<"In Parent Process"<<endl;
    return 0;
}
