#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

void *minhaVez(){
    for(int i=0; i<8; i++){
        sleep(1);
        printf("%d Minha vez!\n", i+1);
    }
}

void *suaVez(){
    for(int i=0; i<3; i++){
        sleep(2);
        printf("%d Sua vez!\n", i+1);
    }
}

int main(void){
    pthread_t tid;

    pthread_create(&tid, NULL, minhaVez, NULL);
    suaVez();
    pthread_join(tid, NULL);

    return 0;
}