#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

int count = 0;

void handle_sig(int sig) {
    if(sig == SIGALRM){
        if(++count == 3){
            printf("Os incomodados que se mudem, tchau\n");
            exit(0);
        }
        printf("Ai que sono, quero dormir mais um pouco\n");
        return;
    }

    printf("SIGUSR1 eh para aproveitar mais um pouco\n");
}

int main() {
    signal(SIGUSR1, handle_sig); // 10
    signal(SIGALRM, handle_sig); // Geral
    
    while(1){
        pause();
    }
    
    return 0;
}