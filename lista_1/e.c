#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int count = 0;

void handle_sig(int sig) {
    pid_t pid;

    if(count++ == 0){
        if((pid = fork()) == 0){
            exit(0);
        }else{
            pause();
        }
    }else if(count++ == 1){
        if(pid > 0){
            waitpid(-1, NULL, WNOHANG);
        }
    }else{
        exit(0);
    }
}

int main() {
    signal(SIGUSR1, handle_sig); // 10
    signal(SIGUSR2, handle_sig); // Geral
    
    while(1){
        pause();
    }
    
    return 0;
}