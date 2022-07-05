#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int count = 0;

void handle_sig(int sig) {}

int main() {
    signal(SIGUSR1, handle_sig); // 10
    signal(SIGUSR2, handle_sig); // Geral
    
    pause();
    if(fork() == 0)
        exit(0);
    pause();
    wait(NULL);
    pause();
    
    return 0;
}