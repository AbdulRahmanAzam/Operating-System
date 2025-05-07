#include<iostream>
#include<unistd.h>
#include<signal.h>
#include<vector>
#include<sys/wait.h>
#include<random>
using namespace std;

void Signal_handler(int signum){
    cout<<"Signal Generated with Id: "<<signum<<endl;
    exit(0);
}

int main(){
    if(signal(SIGINT,Signal_handler) == SIG_ERR){
        perror("Signal Not successfully initialized");
        exit(EXIT_FAILURE);
    }
    
    vector<int>arr;
    for(int i=0;i<15;i++){
        int val = random
        arr.push_back(val);
    }
    return 0;
}
