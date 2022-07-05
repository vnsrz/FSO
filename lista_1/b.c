#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>

void handle_sig(int sig) {
    char string[10];
    if(scanf(" %s", string) == EOF) exit(0);
    
    if(strcmp(string,"Igor3k") == 0 && sig == SIGUSR1){
        printf("Certo\n");
    }else if(strcmp(string,"Monark") == 0 && sig == SIGUSR2){
        printf("Certo\n");
    }else if(strcmp(string,"Con2") == 0 && sig == SIGTERM){
        printf("Certo\n");
    }else if(strcmp(string,"Silencio") == 0 && sig == SIGALRM){
        printf("Certo\n");
    }else if(strcmp(string,"Con1") == 0 && sig == SIGINT){
        printf("Certo\n");
    }else{
        printf("Erro\n");
    }
}

int main() {
    signal(SIGINT, handle_sig); // Convidado 1
    signal(SIGUSR1, handle_sig); // Igor
    signal(SIGUSR2, handle_sig); // Monark (rip)
    signal(SIGTERM, handle_sig); // Convidado 2
    signal(SIGALRM, handle_sig); // Geral

    while(1) ;
    
    return 0;
}