#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

int *v, n=100;
unsigned semente;

typedef struct args{
    unsigned l;
    unsigned r;
    int tam;
}args;

void printArray(int *v, int size){
    int i;

    printf("%d", v[0]);
    for (i=1; i < size; i++)
        printf(" %d", v[i]);
    printf("\n");
}

void* verificaSeed(void* arg){
    args *ptr = (args *)arg;
    unsigned seed=ptr->l, aux=ptr->l;
    int i=0, t;

    while(i < ptr->tam){
        for(int j=1;j<10000;j++) rand_r(&seed); // roda o rand_r 9.999 vezes

        t = rand_r(&seed)%256;

        if(t != v[i]){ // compara o 10.000 numero gerado com v[i]
            if(aux == ptr->r) return 0; // se o numero a ser comparado for o ultimo, retorna 0
            seed = ++aux;
            i = 0;
        }else i++;
    }

    semente = aux;
}

int main(void){
    pthread_t tid;
    unsigned mi, mf;
    args arg1;
    args arg2;

    int i=0;
    v = malloc(sizeof(int)*n);

    scanf("%u %u",&mi, &mf);

    while(scanf("%d", &v[i]) != EOF){
        i++;
        if(i == n-1) v = realloc(v, sizeof(int)*2*n);
    }

    if(mf != mi){
        int meio = (mf - mi)/2;
        arg1.l = mi;
        arg1.r = mi+meio;
        arg1.tam = i;

        arg2.l = mi+meio+1;
        arg2.r = mf;
        arg2.tam = i;

        pthread_create(&tid, NULL, verificaSeed, &arg1);
        verificaSeed(&arg2);
        pthread_join(tid, NULL);

    } else semente = mi;

    printf("%u\n", semente);

    return 0;
}
