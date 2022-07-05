#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <signal.h>

int THREADS = 2;

int a[2000][2000], b[2000][2000], c[2000][2000];
int sinalf1 = 0, sinalf2=0;

typedef struct t_param{
    int inicio;
    int fim;
    int size;
    int sig;
}param;

void trata_sinalf1(int s) {
    //printf("----> Recebi f1\n");
    sinalf1++;
}

void trata_sinalf2(int s) {
    //printf("----> Recebi f2\n");
    sinalf2++;
}

void aguenta(int s){
    return;
}

void leMatriz(int n){
    int aux;
    for(int i=0; i < n; i++){
        for(int j=0; j < n; j++){
            scanf("%d", &aux);
            a[i][j] = aux;
            c[i][j] = 0;
        }
    }
    for(int i=0; i < n; i++){
        for(int j=0; j < n; j++){
            scanf("%d", &aux);
            b[i][j] = aux;
        }
    }
}

void *multiplica(void *l){
    signal(SIGUSR1, aguenta);
    //printf("# Filho %d\n", getpid());
    for(int i=((param*)l)->inicio; i<((param*)l)->fim; i++)
        for(int j=0; j<((param*)l)->size; j++){
            for(int k=0; k<((param*)l)->size; k++)
                c[i][j] += a[i][k] * b[k][j];
        }
    int r=0;
    kill(getppid(), ((param*)l)->sig);
    //printf("filho vou esperar sinal\n");
    pause();
    for(int i=((param*)l)->inicio; i<((param*)l)->fim; i++){
        printf("%d", c[i][0]);
        for(int j=1; j<((param*)l)->size; j++)
            printf(" %d", c[i][j]);
        printf("\n");
    }
    kill(getppid(), ((param*)l)->sig);

    exit(0);
}

int main(){
    int n;

    signal(SIGUSR1, trata_sinalf1);
    signal(SIGUSR2, trata_sinalf2);

    scanf("%d", &n);

    leMatriz(n);

    struct t_param t;
    t.inicio = 0;
    t.fim = 2;
    t.size = n;

    int divisao = n/THREADS;
    int resto = n%THREADS;
    int sigs[2] = {SIGUSR1, SIGUSR2};

    pid_t ids[THREADS];

    for(int i=0; i <THREADS; i++){
        param *t;
        t=malloc(sizeof(param));
        t->inicio = i*divisao;
        t->sig=sigs[i];
        if(i==THREADS-1)
            t->fim=resto+i*divisao+divisao;
        else
            t->fim=i*divisao+divisao;
        t->size = n;
        ids[i] = fork();
        if(!ids[i])
            multiplica(t);
    }
    pause();
    while(sinalf1 == 0 || sinalf2 == 0){
        pause();
    }

    kill(ids[0], SIGUSR1);
    pause();
    kill(ids[1], SIGUSR1);

    wait(NULL);
    wait(NULL);

    return 0;
}