#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

void *minhaVez(){
    int *ptr = (int *)malloc(sizeof(int));
    *ptr = 0;
    for(int i=0; i<8; i++){
        sleep(1);
        printf("%d Minha vez!\n", i+1);
        (*ptr)++;
    }

    return ptr;
}

void *suaVez(){
    for(int i=0; i<3; i++){
        sleep(2);
        printf("%d Sua vez!\n", i+1);
    }
}

int main(void){
    pthread_t tid;
    int *result;

    pthread_create(&tid, NULL, minhaVez, NULL);
    suaVez();
    pthread_join(tid,(void *)&result);

    printf("result === %d\n", *result);
    
    return 0;
}