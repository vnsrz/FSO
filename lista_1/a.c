#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

int count = 0;

void handle_sig(int sig) {
    printf("Recebi %d\n", sig);

    if(sig == SIGINT){
        count = 1;
    }else if(count == 1 && sig == SIGUSR2){
        count = 2;
    }else if(count == 2 && sig == SIGTERM){
        count = 3;
        printf("Senha acionada\n");
    }else if(count == 3 && sig == SIGUSR1){
        printf("Tchau\n");
        exit(0);
    } else {
        count = 0;
    }
}

int main() {
    signal(SIGINT, handle_sig); // 2
    signal(SIGUSR1, handle_sig); // 10
    signal(SIGUSR2, handle_sig); // 12
    signal(SIGTERM, handle_sig); // 15

    while(1) ;
    
    return 0;
}